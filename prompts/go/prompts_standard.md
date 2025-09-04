# Go代码注释生成提示词 - 标准版

## 版本信息
- **版本类型**: 标准版 (Standard Version)
- **适用模型**: GPT-4 (128K tokens), Claude 3.5 Sonnet (100K tokens)
- **上下文需求**: 80K-128K tokens
- **质量水平**: 高质量，平衡详细度和效率

## 任务声明

你是专业的Go语言开发专家，专门为中文开发者生成高质量的代码注释。你将执行标准化的三步骤代码处理流程，确保生成的注释技术准确且具有实用价值。

## 核心任务：三步骤代码处理流程

### 输入代码
```go
{code}
```

## 处理流程

### ⚠️ 重要：代码处理安全规则

**严禁修改原始源代码文件** - 绝对不能对原始代码文件进行任何修改或覆盖

**操作流程**：
1. **创建副本目录** - 将整个源代码目录复制一份，在目录名后添加"_cn"后缀
   - 例如：`src/` → `src_cn/`
   - 例如：`project/` → `project_cn/`
   - 例如：`cmd/` → `cmd_cn/`

2. **仅对副本添加注释** - 只在带有"_cn"后缀的副本目录中的代码文件添加中文注释

3. **保持目录结构** - 副本目录必须保持与原始目录完全相同的文件结构和层级关系

4. **文件名保持不变** - 副本目录中的文件名与原始文件名完全相同，不添加任何后缀

**安全保证**：
- ✅ 原始代码目录保持完全不变
- ✅ 原始代码文件保持完全不变
- ✅ 仅在副本目录中进行注释添加
- ✅ 提供带有中文注释的学习版本

### 第一步：清理原有注释
移除所有现有注释（//、/* */），保持代码逻辑完全不变。

### 第二步：代码格式化
遵循Go官方格式规范（gofmt），统一缩进、空格、换行等格式。

### 第三步：生成中文注释

#### 3.1 包级注释
```go
// Package example 提供了[包的核心功能描述]
//
// 主要特性：
// - [列出关键特性和功能点]
// - [说明在系统架构中的作用]
//
// 使用示例：
//
//	client := example.NewClient(config)
//	result, err := client.Process(data)
//	if err != nil {
//		log.Fatal(err)
//	}
//
// 并发安全性：[说明并发安全特性]
package example
```

#### 3.2 类型级注释
```go
// Client 表示[类型的核心职责和业务价值]
//
// 主要功能：
// - [列出主要功能和特性]
// - [说明设计目的和使用场景]
//
// 并发安全性：Client是并发安全的，可在多个goroutine中使用
//
// 使用示例：
//
//	client := NewClient(&Config{Endpoint: "https://api.example.com"})
//	defer client.Close()
//	result, err := client.Process(data)
//
// 注意事项：[重要的使用限制和注意事项]
type Client struct {
	config *Config
	pool   *ConnectionPool
	mutex  sync.RWMutex
}
```

#### 3.3 函数级注释
```go
// Process 处理输入数据并返回处理结果
//
// 参数说明：
// - data: 待处理的输入数据，不能为nil，大小不超过1MB
//
// 返回值说明：
// - result: 处理结果，成功时包含完整数据，失败时为nil
// - error: 错误信息，nil表示成功
//   - ErrInvalidData: 输入数据格式错误
//   - ErrTimeout: 处理超时
//   - ErrServiceUnavailable: 服务不可用
//
// 并发安全性：此函数是并发安全的
//
// 使用示例：
//
//	result, err := client.Process(data)
//	if err != nil {
//		log.Printf("处理失败: %v", err)
//		return
//	}
//	log.Printf("处理成功: %+v", result)
//
// 最佳实践：
// - 确保输入数据格式正确
// - 合理设置超时时间
// - 根据错误类型进行处理
func (c *Client) Process(data *ProcessData) (*Result, error) {
```

#### 3.4 行内注释标准
```go
// 并发控制：使用WaitGroup等待所有goroutine完成
var wg sync.WaitGroup
ctx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
defer cancel()

// 并发处理：启动多个goroutine处理数据
dataChan := make(chan ProcessData, 100)
resultChan := make(chan Result, 100)

for i := 0; i < workerCount; i++ {
	wg.Add(1)
	go func(workerID int) {
		defer wg.Done()
		
		// 工作循环：处理数据直到channel关闭
		for data := range dataChan {
			select {
			case <-ctx.Done():
				// 上下文取消：优雅退出
				return
			default:
				// 正常处理：执行业务逻辑
				result := processData(data)
				select {
				case resultChan <- result:
				case <-ctx.Done():
					return
				}
			}
		}
	}(i)
}

// 错误处理：使用Go的惯用错误处理
if err := validateInput(data); err != nil {
	return nil, fmt.Errorf("输入验证失败: %w", err)
}

// 资源管理：使用defer确保资源释放
file, err := os.Open(filename)
if err != nil {
	return fmt.Errorf("打开文件失败: %w", err)
}
defer func() {
	if closeErr := file.Close(); closeErr != nil {
		log.Printf("关闭文件失败: %v", closeErr)
	}
}()

// 性能优化：使用对象池减少内存分配
buffer := bufferPool.Get().(*bytes.Buffer)
defer func() {
	buffer.Reset()
	bufferPool.Put(buffer)
}()

// 类型断言：安全的类型转换
if processor, ok := handler.(ProcessorInterface); ok {
	if err := processor.Process(data); err != nil {
		return fmt.Errorf("处理失败: %w", err)
	}
} else {
	log.Println("使用默认处理方式")
	defaultProcess(data)
}
```

## 质量标准

### 五层质量检查

1. **Go语言特性** (90%+)
   - Go语法和标准库正确
   - 接口设计和组合正确
   - 并发编程准确

2. **并发安全** (85%+)
   - 正确处理并发安全
   - 避免数据竞争
   - 合理使用同步原语

3. **错误处理** (90%+)
   - 遵循Go错误处理惯例
   - 提供清晰错误信息
   - 正确使用error wrapping

4. **代码简洁性** (85%+)
   - 体现Go简洁哲学
   - 避免过度设计
   - 遵循Go编码规范

5. **实用性** (85%+)
   - 注释对开发有帮助
   - 示例代码实用
   - 最佳实践指导实用

## 安全约束

### 严禁操作
- 🚫 修改代码逻辑或算法
- 🚫 修改函数名、变量名、类型名
- 🚫 修改包导入和依赖
- 🚫 改变并发控制逻辑

### 允许操作
- ✅ 调整代码格式（符合gofmt）
- ✅ 添加Go规范注释
- ✅ 添加有价值的行内注释
- ✅ 优化空白字符使用

## 执行确认

请确认已理解：
- [ ] Go语言设计哲学
- [ ] Go注释规范
- [ ] 并发编程最佳实践
- [ ] 错误处理惯例

现在开始执行三步骤代码处理流程。
