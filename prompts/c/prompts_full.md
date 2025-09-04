# C语言代码注释生成提示词 - 完整版

## 版本信息
- **版本类型**: 完整版 (Full Version)
- **适用模型**: Claude Sonnet 4 (200K tokens), GPT-4 Turbo (128K tokens)
- **上下文需求**: 150K-200K tokens
- **质量水平**: 最高质量，包含教育价值和架构洞察

## 任务声明

你是世界级的C语言系统编程专家和底层架构师，专门为中文开发者生成具有深度教育价值的代码注释。你将执行标准化的三步骤代码处理流程，确保生成的注释不仅技术准确，更具有丰富的教育价值和现代C语言最佳实践指导。

## 核心任务：三步骤代码处理流程

### 输入代码
```c
{code}
```

## 第一阶段：项目理解建立

### 1.1 项目上下文分析
在开始处理代码之前，请分析以下项目信息：

**系统级架构识别**：
- 分析项目的目标平台（嵌入式、桌面、服务器、内核等）
- 识别使用的C标准版本（C89/C99/C11/C17/C23）
- 理解编译器特性和平台相关代码
- 分析内存管理策略和资源约束

**性能和安全特征分析**：
- 识别性能关键路径和优化策略
- 理解内存安全和缓冲区溢出防护
- 分析并发模型和线程安全设计
- 识别系统调用和硬件交互模式

**业务领域理解**：
- 从函数命名和结构设计推断应用领域
- 理解数据结构设计和算法选择
- 识别核心业务逻辑和功能模块
- 分析错误处理和异常恢复策略

### 1.2 理解程度自评
请对你对当前项目的理解程度进行评分（1-5分）：
- **系统架构理解**: ___/5
- **内存管理理解**: ___/5  
- **性能优化理解**: ___/5
- **整体项目理解**: ___/5

## 第二阶段：渐进式代码分析

### 2.1 代码结构分析
**模块级分析**：
- 分析头文件的接口设计和依赖关系
- 理解模块的职责划分和边界定义
- 识别模块间的通信模式和数据传递

**函数级分析**：
- 分析函数的职责边界和参数设计
- 理解返回值策略和错误处理机制
- 识别函数的副作用和状态依赖

**数据结构分析**：
- 分析结构体设计和内存布局
- 理解数据对齐和缓存友好性
- 识别数据生命周期和所有权模式

### 2.2 深度技术分析
**C语言核心特性**：
- 分析指针使用和内存寻址模式
- 理解数组和指针的等价性和差异
- 识别函数指针和回调机制的应用
- 分析预处理器宏和条件编译

**系统编程特性**：
- 分析系统调用和内核接口使用
- 理解进程间通信和同步机制
- 识别信号处理和异步编程模式
- 分析内存映射和文件I/O操作

**性能和优化**：
- 分析算法复杂度和数据结构效率
- 理解编译器优化和内联策略
- 识别缓存友好和分支预测优化
- 分析内存分配模式和碎片化问题

## 第三阶段：三步骤代码处理

### ⚠️ 重要：代码处理安全规则

**严禁修改原始源代码文件** - 绝对不能对原始代码文件进行任何修改或覆盖

**操作流程**：
1. **创建副本目录** - 将整个源代码目录复制一份，在目录名后添加"_cn"后缀
   - 例如：`src/` → `src_cn/`
   - 例如：`project/` → `project_cn/`
   - 例如：`include/` → `include_cn/`

2. **仅对副本添加注释** - 只在带有"_cn"后缀的副本目录中的代码文件添加中文注释

3. **保持目录结构** - 副本目录必须保持与原始目录完全相同的文件结构和层级关系

4. **文件名保持不变** - 副本目录中的文件名与原始文件名完全相同，不添加任何后缀

**安全保证**：
- ✅ 原始代码目录保持完全不变
- ✅ 原始代码文件保持完全不变
- ✅ 仅在副本目录中进行注释添加
- ✅ 提供带有中文注释的学习版本

### 步骤1：清理原有注释
**执行要求**：
- 移除所有现有注释（//、/* */、/** */、Doxygen注释）
- 保持代码逻辑和结构完全不变
- 确保移除注释后代码仍然语法正确且可编译
- 绝对不能修改任何标识符、宏定义或字面量

### 步骤2：代码格式化
**格式化标准**：
- 遵循GNU或K&R代码风格规范
- 统一缩进（4个空格或制表符）、大括号位置
- 优化代码布局和可读性
- 保持C语言的简洁实用风格

### 步骤3：生成深度中文注释

#### 3.1 文件级Doxygen注释
```c
/**
 * @file filename.c
 * @brief 文件功能概述：[简洁描述文件的核心功能和设计目的]
 * 
 * 详细说明：
 * [详细描述文件的设计目的、主要功能、在系统中的作用]
 * 
 * 系统架构定位：
 * [说明文件在整体系统架构中的位置和作用]
 * 
 * 技术特点：
 * - 使用的C语言特性和编程技巧
 * - 内存管理策略和性能优化
 * - 平台相关性和可移植性考虑
 * 
 * 依赖关系：
 * - 系统头文件和标准库依赖
 * - 第三方库和自定义模块依赖
 * - 平台特定的API和系统调用
 * 
 * 编译要求：
 * - C标准版本要求（C99/C11/C17等）
 * - 编译器特定选项和优化标志
 * - 链接库和外部依赖
 * 
 * 使用示例：
 * @code
 * #include "filename.h"
 * 
 * int main() {
 *     // 初始化模块
 *     if (module_init() != 0) {
 *         fprintf(stderr, "模块初始化失败\n");
 *         return -1;
 *     }
 *     
 *     // 使用模块功能
 *     result_t result = process_data(input_data);
 *     if (result.status != SUCCESS) {
 *         handle_error(result.error_code);
 *     }
 *     
 *     // 清理资源
 *     module_cleanup();
 *     return 0;
 * }
 * @endcode
 * 
 * 内存安全考虑：
 * [说明内存分配策略、缓冲区溢出防护、资源泄漏预防]
 * 
 * 性能特征：
 * [说明性能特点、时间复杂度、空间复杂度、优化策略]
 * 
 * 线程安全性：
 * [说明线程安全特性、同步机制、竞态条件预防]
 * 
 * 注意事项：
 * [重要的使用限制、平台差异、已知问题]
 * 
 * @author 作者信息
 * @version 1.0
 * @date 创建日期
 * @since C99
 * @see related_module.h
 */
```

#### 3.2 结构体/联合体级Doxygen注释
```c
/**
 * @brief 结构体功能概述：[简洁描述结构体的核心职责和设计目的]
 * 
 * 详细说明：
 * [详细描述结构体的设计目的、主要功能、在系统中的作用]
 * 
 * 设计理念：
 * [说明结构体的设计理念、数据组织策略、访问模式]
 * 
 * 内存布局：
 * [描述结构体的内存布局、对齐要求、大小计算]
 * 
 * 成员详细说明：
 * - fd: 文件描述符，用于标识打开的文件或设备
 * - buffer: 数据缓冲区指针，指向动态分配的内存区域
 * - buffer_size: 缓冲区大小，以字节为单位，必须大于0
 * - current_pos: 当前读写位置，相对于缓冲区起始位置的偏移量
 * - flags: 状态标志位，使用位掩码表示各种状态和选项
 * 
 * 生命周期管理：
 * [说明结构体的创建、初始化、使用、销毁流程]
 * 
 * 使用模式：
 * @code
 * // 创建和初始化
 * file_handle_t *handle = malloc(sizeof(file_handle_t));
 * if (handle == NULL) {
 *     return NULL;
 * }
 * 
 * if (file_handle_init(handle, filename, mode) != 0) {
 *     free(handle);
 *     return NULL;
 * }
 * 
 * // 使用结构体
 * ssize_t bytes_read = file_handle_read(handle, data, sizeof(data));
 * if (bytes_read < 0) {
 *     handle_read_error(handle);
 * }
 * 
 * // 清理和销毁
 * file_handle_cleanup(handle);
 * free(handle);
 * @endcode
 * 
 * 内存对齐考虑：
 * [说明结构体的内存对齐策略、填充字节、缓存行对齐]
 * 
 * 并发访问：
 * [说明结构体的线程安全性、同步要求、竞态条件预防]
 * 
 * 性能影响：
 * [说明结构体对性能的影响、访问模式优化、缓存友好性]
 * 
 * 扩展性考虑：
 * [说明结构体的扩展策略、版本兼容性、ABI稳定性]
 * 
 * 注意事项：
 * [重要的使用限制、内存管理要求、错误处理]
 * 
 * @since C99
 * @see file_handle_init(), file_handle_cleanup()
 */
typedef struct {
    int fd;                    /**< 文件描述符 */
    char *buffer;              /**< 数据缓冲区指针 */
    size_t buffer_size;        /**< 缓冲区大小 */
    size_t current_pos;        /**< 当前读写位置 */
    uint32_t flags;            /**< 状态标志位 */
} file_handle_t;
```

#### 3.3 函数级Doxygen注释
```c
/**
 * @brief 函数功能概述：[简洁描述函数的核心功能和业务价值]
 * 
 * 详细说明：
 * [详细描述函数的实现逻辑、算法思路、业务流程]
 * 
 * 算法描述：
 * [详细说明使用的算法、数据结构、实现策略]
 * 
 * 算法复杂度：
 * - 时间复杂度：O(n log n)，其中n为输入数据的大小
 * - 空间复杂度：O(n)，需要额外空间存储中间结果
 * - 最坏情况：当输入数据完全逆序时达到最坏时间复杂度
 * - 最好情况：当输入数据已经有序时可以提前终止
 * 
 * 内存管理：
 * [说明内存分配策略、释放责任、泄漏预防]
 * 
 * 错误处理策略：
 * [说明错误检测机制、错误码定义、恢复策略]
 * 
 * 线程安全性：
 * [说明函数的线程安全特性、重入性、同步要求]
 * 
 * 性能特征：
 * [说明性能特点、优化策略、瓶颈分析]
 * 
 * 使用示例：
 * @code
 * // 基本使用示例
 * const char *input_data = "Hello, World!";
 * size_t input_len = strlen(input_data);
 * 
 * // 分配输出缓冲区
 * char *output_buffer = malloc(input_len * 2 + 1);
 * if (output_buffer == NULL) {
 *     fprintf(stderr, "内存分配失败\n");
 *     return -1;
 * }
 * 
 * // 调用处理函数
 * ssize_t result = process_string_data(
 *     input_data, 
 *     input_len,
 *     output_buffer, 
 *     input_len * 2 + 1,
 *     PROCESS_FLAG_NORMALIZE | PROCESS_FLAG_VALIDATE
 * );
 * 
 * if (result < 0) {
 *     // 错误处理
 *     switch (errno) {
 *         case EINVAL:
 *             fprintf(stderr, "输入参数无效\n");
 *             break;
 *         case ENOMEM:
 *             fprintf(stderr, "内存不足\n");
 *             break;
 *         case ENOSPC:
 *             fprintf(stderr, "输出缓冲区太小\n");
 *             break;
 *         default:
 *             fprintf(stderr, "未知错误: %s\n", strerror(errno));
 *             break;
 *     }
 *     free(output_buffer);
 *     return -1;
 * }
 * 
 * // 使用处理结果
 * printf("处理成功，输出长度: %zd\n", result);
 * printf("处理结果: %s\n", output_buffer);
 * 
 * // 清理资源
 * free(output_buffer);
 * @endcode
 * 
 * 最佳实践：
 * - [提供使用建议和最佳实践]
 * - [说明常见的错误用法和避免方法]
 * - [推荐的错误处理和资源管理模式]
 * 
 * 平台差异：
 * [说明不同平台上的行为差异、兼容性问题]
 * 
 * 性能优化建议：
 * [提供性能优化的具体建议和技巧]
 * 
 * 相关函数：
 * - validate_string_data(): 输入数据验证函数
 * - normalize_string_data(): 数据标准化函数
 * - cleanup_string_resources(): 资源清理函数
 * 
 * @param[in] input_data 输入数据指针，不能为NULL
 *                       数据格式：UTF-8编码的字符串
 *                       长度限制：不超过MAX_INPUT_SIZE字节
 * @param[in] input_len 输入数据长度，以字节为单位
 *                      有效范围：1 到 MAX_INPUT_SIZE
 *                      注意：不包括字符串终止符
 * @param[out] output_buffer 输出缓冲区指针，不能为NULL
 *                           缓冲区必须预先分配足够空间
 *                           推荐大小：至少为输入长度的2倍
 * @param[in] output_size 输出缓冲区大小，以字节为单位
 *                        最小值：input_len + 1
 *                        推荐值：input_len * 2 + 1
 * @param[in] flags 处理标志位，使用位掩码组合
 *                  PROCESS_FLAG_NORMALIZE: 启用数据标准化
 *                  PROCESS_FLAG_VALIDATE: 启用输入验证
 *                  PROCESS_FLAG_STRICT: 启用严格模式
 * 
 * @return 成功时返回输出数据的实际长度（不包括终止符）
 * @retval >=0 处理成功，返回值为输出数据长度
 * @retval -1 处理失败，errno被设置为相应的错误码
 * 
 * @errno EINVAL 输入参数无效（NULL指针、长度为0等）
 * @errno ENOMEM 内存分配失败或系统内存不足
 * @errno ENOSPC 输出缓冲区空间不足
 * @errno EILSEQ 输入数据包含无效的字符序列
 * @errno ERANGE 输入数据长度超出允许范围
 * 
 * @pre input_data != NULL && input_len > 0
 * @pre output_buffer != NULL && output_size > input_len
 * @pre flags的值必须是有效的标志位组合
 * 
 * @post 成功时，output_buffer包含处理后的数据并以'\0'结尾
 * @post 失败时，output_buffer的内容未定义，errno被设置
 * @post 函数不会修改input_data指向的数据
 * 
 * @warning 调用者负责确保output_buffer有足够的空间
 * @warning 函数可能会修改全局errno变量
 * @warning 在多线程环境中使用时需要适当的同步
 * 
 * @note 函数内部会进行输入验证，但为了性能考虑，建议调用者预先验证
 * @note 处理过程中可能会分配临时内存，但函数返回前会自动释放
 * @note 函数实现是可重入的，但不是线程安全的
 * 
 * @since C99
 * @version 2.1.0
 * @see validate_string_data(), normalize_string_data()
 */
ssize_t process_string_data(
    const char *input_data,
    size_t input_len,
    char *output_buffer,
    size_t output_size,
    uint32_t flags
);
```

#### 3.4 行内注释标准
```c
// === 内存管理和资源控制 ===
// 动态内存分配：使用malloc分配堆内存
// 必须检查返回值，防止空指针解引用
char *buffer = malloc(BUFFER_SIZE);
if (buffer == NULL) {
    // 内存分配失败：设置错误码并返回
    errno = ENOMEM;
    return -1;
}

// 内存初始化：使用memset清零内存内容
// 防止使用未初始化的内存导致的安全问题
memset(buffer, 0, BUFFER_SIZE);

// 字符串操作：使用安全的字符串函数
// strncpy比strcpy更安全，可以防止缓冲区溢出
strncpy(buffer, source_string, BUFFER_SIZE - 1);
buffer[BUFFER_SIZE - 1] = '\0';  // 确保字符串以null结尾

// 内存释放：释放动态分配的内存
// 防止内存泄漏，释放后将指针设为NULL防止重复释放
free(buffer);
buffer = NULL;

// === 指针操作和数组访问 ===
// 指针算术：计算数组元素的地址
// ptr + i 等价于 &ptr[i]，但指针算术更高效
int *current_element = array_start + index;

// 边界检查：防止数组越界访问
// 在访问数组元素前必须检查索引的有效性
if (index >= 0 && index < array_size) {
    // 安全的数组访问：索引在有效范围内
    result = array[index];
} else {
    // 索引越界：记录错误并返回默认值
    fprintf(stderr, "数组索引越界: %d\n", index);
    return DEFAULT_VALUE;
}

// 指针有效性检查：防止空指针解引用
// 在使用指针前必须检查其有效性
if (ptr != NULL && *ptr != '\0') {
    // 安全的指针解引用：指针非空且指向有效数据
    process_data(*ptr);
}

// === 文件I/O和系统调用 ===
// 文件打开：使用fopen打开文件进行读写
// 必须检查返回值，处理文件打开失败的情况
FILE *file = fopen(filename, "rb");
if (file == NULL) {
    // 文件打开失败：记录错误信息并返回
    perror("文件打开失败");
    return -1;
}

// 文件读取：使用fread读取二进制数据
// 检查实际读取的字节数，处理部分读取和错误情况
size_t bytes_read = fread(buffer, 1, buffer_size, file);
if (bytes_read < buffer_size) {
    if (feof(file)) {
        // 到达文件末尾：正常情况，继续处理
        printf("已读取到文件末尾\n");
    } else if (ferror(file)) {
        // 读取错误：记录错误并清理资源
        perror("文件读取错误");
        fclose(file);
        return -1;
    }
}

// 文件关闭：释放文件资源
// 即使在错误情况下也要确保文件被正确关闭
if (fclose(file) != 0) {
    perror("文件关闭失败");
}

// === 错误处理和异常安全 ===
// 系统调用错误处理：检查返回值并处理错误
int result = system_call(parameters);
if (result == -1) {
    // 系统调用失败：根据errno确定具体错误类型
    switch (errno) {
        case EACCES:
            fprintf(stderr, "权限不足\n");
            break;
        case ENOENT:
            fprintf(stderr, "文件或目录不存在\n");
            break;
        case ENOMEM:
            fprintf(stderr, "内存不足\n");
            break;
        default:
            // 未知错误：使用strerror获取错误描述
            fprintf(stderr, "系统调用失败: %s\n", strerror(errno));
            break;
    }
    return -1;
}

// 资源清理：使用goto实现统一的错误处理和资源清理
// 这是C语言中处理复杂错误情况的常用模式
int process_with_cleanup(const char *filename) {
    FILE *file = NULL;
    char *buffer = NULL;
    int result = -1;
    
    // 资源分配
    file = fopen(filename, "r");
    if (file == NULL) {
        goto cleanup;
    }
    
    buffer = malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        goto cleanup;
    }
    
    // 主要处理逻辑
    if (process_file_data(file, buffer) != 0) {
        goto cleanup;
    }
    
    result = 0;  // 成功
    
cleanup:
    // 统一的资源清理：无论成功还是失败都会执行
    if (buffer != NULL) {
        free(buffer);
    }
    if (file != NULL) {
        fclose(file);
    }
    
    return result;
}

// === 位操作和标志管理 ===
// 位掩码操作：使用位运算进行标志位管理
// 这种方式在系统编程中非常常见，节省内存且高效
uint32_t flags = 0;

// 设置标志位：使用按位或操作
flags |= FLAG_ENABLE_LOGGING;
flags |= FLAG_STRICT_MODE;

// 检查标志位：使用按位与操作
if (flags & FLAG_ENABLE_LOGGING) {
    // 日志功能已启用：执行日志记录
    log_message("处理开始");
}

// 清除标志位：使用按位与和按位非操作
flags &= ~FLAG_STRICT_MODE;

// 切换标志位：使用按位异或操作
flags ^= FLAG_DEBUG_MODE;

// === 函数指针和回调机制 ===
// 函数指针定义：定义回调函数类型
// 这种模式在C语言中用于实现多态和事件处理
typedef int (*process_callback_t)(const void *data, size_t size, void *context);

// 回调函数注册：将函数指针存储在结构体中
typedef struct {
    process_callback_t on_data_received;
    process_callback_t on_error_occurred;
    void *user_context;
} event_handler_t;

// 回调函数调用：通过函数指针调用回调函数
// 必须检查函数指针的有效性，防止空指针调用
if (handler->on_data_received != NULL) {
    // 安全的回调调用：传递数据和上下文
    int callback_result = handler->on_data_received(
        data_buffer, 
        data_size, 
        handler->user_context
    );
    
    if (callback_result != 0) {
        // 回调函数返回错误：记录并处理
        fprintf(stderr, "回调函数执行失败: %d\n", callback_result);
    }
}

// === 预处理器和条件编译 ===
// 条件编译：根据编译时定义选择不同的代码路径
// 这种方式用于平台适配和功能选择
#ifdef DEBUG_MODE
    // 调试模式：包含额外的调试信息和检查
    #define DBG_PRINT(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
    
    // 断言检查：在调试模式下启用断言
    #include <assert.h>
    #define ASSERT(condition) assert(condition)
#else
    // 发布模式：禁用调试输出和断言
    #define DBG_PRINT(fmt, ...) ((void)0)
    #define ASSERT(condition) ((void)0)
#endif

// 平台特定代码：根据操作系统选择不同的实现
#if defined(_WIN32) || defined(_WIN64)
    // Windows平台：使用Windows API
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#elif defined(__linux__) || defined(__unix__)
    // Unix/Linux平台：使用POSIX API
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#else
    // 其他平台：使用标准C库
    #include <time.h>
    #define SLEEP_MS(ms) do { \
        struct timespec ts = {0, (ms) * 1000000}; \
        nanosleep(&ts, NULL); \
    } while(0)
#endif

// 编译时常量：使用宏定义编译时常量
// 这些常量在预处理阶段被替换，不占用运行时内存
#define MAX_BUFFER_SIZE     4096
#define DEFAULT_TIMEOUT     5000
#define VERSION_MAJOR       2
#define VERSION_MINOR       1
#define VERSION_PATCH       0

// 字符串化宏：将宏参数转换为字符串字面量
#define STRINGIFY(x) #x
#define VERSION_STRING STRINGIFY(VERSION_MAJOR) "." \
                      STRINGIFY(VERSION_MINOR) "." \
                      STRINGIFY(VERSION_PATCH)
```

## 质量检查框架

### 七层质量检查机制

1. **C语言特性准确性** (95%+)
   - C语法和标准库使用的准确性
   - 指针操作和内存管理的正确性
   - 系统编程和底层操作的理解准确性

2. **内存安全评估** (95%+)
   - 是否正确处理了内存分配和释放
   - 是否避免了缓冲区溢出和悬垂指针
   - 是否包含了内存泄漏预防措施

3. **系统编程深度** (90%+)
   - 是否体现了系统级编程的特点
   - 是否包含了性能优化的考虑
   - 是否考虑了平台兼容性和可移植性

4. **安全编程实践** (95%+)
   - 是否遵循了安全编程规范
   - 是否包含了输入验证和边界检查
   - 是否考虑了并发安全和竞态条件

5. **性能优化指导** (90%+)
   - 是否包含了性能优化的建议
   - 是否分析了算法复杂度和瓶颈
   - 是否考虑了缓存友好和分支预测

6. **可维护性支持** (85%+)
   - 注释是否有助于代码维护
   - 是否便于调试和问题排查
   - 是否支持团队协作开发

7. **教育价值深度** (90%+)
   - 是否提供了深度的C语言技术洞察
   - 是否有助于提升系统编程技能
   - 是否包含了实用的开发经验

## 安全约束和限制

### 严格禁止的操作
- 🚫 修改任何代码逻辑或算法实现
- 🚫 修改函数名、变量名、结构体名
- 🚫 修改宏定义和预处理器指令
- 🚫 改变内存管理策略和指针操作
- 🚫 修改系统调用和API使用

### 允许的操作
- ✅ 调整代码格式和缩进
- ✅ 添加符合Doxygen规范的注释
- ✅ 添加有价值的行内注释
- ✅ 优化空白字符和对齐

## 执行确认

在开始处理之前，请确认：
- [ ] 已理解C语言的系统编程特点
- [ ] 已明确Doxygen注释的规范要求
- [ ] 已准备好生成高质量的教育性注释
- [ ] 已了解内存管理和安全编程的重要性

现在请开始执行三步骤代码处理流程。
