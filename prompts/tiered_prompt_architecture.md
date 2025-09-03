# 分层级提示词架构系统

## 设计理念

为了适配不同上下文长度限制的AI模型，本系统设计了三层级的提示词模板架构，确保在任何上下文限制下都能高质量完成代码注释生成任务。

## 架构概览

### 三层级设计

```
🔥 完整版 (Full Version)
├── 上下文需求: 150K-200K tokens
├── 适用模型: Claude Sonnet 4, GPT-4 Turbo (长上下文)
├── 功能特性: 完整项目理解 + 渐进式分析 + 深度注释
└── 质量水平: 最高质量，包含教育价值和架构洞察

⚡ 标准版 (Standard Version)  
├── 上下文需求: 80K-128K tokens
├── 适用模型: GPT-4, Claude 3.5 Sonnet
├── 功能特性: 核心功能说明 + 关键质量要求 + 标准注释
└── 质量水平: 高质量，平衡详细度和效率

💡 精简版 (Compact Version)
├── 上下文需求: 8K-16K tokens  
├── 适用模型: GPT-3.5, 其他短上下文模型
├── 功能特性: 核心任务指令 + 基本格式要求 + 简洁注释
└── 质量水平: 标准质量，确保核心功能完成
```

## 版本特性对比

| 特性维度 | 完整版 | 标准版 | 精简版 |
|---------|--------|--------|--------|
| **项目理解建立** | ✅ 完整三阶段流程 | ⚡ 简化项目分析 | 💡 基础上下文 |
| **渐进式代码分析** | ✅ 动态调整策略 | ⚡ 标准分析流程 | 💡 直接处理 |
| **注释详细程度** | ✅ 深度教育性注释 | ⚡ 标准详细注释 | 💡 核心功能注释 |
| **质量检查机制** | ✅ 七层质量检查 | ⚡ 五层质量检查 | 💡 三层质量检查 |
| **示例和指导** | ✅ 丰富示例和最佳实践 | ⚡ 关键示例 | 💡 基本示例 |
| **错误处理** | ✅ 完整错误处理指导 | ⚡ 标准错误处理 | 💡 基本错误处理 |
| **性能优化建议** | ✅ 深度性能分析 | ⚡ 关键优化点 | 💡 基本优化提示 |

## 上下文自适应选择机制

### 自动版本选择逻辑

```python
def select_prompt_version(model_name: str, context_limit: int) -> str:
    """
    根据AI模型和上下文限制自动选择合适的提示词版本
    """
    if context_limit >= 150000:  # 150K+ tokens
        return "full"
    elif context_limit >= 80000:  # 80K+ tokens  
        return "standard"
    else:  # < 80K tokens
        return "compact"
```

### 模型映射表

```yaml
model_mappings:
  # 长上下文模型 - 完整版
  claude_sonnet_4:
    context_limit: 200000
    recommended_version: "full"

  gpt_4_turbo_long:
    context_limit: 128000
    recommended_version: "full"

  # 中等上下文模型 - 标准版
  gpt_4:
    context_limit: 128000
    recommended_version: "standard"

  claude_3_5_sonnet:
    context_limit: 100000
    recommended_version: "standard"

  # 短上下文模型 - 精简版
  gpt_3_5_turbo:
    context_limit: 16000
    recommended_version: "compact"

  claude_3_haiku:
    context_limit: 100000
    recommended_version: "compact"  # 为了快速响应
```

## 核心任务定义（所有版本共享）

### 三步骤代码处理流程

所有版本都必须严格执行以下三个步骤：

1. **清理原有注释**
   - 移除所有现有注释（行内注释、块注释、文档字符串）
   - 保持代码逻辑和结构完全不变
   - 确保语法正确性和可执行性

2. **代码格式化**  
   - 按照语言标准规范格式化
   - 统一缩进、空格、换行等格式要素
   - 严禁修改标识符或字面量

3. **生成中文注释**
   - 根据版本级别生成相应详细程度的注释
   - 确保技术准确性和教育价值
   - 使用规范的中文技术术语

### 安全约束条件（所有版本必须遵守）

```
🚫 严禁修改代码逻辑
🚫 严禁修改变量名、函数名、类名
🚫 严禁修改字符串字面量和常量值
🚫 严禁改变代码的执行流程
🚫 严禁添加或删除代码行（除注释外）

✅ 允许调整代码格式和缩进
✅ 允许添加符合规范的注释
✅ 允许优化空白字符的使用
```

## 质量保证机制

### 分层级质量标准

#### 完整版质量标准
- 技术准确性: 95%+
- 教育价值: 90%+  
- 中文本土化: 95%+
- 实用性: 90%+
- 完整性: 95%+

#### 标准版质量标准  
- 技术准确性: 90%+
- 教育价值: 80%+
- 中文本土化: 90%+
- 实用性: 85%+
- 完整性: 85%+

#### 精简版质量标准
- 技术准确性: 85%+
- 教育价值: 70%+
- 中文本土化: 85%+
- 实用性: 80%+
- 完整性: 75%+

### 回退机制

当上下文不足时的处理策略：

```
完整版 → 标准版 → 精简版 → 基础模式
```

1. **智能降级**: 自动检测上下文使用情况，必要时降级到更简洁的版本
2. **核心保证**: 即使在最精简模式下，也要确保三步骤流程完整执行
3. **质量维持**: 降级时优先保证技术准确性，其次考虑教育价值

## 文件组织结构

```
prompts/
├── tiered_prompt_architecture.md     # 本文档：架构设计
├── context_adaptive_selector.md      # 上下文自适应选择器
├── quality_assurance_framework.md    # 质量保证框架
│
├── 完整版提示词模板 (Full Version)
│   ├── python_prompts_full.md        # Python完整版
│   ├── javascript_prompts_full.md    # JavaScript完整版
│   ├── typescript_prompts_full.md    # TypeScript完整版
│   ├── java_prompts_full.md          # Java完整版
│   ├── cpp_prompts_full.md           # C++完整版
│   ├── c_prompts_full.md             # C语言完整版
│   ├── go_prompts_full.md            # Go完整版
│   └── rust_prompts_full.md          # Rust完整版
│
├── 标准版提示词模板 (Standard Version)
│   ├── python_prompts_standard.md    # Python标准版
│   ├── javascript_prompts_standard.md # JavaScript标准版
│   ├── typescript_prompts_standard.md # TypeScript标准版
│   ├── java_prompts_standard.md      # Java标准版
│   ├── cpp_prompts_standard.md       # C++标准版
│   ├── c_prompts_standard.md         # C语言标准版
│   ├── go_prompts_standard.md        # Go标准版
│   └── rust_prompts_standard.md      # Rust标准版
│
├── 精简版提示词模板 (Compact Version)
│   ├── python_prompts_compact.md     # Python精简版
│   ├── javascript_prompts_compact.md # JavaScript精简版
│   ├── typescript_prompts_compact.md # TypeScript精简版
│   ├── java_prompts_compact.md       # Java精简版
│   ├── cpp_prompts_compact.md        # C++精简版
│   ├── c_prompts_compact.md          # C语言精简版
│   ├── go_prompts_compact.md         # Go精简版
│   └── rust_prompts_compact.md       # Rust精简版
│
└── 原有模板 (兼容性保留)
    ├── python_prompts.md             # Python原版模板
    ├── javascript_prompts.md         # JavaScript原版模板
    ├── java_prompts.md               # Java原版模板
    ├── cpp_prompts.md                # C++原版模板
    ├── go_prompts.md                 # Go原版模板
    └── rust_prompts.md               # Rust原版模板
```

## 使用指南

### 快速开始

1. **确定AI模型**: 识别当前使用的AI模型和上下文限制
2. **选择版本**: 根据上下文限制选择合适的提示词版本
3. **执行任务**: 使用选定版本的提示词处理代码
4. **质量检查**: 验证输出是否符合预期质量标准

### 版本选择建议

- **新项目或复杂代码**: 优先使用完整版，获得最佳理解和注释质量
- **日常开发任务**: 使用标准版，平衡质量和效率
- **快速处理或简单代码**: 使用精简版，确保基本功能完成

## 下一步计划

1. 实现完整版提示词模板（7种语言）
2. 创建标准版提示词模板（优化版）  
3. 开发精简版提示词模板（核心版）
4. 建立自动化测试和质量验证机制
5. 创建上下文自适应选择器工具
