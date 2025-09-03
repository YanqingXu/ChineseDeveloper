# 上下文自适应选择机制

## 设计目标

创建智能的提示词版本选择系统，根据AI模型的上下文长度限制和当前任务复杂度，自动选择最适合的提示词版本，确保在任何环境下都能获得最佳的代码注释生成效果。

## 核心组件

### 1. 模型识别器

#### 支持的AI模型映射

```yaml
# 长上下文模型 (150K+ tokens) - 推荐完整版
long_context_models:
  - claude-3-5-sonnet-20241022    # Claude Sonnet 4 (200K)
  - claude-3-opus-20240229        # Claude 3 Opus (200K)
  - gpt-4-turbo-2024-04-09       # GPT-4 Turbo (128K)
  - gpt-4-1106-preview           # GPT-4 Turbo Preview (128K)

# 中等上下文模型 (80K-128K tokens) - 推荐标准版  
medium_context_models:
  - gpt-4-0613                   # GPT-4 (8K/32K)
  - gpt-4-0314                   # GPT-4 (8K/32K)
  - claude-3-sonnet-20240229     # Claude 3 Sonnet (200K, 但推荐标准版以提高效率)
  - claude-3-haiku-20240307      # Claude 3 Haiku (200K, 但推荐标准版)

# 短上下文模型 (16K- tokens) - 推荐精简版
short_context_models:
  - gpt-3.5-turbo-0125          # GPT-3.5 Turbo (16K)
  - gpt-3.5-turbo-1106          # GPT-3.5 Turbo (16K)
  - gpt-3.5-turbo-instruct      # GPT-3.5 Instruct (4K)
```

### 2. 上下文评估器

#### 代码复杂度评估

```python
def assess_code_complexity(code: str, language: str) -> str:
    """
    评估代码复杂度，影响提示词版本选择
    
    Returns:
        "simple" | "medium" | "complex"
    """
    factors = {
        "lines": len(code.split('\n')),
        "functions": count_functions(code, language),
        "classes": count_classes(code, language),
        "imports": count_imports(code, language),
        "complexity": calculate_cyclomatic_complexity(code)
    }
    
    # 复杂度评分逻辑
    if factors["lines"] > 200 or factors["complexity"] > 15:
        return "complex"
    elif factors["lines"] > 50 or factors["functions"] > 5:
        return "medium"
    else:
        return "simple"
```

#### 上下文需求预估

```python
def estimate_context_usage(code: str, language: str, version: str) -> int:
    """
    预估不同版本提示词的上下文使用量
    
    Returns:
        预估的token数量
    """
    base_prompt_tokens = {
        "full": 15000,      # 完整版基础提示词
        "standard": 8000,   # 标准版基础提示词  
        "compact": 3000     # 精简版基础提示词
    }
    
    code_tokens = estimate_code_tokens(code)
    response_tokens = estimate_response_tokens(code, version)
    
    return base_prompt_tokens[version] + code_tokens + response_tokens
```

### 3. 智能选择算法

#### 主选择逻辑

```python
def select_optimal_version(
    model_name: str, 
    code: str, 
    language: str,
    user_preference: str = "auto"
) -> dict:
    """
    智能选择最优的提示词版本
    
    Args:
        model_name: AI模型名称
        code: 待处理的代码
        language: 编程语言
        user_preference: 用户偏好 ("auto", "quality", "speed", "balanced")
    
    Returns:
        选择结果和推荐理由
    """
    
    # 1. 获取模型信息
    model_info = get_model_info(model_name)
    
    # 2. 评估代码复杂度
    complexity = assess_code_complexity(code, language)
    
    # 3. 计算各版本的上下文需求
    context_needs = {
        version: estimate_context_usage(code, language, version)
        for version in ["full", "standard", "compact"]
    }
    
    # 4. 应用选择策略
    if user_preference == "quality":
        # 优先质量：选择最高可用版本
        for version in ["full", "standard", "compact"]:
            if context_needs[version] <= model_info["context_limit"] * 0.8:
                return create_selection_result(version, "quality_priority")
                
    elif user_preference == "speed":
        # 优先速度：选择最精简可用版本
        for version in ["compact", "standard", "full"]:
            if context_needs[version] <= model_info["context_limit"] * 0.6:
                return create_selection_result(version, "speed_priority")
                
    else:  # auto 或 balanced
        # 智能平衡选择
        return balanced_selection(model_info, complexity, context_needs)

def balanced_selection(model_info: dict, complexity: str, context_needs: dict) -> dict:
    """平衡选择策略"""
    
    context_limit = model_info["context_limit"]
    
    # 根据代码复杂度调整选择策略
    if complexity == "complex":
        # 复杂代码优先使用完整版
        if context_needs["full"] <= context_limit * 0.75:
            return create_selection_result("full", "complex_code_needs_full_analysis")
        elif context_needs["standard"] <= context_limit * 0.8:
            return create_selection_result("standard", "complex_code_fallback_to_standard")
        else:
            return create_selection_result("compact", "context_limit_forces_compact")
            
    elif complexity == "medium":
        # 中等复杂度代码优先使用标准版
        if context_needs["standard"] <= context_limit * 0.7:
            return create_selection_result("standard", "medium_code_optimal_for_standard")
        elif context_needs["full"] <= context_limit * 0.8:
            return create_selection_result("full", "sufficient_context_for_full")
        else:
            return create_selection_result("compact", "context_limit_requires_compact")
            
    else:  # simple
        # 简单代码可以使用任何版本，选择最经济的
        if context_needs["compact"] <= context_limit * 0.4:
            return create_selection_result("compact", "simple_code_efficient_with_compact")
        elif context_needs["standard"] <= context_limit * 0.6:
            return create_selection_result("standard", "simple_code_good_with_standard")
        else:
            return create_selection_result("full", "simple_code_with_full_context")
```

### 4. 动态调整机制

#### 实时监控和调整

```python
class AdaptiveSelector:
    def __init__(self):
        self.performance_history = {}
        self.context_usage_stats = {}
    
    def monitor_performance(self, selection_result: dict, actual_quality: float):
        """监控选择效果，用于优化算法"""
        key = f"{selection_result['model']}_{selection_result['version']}_{selection_result['complexity']}"
        
        if key not in self.performance_history:
            self.performance_history[key] = []
        
        self.performance_history[key].append({
            "quality": actual_quality,
            "context_used": selection_result["context_used"],
            "timestamp": datetime.now()
        })
    
    def optimize_selection_algorithm(self):
        """基于历史数据优化选择算法"""
        # 分析性能数据，调整选择权重
        for key, history in self.performance_history.items():
            if len(history) >= 10:  # 有足够数据时进行优化
                avg_quality = sum(h["quality"] for h in history) / len(history)
                if avg_quality < 0.8:  # 质量不达标
                    self.adjust_selection_weights(key, "increase_version")
```

### 5. 用户界面和配置

#### 选择器配置选项

```yaml
selector_config:
  # 默认选择策略
  default_strategy: "balanced"  # auto, quality, speed, balanced
  
  # 上下文安全边界
  context_safety_margin: 0.2  # 保留20%上下文空间
  
  # 质量阈值
  minimum_quality_threshold: 0.75
  
  # 性能优化
  enable_caching: true
  cache_duration: 3600  # 1小时
  
  # 用户偏好
  user_preferences:
    prefer_quality_over_speed: true
    allow_automatic_fallback: true
    show_selection_reasoning: true
```

#### 使用示例

```python
# 基本使用
selector = ContextAdaptiveSelector()
result = selector.select_version(
    model="claude-3-5-sonnet-20241022",
    code=python_code,
    language="python"
)

print(f"推荐版本: {result['version']}")
print(f"推荐理由: {result['reasoning']}")
print(f"预估质量: {result['expected_quality']}")

# 高级配置使用
selector.configure({
    "strategy": "quality",
    "safety_margin": 0.15,
    "enable_monitoring": True
})

result = selector.select_version_with_monitoring(
    model="gpt-4-turbo",
    code=javascript_code,
    language="javascript",
    quality_callback=quality_feedback_function
)
```

## 集成指南

### 1. 与现有提示词系统集成

```python
def get_prompt_template(language: str, version: str) -> str:
    """获取指定语言和版本的提示词模板"""
    template_map = {
        "python": {
            "full": "python_prompts_full.md",
            "standard": "python_prompts_standard.md", 
            "compact": "python_prompts_compact.md"
        },
        "javascript": {
            "full": "javascript_prompts_full.md",
            "standard": "javascript_prompts_standard.md",
            "compact": "javascript_prompts_compact.md"
        }
        # ... 其他语言
    }
    
    template_file = template_map[language][version]
    return load_template(template_file)
```

### 2. API接口设计

```python
@app.route('/api/select-prompt-version', methods=['POST'])
def api_select_version():
    """REST API接口"""
    data = request.json
    
    result = selector.select_version(
        model=data['model'],
        code=data['code'],
        language=data['language'],
        user_preference=data.get('preference', 'auto')
    )
    
    return jsonify({
        "version": result["version"],
        "reasoning": result["reasoning"],
        "expected_quality": result["expected_quality"],
        "context_usage": result["context_usage"],
        "template_path": result["template_path"]
    })
```

## 质量保证

### 选择准确性验证

1. **A/B测试**: 对比不同选择策略的效果
2. **用户反馈**: 收集实际使用中的质量评价
3. **自动化测试**: 定期验证选择逻辑的正确性
4. **性能监控**: 跟踪上下文使用效率和响应质量

### 持续优化机制

1. **数据驱动优化**: 基于使用数据调整选择算法
2. **模型更新适配**: 及时适配新的AI模型
3. **用户习惯学习**: 学习用户偏好，个性化推荐
4. **质量反馈循环**: 建立质量评估和改进的闭环

## 下一步实现

1. 实现核心选择算法
2. 创建模型信息数据库
3. 开发性能监控系统
4. 建立用户反馈机制
5. 集成到现有提示词系统
