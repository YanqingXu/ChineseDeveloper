# TypeScript代码注释生成提示词 - 精简版

## 版本信息
- **版本类型**: 精简版 (Compact Version)
- **适用模型**: GPT-3.5 Turbo (16K tokens), 其他短上下文模型
- **上下文需求**: 8K-16K tokens
- **质量水平**: 标准质量，确保核心功能完成

## 任务声明

你是TypeScript开发专家，为中文开发者生成实用的代码注释。执行三步骤处理：清理注释→格式化→生成中文注释。

## 输入代码
```typescript
{code}
```

## 处理流程

### ⚠️ 重要：代码处理安全规则

**严禁修改原始源代码文件** - 绝对不能对原始代码文件进行任何修改或覆盖

**操作流程**：
1. **创建副本目录** - 将整个源代码目录复制一份，在目录名后添加"_cn"后缀
   - 例如：`src/` → `src_cn/`
   - 例如：`project/` → `project_cn/`

2. **仅对副本添加注释** - 只在带有"_cn"后缀的副本目录中的代码文件添加中文注释

3. **保持目录结构** - 副本目录必须保持与原始目录完全相同的文件结构和层级关系

4. **文件名保持不变** - 副本目录中的文件名与原始文件名完全相同，不添加任何后缀

**安全保证**：
- ✅ 原始代码保持完全不变
- ✅ 仅在副本目录中进行注释添加

### 步骤1：清理原有注释
- 移除所有注释（//、/* */、/** */、TSDoc注释）
- 保持代码逻辑完全不变
- 严禁修改标识符、类型定义或字面量

### 步骤2：代码格式化
- 遵循TypeScript格式规范
- 统一缩进（2个空格）
- 优化代码布局

### 步骤3：生成中文注释

#### 接口/类型注释格式
```typescript
/**
 * 功能说明：[简洁描述接口/类型功能]
 * 
 * @template T - 泛型参数说明
 * @since TypeScript 4.5+
 */
interface ExampleInterface<T> {
  id: string;
  data: T;
}
```

#### 函数注释格式
```typescript
/**
 * 功能说明：[简洁描述函数功能]
 * 
 * @param data - 参数说明
 * @param options - 配置选项
 * @returns 返回值说明
 * @throws {Error} 错误情况说明
 * 
 * @example
 * const result = await processData(data, options);
 */
```

#### 行内注释格式
```typescript
// 类型定义：创建只读版本
type ReadonlyEntity<T> = {
  readonly [K in keyof T]: T[K];
};

// 泛型约束：确保类型参数满足条件
function updateEntity<T extends { id: string }>(
  entity: T, 
  updates: Partial<T>
): T {
  // 对象合并：保持类型安全
  return { ...entity, ...updates };
}

// 类型守卫：运行时类型检查
function isUser(obj: unknown): obj is User {
  return typeof obj === 'object' && obj !== null && 'id' in obj;
}

// 装饰器：为类添加元数据
@Injectable()
class UserService {
  // 异步方法：处理用户数据
  async getUser(id: string): Promise<User> {
    const user = await this.repository.findById(id);
    
    if (!user) {
      // 错误处理：抛出类型安全的错误
      throw new NotFoundError(`用户 ${id} 不存在`);
    }
    
    return user;
  }
}

// 条件类型：根据条件选择类型
type ApiResponse<T> = T extends string 
  ? { message: T } 
  : { data: T };

// 异步处理：网络请求重试机制
async function fetchData<T>(url: string): Promise<T> {
  try {
    const response = await fetch(url);
    
    if (!response.ok) {
      throw new Error(`HTTP ${response.status}`);
    }
    
    // 类型安全的JSON解析
    return await response.json() as T;
  } catch (error) {
    // 错误处理：记录并重新抛出
    console.error('请求失败:', error);
    throw error;
  }
}

// 高级类型：模板字面量类型
type EventName<T extends string> = `on${Capitalize<T>}`;

// 映射类型：创建可选属性
type PartialExcept<T, K extends keyof T> = Partial<T> & Pick<T, K>;

// 事件处理：类型安全的事件系统
class EventEmitter<TEvents extends Record<string, any[]>> {
  private listeners = new Map<keyof TEvents, Function[]>();
  
  // 事件监听：类型安全的监听器注册
  on<K extends keyof TEvents>(
    event: K,
    listener: (...args: TEvents[K]) => void
  ): void {
    const eventListeners = this.listeners.get(event) || [];
    eventListeners.push(listener);
    this.listeners.set(event, eventListeners);
  }
  
  // 事件触发：类型安全的事件发射
  emit<K extends keyof TEvents>(event: K, ...args: TEvents[K]): void {
    const eventListeners = this.listeners.get(event) || [];
    eventListeners.forEach(listener => listener(...args));
  }
}
```

#### TypeScript特殊特性注释
```typescript
// 模块声明：为第三方库添加类型
declare module 'third-party-lib' {
  export function process<T>(data: T): Promise<T>;
}

// 全局类型扩展：扩展Window对象
declare global {
  interface Window {
    customAPI: {
      version: string;
    };
  }
}

// 工具类型：提取函数参数类型
type FunctionArgs<T> = T extends (...args: infer P) => any ? P : never;

// 递归类型：深度可选
type DeepPartial<T> = {
  [P in keyof T]?: T[P] extends object ? DeepPartial<T[P]> : T[P];
};

// 装饰器工厂：创建参数化装饰器
function Column(name: string) {
  return function (target: any, propertyKey: string) {
    // 添加元数据
    Reflect.defineMetadata('columnName', name, target, propertyKey);
  };
}

// 类型断言：安全的类型转换
function assertIsUser(obj: unknown): asserts obj is User {
  if (!isUser(obj)) {
    throw new Error('对象不是有效的User类型');
  }
}
```

## 质量要求

### 基本标准
1. **TypeScript特性** (85%+) - 类型定义正确，泛型使用合理
2. **类型安全** (85%+) - 提供编译时类型检查
3. **实用性** (80%+) - 注释对开发有帮助
4. **中文规范** (85%+) - 中文表达自然

### 注释要求
- 所有导出的接口/类型必须有TSDoc注释
- 泛型约束必须有说明
- 装饰器使用必须有注释
- 关键类型逻辑必须有解释

## 安全约束

### 严禁操作
- 🚫 修改代码逻辑
- 🚫 修改类型定义、接口声明
- 🚫 修改变量名、函数名、类名
- 🚫 修改装饰器和泛型约束
- 🚫 改变导入导出语句

### 允许操作
- ✅ 调整代码格式
- ✅ 添加TSDoc注释
- ✅ 添加行内注释

## 输出要求

生成的代码必须：
- 保持原有功能不变
- 包含完整的中文注释
- 符合TSDoc规范
- 体现TypeScript类型安全特性

## 执行指令

现在开始执行三步骤处理流程，生成带有高质量中文注释的TypeScript代码。
