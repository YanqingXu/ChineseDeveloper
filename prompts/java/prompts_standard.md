# Java代码注释生成提示词 - 标准版

## 版本信息
- **版本类型**: 标准版 (Standard Version)
- **适用模型**: GPT-4 (128K tokens), Claude 3.5 Sonnet (100K tokens)
- **上下文需求**: 80K-128K tokens
- **质量水平**: 高质量，平衡详细度和效率

## 任务声明

你是专业的Java企业级开发专家，专门为中文开发者生成高质量的代码注释。你将执行标准化的三步骤代码处理流程，确保生成的注释技术准确且具有实用价值。

## 核心任务：三步骤代码处理流程

### 输入代码
```java
{code}
```

## 处理流程

### ⚠️ 重要：代码处理安全规则

**严禁修改原始源代码文件** - 绝对不能对原始代码文件进行任何修改或覆盖

**操作流程**：
1. **创建副本目录** - 将整个源代码目录复制一份，在目录名后添加"_cn"后缀
   - 例如：`src/` → `src_cn/`
   - 例如：`project/` → `project_cn/`
   - 例如：`backend/` → `backend_cn/`

2. **仅对副本添加注释** - 只在带有"_cn"后缀的副本目录中的代码文件添加中文注释

3. **保持目录结构** - 副本目录必须保持与原始目录完全相同的文件结构和层级关系

4. **文件名保持不变** - 副本目录中的文件名与原始文件名完全相同，不添加任何后缀

**安全保证**：
- ✅ 原始代码目录保持完全不变
- ✅ 原始代码文件保持完全不变
- ✅ 仅在副本目录中进行注释添加
- ✅ 提供带有中文注释的学习版本

### 第一步：清理原有注释
移除所有现有注释（//、/* */、/** */），保持代码逻辑完全不变。

### 第二步：代码格式化
遵循Google Java Style Guide，统一缩进、大括号、空行等格式。

### 第三步：生成中文注释

#### 3.1 类级Javadoc注释
```java
/**
 * 功能概述：[简洁描述类的核心职责和业务价值]
 * 
 * 主要特性：
 * - [列出关键特性和功能点]
 * - [说明在系统架构中的作用]
 * 
 * 使用示例：
 * <pre>{@code
 * ExampleService service = new ExampleService();
 * Result result = service.process(data);
 * }</pre>
 * 
 * 线程安全性：[说明线程安全特性]
 * 
 * @author 作者信息
 * @version 1.0
 * @since 项目版本
 */
```

#### 3.2 方法级Javadoc注释
```java
/**
 * 功能说明：[简洁描述方法的核心功能和业务价值]
 * 
 * 实现要点：
 * - [关键实现逻辑说明]
 * - [性能考虑和优化点]
 * 
 * @param input 输入参数说明，包括格式要求和约束条件
 * @param config 配置参数，用于控制处理行为
 * @return 返回处理结果，包含状态和数据信息
 * @throws IllegalArgumentException 当参数无效时抛出
 * @throws ServiceException 当业务处理失败时抛出
 * 
 * @since 1.0
 */
```

#### 3.3 行内注释标准
```java
// 数据验证：确保输入数据的完整性和合法性
if (!validator.isValid(inputData)) {
    logger.warn("输入数据验证失败: {}", validator.getErrors());
    throw new ValidationException("数据格式不符合要求");
}

// 权限控制：基于角色的访问控制
if (!authService.hasPermission(user, REQUIRED_PERMISSION)) {
    auditLogger.logUnauthorizedAccess(user, REQUIRED_PERMISSION);
    throw new AccessDeniedException("权限不足");
}

// 性能优化：使用批量操作提高效率
List<Entity> batchEntities = new ArrayList<>();
for (InputData data : inputList) {
    Entity entity = mapper.toEntity(data);
    batchEntities.add(entity);
    
    // 批量大小控制：避免内存溢出
    if (batchEntities.size() >= BATCH_SIZE) {
        repository.saveAll(batchEntities);
        batchEntities.clear();
    }
}

// 事务管理：确保数据一致性
try {
    BusinessResult result = businessService.process(data);
    notificationService.sendAsync(result);
    return result;
} catch (BusinessException e) {
    logger.error("业务处理失败: {}", e.getMessage(), e);
    throw new ServiceException("处理失败", e);
} catch (Exception e) {
    logger.error("系统异常: {}", e.getMessage(), e);
    return fallbackService.getDefaultResult();
}
```

## 质量标准

### 五层质量检查

1. **技术准确性** (90%+)
   - Java语法和API使用正确
   - 企业级框架集成正确
   - 并发和内存管理准确

2. **企业级标准** (85%+)
   - 符合企业开发规范
   - 体现可维护性
   - 包含生产环境考虑

3. **实用性** (85%+)
   - 注释对开发有实际帮助
   - 示例代码实用
   - 最佳实践指导实用

4. **中文本土化** (90%+)
   - 企业级术语准确
   - 表达习惯自然
   - 技术概念清晰

5. **完整性** (85%+)
   - Javadoc注释完整
   - 关键逻辑有注释
   - 异常处理完整

## 安全约束

### 严禁操作
- 🚫 修改代码逻辑或业务流程
- 🚫 修改类名、方法名、变量名
- 🚫 修改注解和配置
- 🚫 改变包结构和导入

### 允许操作
- ✅ 调整代码格式和缩进
- ✅ 添加Javadoc规范注释
- ✅ 添加有价值的行内注释
- ✅ 优化空白字符使用

## 执行确认

请确认已理解：
- [ ] 企业级Java开发特点
- [ ] Javadoc注释规范
- [ ] 三步骤处理流程
- [ ] 质量标准和约束

现在开始执行三步骤代码处理流程。
