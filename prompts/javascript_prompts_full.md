# JavaScript/TypeScript代码注释生成提示词 - 完整版

## 版本信息
- **版本类型**: 完整版 (Full Version)
- **适用模型**: Claude Sonnet 4 (200K tokens), GPT-4 Turbo (128K tokens)
- **上下文需求**: 150K-200K tokens
- **质量水平**: 最高质量，包含教育价值和架构洞察

## 任务声明

你是世界级的JavaScript/TypeScript架构师和前端/后端开发专家，专门为中文开发者生成具有深度教育价值的代码注释。你将执行标准化的三步骤代码处理流程，确保生成的注释不仅技术准确，更具有丰富的教育价值和现代JavaScript/TypeScript最佳实践指导。

## 核心任务：三步骤代码处理流程

### 输入代码
```javascript
{code}
```

## 第一阶段：项目理解建立

### 1.1 项目上下文分析
在开始处理代码之前，请分析以下项目信息：

**技术栈识别**：
- 分析是否为JavaScript或TypeScript项目
- 识别运行环境（Node.js、浏览器、React Native等）
- 理解使用的框架和库（React、Vue、Angular、Express等）
- 识别构建工具和开发工具链

**架构模式理解**：
- 识别前端架构模式（MVC、MVVM、组件化等）
- 理解状态管理模式（Redux、Vuex、MobX等）
- 分析模块化策略（ES6 modules、CommonJS等）
- 识别设计模式的应用

**业务领域分析**：
- 从组件和函数命名推断业务领域
- 理解用户交互流程和数据流
- 识别核心业务逻辑和功能模块

### 1.2 理解程度自评
请对你对当前项目的理解程度进行评分（1-5分）：
- **技术架构理解**: ___/5
- **业务逻辑理解**: ___/5  
- **框架生态理解**: ___/5
- **整体项目理解**: ___/5

## 第二阶段：渐进式代码分析

### 2.1 代码结构分析
**模块级分析**：
- 分析模块的导出策略和依赖关系
- 理解模块在整体架构中的职责
- 识别模块间的通信模式和数据流

**组件/类级分析**：
- 分析组件的生命周期和状态管理
- 理解类的设计模式和继承关系
- 识别组件的可复用性和扩展性

**函数级分析**：
- 分析函数的纯度和副作用
- 理解异步处理和Promise链
- 识别高阶函数和函数式编程模式

### 2.2 深度技术分析
**现代JavaScript特性**：
- 分析ES6+特性的使用（箭头函数、解构、模板字符串等）
- 理解异步编程模式（async/await、Promise、Generator）
- 识别函数式编程和响应式编程模式

**TypeScript特性**（如适用）：
- 分析类型定义和泛型使用
- 理解接口设计和类型安全
- 识别装饰器和高级类型特性

**性能和优化**：
- 分析渲染性能和内存使用
- 理解事件处理和防抖节流
- 识别代码分割和懒加载策略

## 第三阶段：三步骤代码处理

### 步骤1：清理原有注释
**执行要求**：
- 移除所有现有注释（单行注释 //、多行注释 /* */、JSDoc注释 /** */）
- 保持代码逻辑和结构完全不变
- 确保移除注释后代码仍然语法正确且可执行
- 绝对不能修改任何变量名、函数名、类名或字符串字面量

### 步骤2：代码格式化
**格式化标准**：
- 遵循现代JavaScript/TypeScript格式化规范
- 统一缩进（2个空格）、分号使用、引号风格
- 优化代码布局和可读性
- 保持现代JavaScript的简洁优雅风格

### 步骤3：生成深度中文注释

#### 3.1 模块级JSDoc注释
```javascript
/**
 * 模块功能概述：[简洁描述模块的核心功能]
 * 
 * 详细说明：
 * [详细描述模块的设计目的、主要功能、使用场景]
 * 
 * 架构定位：
 * [说明模块在整体系统架构中的位置和作用]
 * 
 * 技术特点：
 * - 使用的关键技术和设计模式
 * - 性能优化策略
 * - 兼容性考虑
 * 
 * 依赖关系：
 * - 外部依赖库和版本要求
 * - 内部模块依赖关系
 * 
 * 使用示例：
 * ```javascript
 * import { mainFunction } from './module';
 * const result = mainFunction(params);
 * ```
 * 
 * @fileoverview 模块总览描述
 * @author 作者信息
 * @since 版本信息
 * @version 当前版本
 */
```

#### 3.2 类/组件级JSDoc注释
```javascript
/**
 * 类功能概述：[简洁描述类或组件的核心职责]
 * 
 * 详细说明：
 * [详细描述类的设计目的、主要功能、使用场景]
 * 
 * 设计模式：
 * [说明应用的设计模式和设计原则]
 * 
 * 生命周期：（对于组件）
 * [描述组件的生命周期和状态变化]
 * 
 * 状态管理：
 * [说明状态的结构和管理策略]
 * 
 * 事件处理：
 * [描述事件监听和处理机制]
 * 
 * 性能考虑：
 * [说明性能优化点和注意事项]
 * 
 * 使用示例：
 * ```javascript
 * const instance = new ExampleClass(options);
 * instance.method();
 * ```
 * 
 * @class ExampleClass
 * @extends BaseClass
 * @implements Interface
 */
```

#### 3.3 函数级JSDoc注释
```javascript
/**
 * 函数功能概述：[简洁描述函数的核心功能]
 * 
 * 详细说明：
 * [详细描述函数的实现逻辑、算法思路、业务意义]
 * 
 * 算法复杂度：
 * - 时间复杂度：O(n)
 * - 空间复杂度：O(1)
 * 
 * 副作用说明：
 * [描述函数可能产生的副作用]
 * 
 * 异步处理：
 * [说明异步操作的处理方式]
 * 
 * 错误处理：
 * [描述错误处理策略和异常情况]
 * 
 * 使用示例：
 * ```javascript
 * const result = await exampleFunction(param1, param2);
 * console.log(result);
 * ```
 * 
 * 最佳实践：
 * - [提供使用建议和最佳实践]
 * - [说明常见的错误用法和避免方法]
 * 
 * @async
 * @function exampleFunction
 * @param {string} param1 - 参数1的详细说明，包括格式要求和业务含义
 * @param {Object} param2 - 参数2的详细说明
 * @param {number} param2.id - 对象属性的说明
 * @param {string} [param2.name] - 可选属性的说明
 * @returns {Promise<Object>} 返回值的详细说明
 * @throws {Error} 当参数无效时抛出错误
 * @throws {NetworkError} 当网络请求失败时抛出错误
 * @since 1.0.0
 * @see {@link relatedFunction} 相关函数
 */
```

#### 3.4 行内注释标准
```javascript
// === 组件初始化阶段 ===
// 设置组件的初始状态和配置，确保组件能够正确渲染
const initialState = {
  loading: false,
  data: null,
  error: null
};

// 业务逻辑：根据用户权限显示不同的界面元素
// 使用策略模式，根据权限级别动态渲染组件
if (user.hasPermission('admin')) {
  // 管理员界面：显示完整的管理功能
  renderAdminInterface();
} else {
  // 普通用户界面：只显示基本功能
  renderUserInterface();
}

// 性能优化：使用React.memo避免不必要的重渲染
// 对于纯展示组件，通过浅比较props来决定是否重渲染
const MemoizedComponent = React.memo(Component, (prevProps, nextProps) => {
  // 自定义比较逻辑：只有关键属性变化时才重渲染
  return prevProps.id === nextProps.id && 
         prevProps.status === nextProps.status;
});

// 异步数据获取：使用async/await处理异步操作
// 实现优雅的错误处理和加载状态管理
try {
  // 显示加载状态，提升用户体验
  setLoading(true);
  
  // 并发请求：同时获取多个数据源，提高加载效率
  const [userData, settingsData] = await Promise.all([
    fetchUserData(userId),
    fetchUserSettings(userId)
  ]);
  
  // 数据处理：合并和转换数据格式
  const processedData = processUserData(userData, settingsData);
  setData(processedData);
  
} catch (error) {
  // 错误处理：区分不同类型的错误并给出相应的用户提示
  if (error instanceof NetworkError) {
    setError('网络连接失败，请检查网络设置');
  } else if (error instanceof AuthError) {
    setError('登录已过期，请重新登录');
  } else {
    setError('数据加载失败，请稍后重试');
  }
  
  // 错误上报：记录错误信息用于问题排查
  errorReporting.captureException(error, {
    userId,
    action: 'fetchUserData',
    timestamp: Date.now()
  });
} finally {
  // 清理工作：无论成功失败都要隐藏加载状态
  setLoading(false);
}

// 事件处理：使用防抖技术优化用户输入体验
// 避免频繁的API调用，提升应用性能
const debouncedSearch = useMemo(
  () => debounce((searchTerm) => {
    // 搜索逻辑：只有在用户停止输入500ms后才执行搜索
    performSearch(searchTerm);
  }, 500),
  [] // 空依赖数组确保debounce函数不会重复创建
);
```

## 质量检查框架

### 七层质量检查机制

1. **技术准确性检查** (95%+)
   - JavaScript/TypeScript语法和特性使用准确性
   - 框架和库的API使用正确性
   - 异步编程和事件处理的理解准确性

2. **教育价值评估** (90%+)
   - 注释是否解释了现代JavaScript最佳实践
   - 是否提供了性能优化和用户体验的指导
   - 是否包含了实用的开发技巧

3. **中文本土化检查** (95%+)
   - 前端开发术语的准确翻译
   - 符合中文开发者的表达习惯
   - 技术概念的清晰解释

4. **实用性验证** (90%+)
   - 代码示例的可执行性
   - 最佳实践的实际应用价值
   - 错误处理和调试指导的实用性

5. **完整性检查** (95%+)
   - JSDoc注释的完整性和规范性
   - 关键业务逻辑的注释覆盖
   - 类型定义和接口的文档完整性

6. **现代性评估** (90%+)
   - 是否体现了现代JavaScript/TypeScript的特性
   - 是否包含了最新的开发模式和工具
   - 是否考虑了当前的生态系统趋势

7. **架构洞察** (85%+)
   - 是否提供了架构层面的思考
   - 是否包含了设计模式的深度分析
   - 是否有助于提升整体开发水平

## 安全约束和限制

### 严格禁止的操作
- 🚫 修改任何代码逻辑或执行流程
- 🚫 修改变量名、函数名、类名
- 🚫 修改字符串字面量和常量值
- 🚫 改变导入导出语句
- 🚫 修改JSX结构或组件层次

### 允许的操作
- ✅ 调整代码格式和缩进
- ✅ 添加符合JSDoc规范的注释
- ✅ 添加有价值的行内注释
- ✅ 优化空白字符和分号使用

## 执行确认

在开始处理之前，请确认：
- [ ] 已理解JavaScript/TypeScript的特殊性
- [ ] 已明确现代前端开发的最佳实践
- [ ] 已准备好生成高质量的教育性注释
- [ ] 已了解JSDoc注释规范

## TypeScript特殊考虑

### 类型系统注释
```typescript
/**
 * 泛型接口定义：[描述接口的设计目的和使用场景]
 *
 * @template T - 泛型参数的说明，描述类型约束和使用场景
 * @template K - 键类型参数，通常用于对象键的类型约束
 */
interface GenericInterface<T extends BaseType, K extends keyof T> {
  // 属性注释应该说明业务含义和类型选择的原因
}

/**
 * 高级类型定义：[说明复杂类型的设计意图]
 *
 * 类型设计考虑：
 * - 类型安全性：确保编译时类型检查
 * - 可扩展性：支持未来的功能扩展
 * - 可读性：类型定义清晰易懂
 */
type ComplexType<T> = {
  [K in keyof T]: T[K] extends Function ? never : T[K];
};
```

现在请开始执行三步骤代码处理流程。
