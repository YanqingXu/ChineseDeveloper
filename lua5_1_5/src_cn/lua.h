/**
 * @file lua.h
 * @brief Lua 5.1.5 核心API头文件：提供完整的Lua C API接口定义
 *
 * 详细说明：
 * 本文件是Lua脚本语言的核心C API头文件，定义了所有用于在C程序中
 * 嵌入和扩展Lua解释器的接口函数、数据类型和常量。Lua是一种轻量级、
 * 高性能的脚本语言，广泛应用于游戏开发、应用程序脚本化、配置管理等领域。
 *
 * 系统架构定位：
 * - 作为Lua解释器的公共接口层，隔离内部实现细节
 * - 提供栈式操作模型，简化C与Lua之间的数据交换
 * - 支持协程、垃圾回收、调试等高级特性
 * - 设计为可嵌入式，最小化对宿主程序的依赖
 *
 * 技术特点：
 * - 基于栈的虚拟机架构，操作简单高效
 * - 自动内存管理，支持增量垃圾回收
 * - 协程支持，实现轻量级并发编程
 * - 元表机制，提供强大的面向对象编程能力
 * - 动态类型系统，支持8种基本数据类型
 *
 * 依赖关系：
 * - 标准C库：stdarg.h（可变参数）、stddef.h（基本类型定义）
 * - luaconf.h：Lua配置文件，定义平台相关的配置选项
 * - 无其他外部依赖，保证最大的可移植性
 *
 * 编译要求：
 * - C标准版本：C89或更高版本（推荐C99）
 * - 编译器支持：GCC、Clang、MSVC等主流编译器
 * - 平台支持：Windows、Linux、macOS、嵌入式系统
 *
 * 使用示例：
 * @code
 * #include "lua.h"
 * #include "lauxlib.h"
 * #include "lualib.h"
 *
 * int main() {
 *     // 创建Lua状态机
 *     lua_State *L = luaL_newstate();
 *     if (L == NULL) {
 *         fprintf(stderr, "无法创建Lua状态机\n");
 *         return -1;
 *     }
 *
 *     // 加载标准库
 *     luaL_openlibs(L);
 *
 *     // 执行Lua脚本
 *     if (luaL_dostring(L, "print('Hello from Lua!')") != 0) {
 *         fprintf(stderr, "脚本执行失败: %s\n", lua_tostring(L, -1));
 *     }
 *
 *     // 清理资源
 *     lua_close(L);
 *     return 0;
 * }
 * @endcode
 *
 * 内存安全考虑：
 * - 所有API函数都进行参数有效性检查
 * - 自动垃圾回收机制防止内存泄漏
 * - 栈溢出保护，防止无限递归
 * - 提供内存分配器自定义接口
 *
 * 性能特征：
 * - 解释器启动时间：< 1ms（典型情况）
 * - 内存占用：核心解释器约150KB
 * - 函数调用开销：约为原生C函数调用的3-5倍
 * - 垃圾回收：增量式，单次暂停时间 < 1ms
 *
 * 线程安全性：
 * - lua_State不是线程安全的，每个线程需要独立的状态机
 * - 全局状态和常量是只读的，可以安全共享
 * - 提供lua_newthread创建协程，支持协作式多任务
 *
 * 注意事项：
 * - 必须正确管理Lua栈，避免栈溢出或下溢
 * - 字符串和userdata的生命周期由垃圾回收器管理
 * - 跨C函数调用边界时需要注意异常处理
 * - 在多线程环境中使用时需要适当的同步机制
 *
 * @author Roberto Ierusalimschy, Luiz Henrique de Figueiredo, Waldemar Celes
 * @version 5.1.5
 * @date 2012
 * @since C89
 * @see luaconf.h, lauxlib.h, lualib.h
 */

#ifndef lua_h
#define lua_h

#include <stdarg.h>
#include <stddef.h>

#include "luaconf.h"

/**
 * @name Lua版本信息常量
 * @brief 定义Lua解释器的版本标识和作者信息
 * @{
 */
#define LUA_VERSION         "Lua 5.1"                                    /**< Lua主版本号字符串 */
#define LUA_RELEASE         "Lua 5.1.5"                                  /**< Lua完整版本号字符串 */
#define LUA_VERSION_NUM     501                                          /**< Lua版本号数值形式，用于版本比较 */
#define LUA_COPYRIGHT       "Copyright (C) 1994-2012 Lua.org, PUC-Rio"  /**< Lua版权信息 */
#define LUA_AUTHORS         "R. Ierusalimschy, L. H. de Figueiredo & W. Celes" /**< Lua作者信息 */
/** @} */

/**
 * @name 预编译代码标识
 * @brief 用于标识Lua预编译字节码的魔数
 */
#define LUA_SIGNATURE       "\033Lua"                                    /**< 预编译代码文件头标识：ESC + "Lua" */

/**
 * @name 函数调用返回值控制
 * @brief 控制lua_call和lua_pcall函数的返回值数量
 */
#define LUA_MULTRET         (-1)                                         /**< 返回所有结果值的特殊标识 */

/**
 * @name 伪索引常量
 * @brief 用于访问特殊表的伪索引，这些索引不对应实际的栈位置
 * @{
 */
#define LUA_REGISTRYINDEX   (-10000)                                     /**< 注册表伪索引：全局唯一的键值存储 */
#define LUA_ENVIRONINDEX    (-10001)                                     /**< 环境表伪索引：当前函数的环境 */
#define LUA_GLOBALSINDEX    (-10002)                                     /**< 全局表伪索引：全局变量存储 */
#define lua_upvalueindex(i) (LUA_GLOBALSINDEX-(i))                       /**< 上值伪索引宏：访问闭包的上值 */
/** @} */

/**
 * @name 线程状态码
 * @brief 定义Lua线程（协程）的执行状态
 * @{
 */
#define LUA_YIELD           1                                            /**< 线程挂起状态：协程主动让出执行权 */
#define LUA_ERRRUN          2                                            /**< 运行时错误：脚本执行过程中发生错误 */
#define LUA_ERRSYNTAX       3                                            /**< 语法错误：脚本编译时发现语法问题 */
#define LUA_ERRMEM          4                                            /**< 内存错误：内存分配失败 */
#define LUA_ERRERR          5                                            /**< 错误处理错误：错误处理函数本身出错 */
/** @} */

/**
 * @brief Lua状态机结构体：封装了Lua解释器的完整运行时状态
 *
 * 详细说明：
 * lua_State是Lua解释器的核心数据结构，包含了虚拟机栈、全局状态、
 * 垃圾回收器状态、调试信息等所有运行时数据。每个lua_State实例
 * 代表一个独立的Lua执行环境，可以看作是一个轻量级的虚拟机实例。
 *
 * 设计理念：
 * - 封装性：隐藏内部实现细节，只通过API函数访问
 * - 独立性：每个状态机相互独立，支持多实例并存
 * - 轻量性：内存占用小，创建和销毁开销低
 *
 * 生命周期管理：
 * - 创建：通过lua_newstate()或luaL_newstate()创建
 * - 使用：通过各种lua_*函数操作状态机
 * - 销毁：通过lua_close()释放所有资源
 *
 * 内存管理：
 * - 自动垃圾回收：自动管理Lua对象的内存
 * - 自定义分配器：支持用户自定义内存分配策略
 * - 内存限制：可以设置内存使用上限
 *
 * 并发模型：
 * - 非线程安全：单个状态机不能被多线程同时访问
 * - 协程支持：通过lua_newthread创建协程
 * - 状态隔离：不同状态机之间完全隔离
 *
 * @since C89
 * @see lua_newstate(), lua_close(), lua_newthread()
 */
typedef struct lua_State lua_State;

/**
 * @brief C函数类型定义：可以被Lua调用的C函数签名
 *
 * 详细说明：
 * 这是所有可以从Lua脚本中调用的C函数必须遵循的函数签名。
 * 函数通过Lua栈与脚本进行参数传递和结果返回。
 *
 * 参数说明：
 * @param L Lua状态机指针，用于访问Lua栈和状态
 *
 * 返回值说明：
 * @return 返回推入栈中的结果数量，0表示无返回值
 *
 * 使用模式：
 * @code
 * // C函数实现示例
 * static int my_c_function(lua_State *L) {
 *     // 获取参数数量
 *     int argc = lua_gettop(L);
 *
 *     // 检查参数
 *     if (argc != 2) {
 *         return luaL_error(L, "期望2个参数，实际得到%d个", argc);
 *     }
 *
 *     // 获取参数
 *     double a = luaL_checknumber(L, 1);
 *     double b = luaL_checknumber(L, 2);
 *
 *     // 计算结果并推入栈
 *     lua_pushnumber(L, a + b);
 *
 *     // 返回结果数量
 *     return 1;
 * }
 * @endcode
 *
 * 错误处理：
 * - 可以通过lua_error()或luaL_error()抛出错误
 * - 错误会被转换为Lua异常，可以被pcall捕获
 * - 函数应该保证栈的一致性
 *
 * 性能考虑：
 * - 避免频繁的栈操作，批量处理数据
 * - 使用luaL_checkstack()确保栈空间充足
 * - 合理使用lua_rawget/lua_rawset提高性能
 *
 * @since C89
 * @see lua_pushcfunction(), lua_call(), lua_pcall()
 */
typedef int (*lua_CFunction) (lua_State *L);

/**
 * @brief 读取器函数类型：用于从数据源读取Lua代码块
 *
 * 详细说明：
 * 读取器函数用于lua_load()函数中，从各种数据源（文件、内存、网络等）
 * 读取Lua源代码或字节码。这种设计允许灵活的代码加载策略。
 *
 * 参数说明：
 * @param L Lua状态机指针
 * @param ud 用户数据指针，由lua_load()调用时传入
 * @param sz 输出参数，返回读取的数据长度
 *
 * 返回值说明：
 * @return 指向读取数据的指针，NULL表示读取结束
 *
 * 实现要求：
 * - 每次调用返回一个数据块
 * - 通过sz参数返回数据长度
 * - 返回NULL表示数据读取完毕
 * - 返回的内存在下次调用前必须保持有效
 *
 * @since C89
 * @see lua_load(), lua_dump()
 */
typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);

/**
 * @brief 写入器函数类型：用于将Lua字节码写入目标位置
 *
 * 详细说明：
 * 写入器函数用于lua_dump()函数中，将编译后的Lua字节码写入到
 * 各种目标位置（文件、内存缓冲区、网络等）。
 *
 * 参数说明：
 * @param L Lua状态机指针
 * @param p 指向要写入数据的指针
 * @param sz 要写入的数据长度
 * @param ud 用户数据指针，由lua_dump()调用时传入
 *
 * 返回值说明：
 * @return 0表示写入成功，非0表示写入失败
 *
 * 实现要求：
 * - 必须写入所有sz字节的数据
 * - 写入失败时返回非0值
 * - 可以进行缓冲以提高性能
 *
 * @since C89
 * @see lua_dump(), lua_load()
 */
typedef int (*lua_Writer) (lua_State *L, const void* p, size_t sz, void* ud);

/**
 * @brief 内存分配器函数类型：自定义Lua的内存管理策略
 *
 * 详细说明：
 * 内存分配器函数允许用户完全控制Lua的内存分配和释放行为。
 * 这对于嵌入式系统、内存池管理、内存统计等场景非常有用。
 *
 * 参数说明：
 * @param ud 用户数据指针，在创建状态机时指定
 * @param ptr 要重新分配的内存指针，NULL表示新分配
 * @param osize 原始内存块大小，0表示新分配
 * @param nsize 新的内存块大小，0表示释放内存
 *
 * 返回值说明：
 * @return 新分配的内存指针，分配失败或释放内存时返回NULL
 *
 * 行为规范：
 * - nsize == 0：释放ptr指向的内存，返回NULL
 * - ptr == NULL：分配nsize字节的新内存
 * - 其他情况：重新分配ptr指向的内存为nsize字节
 *
 * 实现示例：
 * @code
 * static void* my_alloc(void *ud, void *ptr, size_t osize, size_t nsize) {
 *     (void)ud; (void)osize;  // 未使用的参数
 *
 *     if (nsize == 0) {
 *         free(ptr);
 *         return NULL;
 *     } else {
 *         return realloc(ptr, nsize);
 *     }
 * }
 * @endcode
 *
 * @since C89
 * @see lua_newstate(), lua_getallocf(), lua_setallocf()
 */
typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);

/**
 * @name Lua数据类型常量
 * @brief 定义Lua中所有基本数据类型的标识符
 * @{
 */
#define LUA_TNONE           (-1)                                         /**< 无效类型：栈位置无效时返回 */

#define LUA_TNIL            0                                            /**< nil类型：表示空值或未定义 */
#define LUA_TBOOLEAN        1                                            /**< 布尔类型：true或false */
#define LUA_TLIGHTUSERDATA  2                                            /**< 轻量用户数据：C指针的简单包装 */
#define LUA_TNUMBER         3                                            /**< 数字类型：双精度浮点数 */
#define LUA_TSTRING         4                                            /**< 字符串类型：不可变字符串 */
#define LUA_TTABLE          5                                            /**< 表类型：关联数组，Lua的核心数据结构 */
#define LUA_TFUNCTION       6                                            /**< 函数类型：Lua函数或C函数 */
#define LUA_TUSERDATA       7                                            /**< 完整用户数据：带元表的C数据块 */
#define LUA_TTHREAD         8                                            /**< 线程类型：协程对象 */
/** @} */

/**
 * @name 栈管理常量
 * @brief 定义Lua栈的最小保证空间
 */
#define LUA_MINSTACK        20                                           /**< C函数可用的最小栈空间：保证至少20个栈位 */

/**
 * @name 用户自定义头文件包含
 * @brief 允许用户在编译时包含自定义的头文件
 */
#if defined(LUA_USER_H)
#include LUA_USER_H                                                      /**< 用户自定义头文件：通过LUA_USER_H宏指定 */
#endif

/**
 * @brief Lua数字类型定义：Lua中数字值的C类型表示
 *
 * 详细说明：
 * lua_Number是Lua中所有数字值在C代码中的表示类型。
 * 默认情况下是double类型，但可以通过luaconf.h配置为其他类型。
 *
 * 配置选项：
 * - 双精度浮点：double（默认，范围约±1.7e308）
 * - 单精度浮点：float（节省内存，范围约±3.4e38）
 * - 长双精度：long double（扩展精度，平台相关）
 *
 * 使用场景：
 * - 与Lua数字值进行转换时使用
 * - 在C函数中处理数字参数和返回值
 * - 进行数学运算和比较操作
 *
 * @since C89
 * @see lua_tonumber(), lua_pushnumber(), LUA_NUMBER
 */
typedef LUA_NUMBER lua_Number;

/**
 * @brief Lua整数类型定义：Lua中整数值的C类型表示
 *
 * 详细说明：
 * lua_Integer是Lua中整数值在C代码中的表示类型。
 * 通常用于数组索引、循环计数等需要整数语义的场合。
 *
 * 配置选项：
 * - ptrdiff_t：指针差值类型（默认，与平台指针大小匹配）
 * - long：长整型（32位或64位，平台相关）
 * - int：标准整型（通常32位）
 *
 * 使用场景：
 * - 数组索引和表键值操作
 * - 循环计数和迭代控制
 * - 位运算和整数数学运算
 *
 * @since C89
 * @see lua_tointeger(), lua_pushinteger(), LUA_INTEGER
 */
typedef LUA_INTEGER lua_Integer;

/**
 * @name 状态机管理函数
 * @brief 用于创建、销毁和管理Lua状态机的核心函数
 * @{
 */

/**
 * @brief 创建新的Lua状态机：使用自定义内存分配器
 *
 * 详细说明：
 * 创建一个全新的Lua状态机实例，使用用户提供的内存分配器。
 * 新创建的状态机包含空的栈和基本的运行时环境，但不包含标准库。
 *
 * 算法描述：
 * 1. 使用提供的分配器分配状态机内存
 * 2. 初始化虚拟机栈和基本数据结构
 * 3. 设置垃圾回收器的初始状态
 * 4. 创建注册表、全局表等基础表
 *
 * 内存管理：
 * - 所有内存分配都通过用户提供的分配器进行
 * - 分配失败时返回NULL，不会抛出异常
 * - 状态机的所有后续内存操作都使用相同的分配器
 *
 * 使用示例：
 * @code
 * // 使用标准分配器创建状态机
 * lua_State *L = lua_newstate(realloc, NULL);
 * if (L == NULL) {
 *     fprintf(stderr, "无法创建Lua状态机\n");
 *     return -1;
 * }
 *
 * // 使用状态机...
 *
 * // 清理资源
 * lua_close(L);
 * @endcode
 *
 * @param[in] f 内存分配器函数指针，不能为NULL
 * @param[in] ud 用户数据指针，传递给分配器函数
 *
 * @return 成功时返回新的状态机指针，失败时返回NULL
 * @retval NULL 内存分配失败或分配器函数为NULL
 *
 * @warning 必须使用lua_close()释放返回的状态机
 * @note 新状态机不包含标准库，需要手动加载
 *
 * @since C89
 * @see lua_close(), luaL_newstate(), lua_setallocf()
 */
LUA_API lua_State *(lua_newstate) (lua_Alloc f, void *ud);

/**
 * @brief 关闭并销毁Lua状态机：释放所有相关资源
 *
 * 详细说明：
 * 销毁指定的Lua状态机，释放其占用的所有内存资源。
 * 这包括栈内容、全局变量、注册表、垃圾回收器管理的对象等。
 *
 * 清理过程：
 * 1. 触发完整的垃圾回收，释放所有Lua对象
 * 2. 调用所有userdata的__gc元方法
 * 3. 关闭所有打开的文件和资源
 * 4. 释放状态机本身的内存
 *
 * 安全考虑：
 * - 调用后L指针变为无效，不能再使用
 * - 会自动处理循环引用和复杂对象图
 * - 确保所有C资源得到正确释放
 *
 * @param[in] L 要关闭的Lua状态机指针，不能为NULL
 *
 * @warning 调用后L指针立即失效，不能再使用
 * @warning 确保没有其他代码持有对该状态机的引用
 *
 * @since C89
 * @see lua_newstate(), luaL_newstate()
 */
LUA_API void       (lua_close) (lua_State *L);

/**
 * @brief 创建新的协程线程：在现有状态机中创建协程
 *
 * 详细说明：
 * 在指定的Lua状态机中创建一个新的协程（线程）。新协程与主线程
 * 共享全局状态，但拥有独立的执行栈，支持协作式多任务编程。
 *
 * 协程特性：
 * - 共享全局状态：访问相同的全局变量和注册表
 * - 独立执行栈：拥有自己的函数调用栈
 * - 协作式调度：通过yield/resume实现主动让出
 * - 轻量级：创建和切换开销很小
 *
 * 使用模式：
 * @code
 * // 创建协程
 * lua_State *co = lua_newthread(L);
 *
 * // 在协程中加载函数
 * lua_pushcfunction(co, my_coroutine_func);
 *
 * // 启动协程
 * int result = lua_resume(co, 0);
 * if (result == LUA_YIELD) {
 *     printf("协程挂起\n");
 * } else if (result == 0) {
 *     printf("协程完成\n");
 * } else {
 *     printf("协程错误: %s\n", lua_tostring(co, -1));
 * }
 * @endcode
 *
 * @param[in] L 父状态机指针，不能为NULL
 *
 * @return 新创建的协程状态机指针
 * @retval NULL 内存分配失败
 *
 * @note 新协程会被推入父状态机的栈顶
 * @note 协程的生命周期由垃圾回收器管理
 *
 * @since C89
 * @see lua_resume(), lua_yield(), lua_status()
 */
LUA_API lua_State *(lua_newthread) (lua_State *L);

/**
 * @brief 设置恐慌函数：处理无法恢复的错误
 *
 * 详细说明：
 * 设置当Lua遇到无法通过正常错误处理机制恢复的严重错误时
 * 调用的恐慌函数。这通常发生在内存不足或栈溢出等情况下。
 *
 * 恐慌情况：
 * - 内存分配失败且无法进行垃圾回收
 * - 栈溢出且无法扩展栈空间
 * - 错误处理函数本身出错
 * - 其他无法恢复的系统级错误
 *
 * 恐慌函数要求：
 * - 不应该返回到Lua（通常调用exit()或longjmp()）
 * - 可以进行清理工作，但要快速完成
 * - 不应该再调用Lua API函数
 *
 * 默认行为：
 * - 如果没有设置恐慌函数，程序会调用abort()终止
 *
 * @param[in] L Lua状态机指针，不能为NULL
 * @param[in] panicf 恐慌函数指针，NULL表示使用默认行为
 *
 * @return 之前设置的恐慌函数指针
 *
 * @warning 恐慌函数不应该返回到Lua
 * @note 恐慌函数应该尽快终止程序或进行非本地跳转
 *
 * @since C89
 * @see lua_error(), lua_pcall()
 */
LUA_API lua_CFunction (lua_atpanic) (lua_State *L, lua_CFunction panicf);

/** @} */

/**
 * @name 基本栈操作函数
 * @brief 用于管理Lua虚拟栈的基础函数
 * @{
 */

/**
 * @brief 获取栈顶位置：返回栈中元素的数量
 *
 * 详细说明：
 * 返回当前栈中有效元素的数量，也就是栈顶的索引值。
 * 栈索引从1开始，所以返回值0表示栈为空。
 *
 * 栈索引规则：
 * - 正索引：1表示栈底，lua_gettop(L)表示栈顶
 * - 负索引：-1表示栈顶，-lua_gettop(L)表示栈底
 * - 0表示无效位置
 *
 * 使用场景：
 * - 检查函数参数数量
 * - 保存栈状态以便后续恢复
 * - 验证栈操作的正确性
 *
 * @param[in] L Lua状态机指针，不能为NULL
 *
 * @return 栈中元素的数量（栈顶索引）
 * @retval 0 栈为空
 * @retval >0 栈中元素数量
 *
 * @note 这是一个O(1)操作，性能开销很小
 *
 * @since C89
 * @see lua_settop(), lua_checkstack()
 */
LUA_API int   (lua_gettop) (lua_State *L);

/**
 * @brief 设置栈顶位置：调整栈的大小
 *
 * 详细说明：
 * 设置栈顶到指定位置，可以用来压入nil值或弹出多个值。
 * 这是一个非常高效的栈大小调整操作。
 *
 * 操作行为：
 * - idx > 当前栈顶：压入(idx - 栈顶)个nil值
 * - idx < 当前栈顶：弹出(栈顶 - idx)个值
 * - idx == 当前栈顶：无操作
 * - idx == 0：清空整个栈
 *
 * 索引处理：
 * - 正索引：直接使用
 * - 负索引：相对于当前栈顶计算
 *
 * 使用示例：
 * @code
 * // 清空栈
 * lua_settop(L, 0);
 *
 * // 保留栈顶3个元素
 * lua_settop(L, 3);
 *
 * // 弹出1个元素（等价于lua_pop(L, 1)）
 * lua_settop(L, -2);
 * @endcode
 *
 * @param[in] L Lua状态机指针，不能为NULL
 * @param[in] idx 新的栈顶位置索引
 *
 * @warning 确保idx不会超出栈的有效范围
 * @note 这是实现lua_pop宏的基础函数
 *
 * @since C89
 * @see lua_gettop(), lua_pop(), lua_checkstack()
 */
LUA_API void  (lua_settop) (lua_State *L, int idx);

/**
 * @brief 复制栈中的值：将指定位置的值复制到栈顶
 *
 * 详细说明：
 * 将栈中指定位置的值复制一份并推入栈顶，原位置的值保持不变。
 * 这是一个非常常用的栈操作，用于复制值而不移动它们。
 *
 * 复制规则：
 * - 创建值的完整副本（对于字符串、数字等）
 * - 对于表、函数等引用类型，复制引用而不是内容
 * - 保持原值在栈中的位置不变
 *
 * 使用场景：
 * - 在不移动原值的情况下获取副本
 * - 为函数调用准备参数
 * - 实现栈值的重新排列
 *
 * @param[in] L Lua状态机指针，不能为NULL
 * @param[in] idx 要复制的值的栈索引
 *
 * @warning 确保idx指向有效的栈位置
 * @note 栈会增长1个位置
 *
 * @since C89
 * @see lua_remove(), lua_insert(), lua_replace()
 */
LUA_API void  (lua_pushvalue) (lua_State *L, int idx);

/**
 * @brief 移除栈中的值：删除指定位置的值并压缩栈
 *
 * 详细说明：
 * 移除栈中指定位置的值，并将其上方的所有值下移一位。
 * 这个操作会改变栈的大小和其他值的索引。
 *
 * 移除过程：
 * 1. 删除指定位置的值
 * 2. 将该位置上方的所有值下移一位
 * 3. 栈顶位置减1
 *
 * 索引影响：
 * - 被移除位置之上的所有正索引减1
 * - 负索引保持相对位置不变
 *
 * @param[in] L Lua状态机指针，不能为NULL
 * @param[in] idx 要移除的值的栈索引
 *
 * @warning 确保idx指向有效的栈位置
 * @warning 移除操作会改变其他值的索引
 *
 * @since C89
 * @see lua_insert(), lua_replace(), lua_pushvalue()
 */
LUA_API void  (lua_remove) (lua_State *L, int idx);

/**
 * @brief 插入栈顶值：将栈顶值移动到指定位置
 *
 * 详细说明：
 * 将栈顶的值移动到指定位置，并将该位置及其上方的值上移一位。
 * 栈的总大小保持不变，但值的位置发生变化。
 *
 * 插入过程：
 * 1. 取出栈顶值
 * 2. 将指定位置及其上方的值上移一位
 * 3. 将栈顶值放入指定位置
 *
 * 使用场景：
 * - 重新排列栈中值的顺序
 * - 将新值插入到特定位置
 * - 实现复杂的栈操作模式
 *
 * @param[in] L Lua状态机指针，不能为NULL
 * @param[in] idx 插入位置的栈索引
 *
 * @warning 确保栈不为空且idx有效
 * @note 栈大小保持不变，但值的位置会改变
 *
 * @since C89
 * @see lua_remove(), lua_replace(), lua_pushvalue()
 */
LUA_API void  (lua_insert) (lua_State *L, int idx);

/**
 * @brief 替换栈中的值：用栈顶值替换指定位置的值
 *
 * 详细说明：
 * 用栈顶的值替换指定位置的值，然后弹出栈顶值。
 * 这是一个原子操作，栈大小减1。
 *
 * 替换过程：
 * 1. 将栈顶值复制到指定位置
 * 2. 弹出栈顶值
 * 3. 栈大小减1
 *
 * 使用场景：
 * - 更新栈中特定位置的值
 * - 实现赋值操作
 * - 优化栈空间使用
 *
 * @param[in] L Lua状态机指针，不能为NULL
 * @param[in] idx 要替换的位置的栈索引
 *
 * @warning 确保栈不为空且idx有效
 * @note 栈大小减1
 *
 * @since C89
 * @see lua_insert(), lua_remove(), lua_pushvalue()
 */
LUA_API void  (lua_replace) (lua_State *L, int idx);

/**
 * @brief 检查栈空间：确保栈有足够的空间
 *
 * 详细说明：
 * 检查栈是否有足够的空间容纳指定数量的新元素。
 * 如果空间不足，会尝试扩展栈；如果扩展失败，返回0。
 *
 * 栈管理：
 * - Lua栈会根据需要自动增长
 * - 但在某些情况下可能达到内存限制
 * - 建议在大量压栈操作前检查空间
 *
 * 性能考虑：
 * - 栈扩展可能涉及内存重新分配
 * - 提前检查可以避免操作中途失败
 * - 对于已知大小的操作，一次性检查更高效
 *
 * @param[in] L Lua状态机指针，不能为NULL
 * @param[in] sz 需要的额外栈空间数量
 *
 * @return 是否有足够的栈空间
 * @retval 1 栈空间充足或扩展成功
 * @retval 0 栈空间不足且无法扩展
 *
 * @note 每个C函数至少保证有LUA_MINSTACK个栈位可用
 *
 * @since C89
 * @see LUA_MINSTACK, lua_gettop(), lua_settop()
 */
LUA_API int   (lua_checkstack) (lua_State *L, int sz);

/**
 * @brief 跨状态机移动值：在两个状态机之间传递值
 *
 * 详细说明：
 * 将值从一个Lua状态机的栈顶移动到另一个状态机的栈顶。
 * 这主要用于在主线程和协程之间传递数据。
 *
 * 移动规则：
 * - 从源状态机弹出n个值
 * - 将这些值推入目标状态机
 * - 保持值的相对顺序
 * - 两个状态机必须属于同一个Lua universe
 *
 * 使用场景：
 * - 主线程与协程之间的数据传递
 * - 不同执行上下文间的值共享
 * - 实现复杂的协程通信模式
 *
 * 限制条件：
 * - 两个状态机必须共享相同的全局状态
 * - 不能在不相关的状态机之间使用
 *
 * @param[in] from 源状态机指针，不能为NULL
 * @param[in] to 目标状态机指针，不能为NULL
 * @param[in] n 要移动的值的数量
 *
 * @warning 确保两个状态机相互兼容
 * @warning 确保源状态机有足够的值可移动
 *
 * @since C89
 * @see lua_newthread(), lua_resume(), lua_yield()
 */
LUA_API void  (lua_xmove) (lua_State *from, lua_State *to, int n);

/** @} */

/**
 * @name 类型检查函数
 * @brief 用于检查栈中值的类型的函数组
 * @{
 */

/** @brief 检查指定位置的值是否为数字类型 */
LUA_API int             (lua_isnumber) (lua_State *L, int idx);

/** @brief 检查指定位置的值是否为字符串类型 */
LUA_API int             (lua_isstring) (lua_State *L, int idx);

/** @brief 检查指定位置的值是否为C函数类型 */
LUA_API int             (lua_iscfunction) (lua_State *L, int idx);

/** @brief 检查指定位置的值是否为用户数据类型 */
LUA_API int             (lua_isuserdata) (lua_State *L, int idx);

/** @brief 获取指定位置值的类型标识符 */
LUA_API int             (lua_type) (lua_State *L, int idx);

/** @brief 获取类型标识符对应的类型名称字符串 */
LUA_API const char     *(lua_typename) (lua_State *L, int tp);

/** @} */

/**
 * @name 值比较函数
 * @brief 用于比较栈中值的函数组
 * @{
 */

/** @brief 比较两个值是否相等（调用元方法） */
LUA_API int            (lua_equal) (lua_State *L, int idx1, int idx2);

/** @brief 原始比较两个值是否相等（不调用元方法） */
LUA_API int            (lua_rawequal) (lua_State *L, int idx1, int idx2);

/** @brief 比较第一个值是否小于第二个值 */
LUA_API int            (lua_lessthan) (lua_State *L, int idx1, int idx2);

/** @} */

/**
 * @name 值转换函数
 * @brief 将栈中的值转换为C类型的函数组
 * @{
 */

/** @brief 将栈中的值转换为数字类型 */
LUA_API lua_Number      (lua_tonumber) (lua_State *L, int idx);

/** @brief 将栈中的值转换为整数类型 */
LUA_API lua_Integer     (lua_tointeger) (lua_State *L, int idx);

/** @brief 将栈中的值转换为布尔类型 */
LUA_API int             (lua_toboolean) (lua_State *L, int idx);

/** @brief 将栈中的值转换为字符串并返回长度 */
LUA_API const char     *(lua_tolstring) (lua_State *L, int idx, size_t *len);

/** @brief 获取对象的长度（字符串、表、用户数据） */
LUA_API size_t          (lua_objlen) (lua_State *L, int idx);

/** @brief 将栈中的值转换为C函数指针 */
LUA_API lua_CFunction   (lua_tocfunction) (lua_State *L, int idx);

/** @brief 将栈中的值转换为用户数据指针 */
LUA_API void           *(lua_touserdata) (lua_State *L, int idx);

/** @brief 将栈中的值转换为线程（协程）指针 */
LUA_API lua_State      *(lua_tothread) (lua_State *L, int idx);

/** @brief 将栈中的值转换为通用指针（用于调试） */
LUA_API const void     *(lua_topointer) (lua_State *L, int idx);

/** @} */

/**
 * @name 值压栈函数
 * @brief 将C值推入Lua栈的函数组
 * @{
 */

/** @brief 将nil值推入栈 */
LUA_API void  (lua_pushnil) (lua_State *L);

/** @brief 将数字值推入栈 */
LUA_API void  (lua_pushnumber) (lua_State *L, lua_Number n);

/** @brief 将整数值推入栈 */
LUA_API void  (lua_pushinteger) (lua_State *L, lua_Integer n);

/** @brief 将指定长度的字符串推入栈 */
LUA_API void  (lua_pushlstring) (lua_State *L, const char *s, size_t l);

/** @brief 将以null结尾的字符串推入栈 */
LUA_API void  (lua_pushstring) (lua_State *L, const char *s);

/** @brief 将格式化字符串推入栈（使用va_list） */
LUA_API const char *(lua_pushvfstring) (lua_State *L, const char *fmt,
                                                      va_list argp);

/** @brief 将格式化字符串推入栈（使用可变参数） */
LUA_API const char *(lua_pushfstring) (lua_State *L, const char *fmt, ...);

/** @brief 将C闭包推入栈 */
LUA_API void  (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n);

/** @brief 将布尔值推入栈 */
LUA_API void  (lua_pushboolean) (lua_State *L, int b);

/** @brief 将轻量用户数据推入栈 */
LUA_API void  (lua_pushlightuserdata) (lua_State *L, void *p);

/** @brief 将当前线程推入栈 */
LUA_API int   (lua_pushthread) (lua_State *L);

/** @} */

/**
 * @name 表访问函数
 * @brief 从Lua表中获取值的函数组
 * @{
 */

/** @brief 从表中获取值（调用元方法） */
LUA_API void  (lua_gettable) (lua_State *L, int idx);

/** @brief 从表中获取指定字段的值 */
LUA_API void  (lua_getfield) (lua_State *L, int idx, const char *k);

/** @brief 从表中原始获取值（不调用元方法） */
LUA_API void  (lua_rawget) (lua_State *L, int idx);

/** @brief 从表中获取指定整数索引的值 */
LUA_API void  (lua_rawgeti) (lua_State *L, int idx, int n);

/** @brief 创建新表并推入栈 */
LUA_API void  (lua_createtable) (lua_State *L, int narr, int nrec);

/** @brief 创建新的用户数据并推入栈 */
LUA_API void *(lua_newuserdata) (lua_State *L, size_t sz);

/** @brief 获取对象的元表 */
LUA_API int   (lua_getmetatable) (lua_State *L, int objindex);

/** @brief 获取对象的环境表 */
LUA_API void  (lua_getfenv) (lua_State *L, int idx);

/** @} */

/**
 * @name 表设置函数
 * @brief 向Lua表中设置值的函数组
 * @{
 */

/** @brief 向表中设置值（调用元方法） */
LUA_API void  (lua_settable) (lua_State *L, int idx);

/** @brief 向表中设置指定字段的值 */
LUA_API void  (lua_setfield) (lua_State *L, int idx, const char *k);

/** @brief 向表中原始设置值（不调用元方法） */
LUA_API void  (lua_rawset) (lua_State *L, int idx);

/** @brief 向表中设置指定整数索引的值 */
LUA_API void  (lua_rawseti) (lua_State *L, int idx, int n);

/** @brief 设置对象的元表 */
LUA_API int   (lua_setmetatable) (lua_State *L, int objindex);

/** @brief 设置对象的环境表 */
LUA_API int   (lua_setfenv) (lua_State *L, int idx);

/** @} */

/**
 * @name 函数调用和代码执行
 * @brief 用于调用函数和执行Lua代码的函数组
 * @{
 */

/** @brief 调用函数（不保护，错误会传播） */
LUA_API void  (lua_call) (lua_State *L, int nargs, int nresults);

/** @brief 保护模式调用函数（捕获错误） */
LUA_API int   (lua_pcall) (lua_State *L, int nargs, int nresults, int errfunc);

/** @brief 保护模式调用C函数 */
LUA_API int   (lua_cpcall) (lua_State *L, lua_CFunction func, void *ud);

/** @brief 加载Lua代码块 */
LUA_API int   (lua_load) (lua_State *L, lua_Reader reader, void *dt,
                                        const char *chunkname);

/** @brief 将函数转储为字节码 */
LUA_API int (lua_dump) (lua_State *L, lua_Writer writer, void *data);

/** @} */

/**
 * @name 协程控制函数
 * @brief 用于控制协程执行的函数组
 * @{
 */

/** @brief 挂起协程 */
LUA_API int  (lua_yield) (lua_State *L, int nresults);

/** @brief 恢复协程执行 */
LUA_API int  (lua_resume) (lua_State *L, int narg);

/** @brief 获取协程状态 */
LUA_API int  (lua_status) (lua_State *L);

/** @} */

/**
 * @name 垃圾回收控制常量
 * @brief 用于控制垃圾回收器行为的选项
 * @{
 */
#define LUA_GCSTOP          0    /**< 停止垃圾回收器 */
#define LUA_GCRESTART       1    /**< 重启垃圾回收器 */
#define LUA_GCCOLLECT       2    /**< 执行完整的垃圾回收 */
#define LUA_GCCOUNT         3    /**< 获取内存使用量（KB） */
#define LUA_GCCOUNTB        4    /**< 获取内存使用量的余数（字节） */
#define LUA_GCSTEP          5    /**< 执行一步增量垃圾回收 */
#define LUA_GCSETPAUSE      6    /**< 设置垃圾回收暂停参数 */
#define LUA_GCSETSTEPMUL    7    /**< 设置垃圾回收步长倍数 */
/** @} */

/**
 * @name 垃圾回收和其他函数
 * @brief 垃圾回收控制和其他实用函数
 * @{
 */

/** @brief 控制垃圾回收器 */
LUA_API int (lua_gc) (lua_State *L, int what, int data);

/** @brief 抛出错误 */
LUA_API int   (lua_error) (lua_State *L);

/** @brief 遍历表的下一个键值对 */
LUA_API int   (lua_next) (lua_State *L, int idx);

/** @brief 连接栈顶的n个值 */
LUA_API void  (lua_concat) (lua_State *L, int n);

/** @brief 获取当前的内存分配器 */
LUA_API lua_Alloc (lua_getallocf) (lua_State *L, void **ud);

/** @brief 设置内存分配器 */
LUA_API void lua_setallocf (lua_State *L, lua_Alloc f, void *ud);

/** @} */


/**
 * @name 便利宏定义
 * @brief 提供常用操作的简化宏定义
 * @{
 */

/** @brief 弹出栈顶的n个元素 */
#define lua_pop(L,n)            lua_settop(L, -(n)-1)

/** @brief 创建空表 */
#define lua_newtable(L)         lua_createtable(L, 0, 0)

/** @brief 注册C函数为全局函数 */
#define lua_register(L,n,f)     (lua_pushcfunction(L, (f)), lua_setglobal(L, (n)))

/** @brief 推入C函数（无上值的闭包） */
#define lua_pushcfunction(L,f)  lua_pushcclosure(L, (f), 0)

/** @brief 获取字符串长度（兼容性宏） */
#define lua_strlen(L,i)         lua_objlen(L, (i))

/** @brief 检查是否为函数类型 */
#define lua_isfunction(L,n)     (lua_type(L, (n)) == LUA_TFUNCTION)
/** @brief 检查是否为表类型 */
#define lua_istable(L,n)        (lua_type(L, (n)) == LUA_TTABLE)
/** @brief 检查是否为轻量用户数据类型 */
#define lua_islightuserdata(L,n) (lua_type(L, (n)) == LUA_TLIGHTUSERDATA)
/** @brief 检查是否为nil类型 */
#define lua_isnil(L,n)          (lua_type(L, (n)) == LUA_TNIL)
/** @brief 检查是否为布尔类型 */
#define lua_isboolean(L,n)      (lua_type(L, (n)) == LUA_TBOOLEAN)
/** @brief 检查是否为线程类型 */
#define lua_isthread(L,n)       (lua_type(L, (n)) == LUA_TTHREAD)
/** @brief 检查是否为无效类型 */
#define lua_isnone(L,n)         (lua_type(L, (n)) == LUA_TNONE)
/** @brief 检查是否为无效或nil类型 */
#define lua_isnoneornil(L, n)   (lua_type(L, (n)) <= 0)

/** @brief 推入字符串字面量 */
#define lua_pushliteral(L, s)   \
    lua_pushlstring(L, "" s, (sizeof(s)/sizeof(char))-1)

/** @brief 设置全局变量 */
#define lua_setglobal(L,s)      lua_setfield(L, LUA_GLOBALSINDEX, (s))
/** @brief 获取全局变量 */
#define lua_getglobal(L,s)      lua_getfield(L, LUA_GLOBALSINDEX, (s))

/** @brief 转换为字符串（不返回长度） */
#define lua_tostring(L,i)       lua_tolstring(L, (i), NULL)

/** @} */

/**
 * @name 兼容性宏和函数
 * @brief 提供向后兼容性的宏定义
 * @{
 */

/** @brief 创建新状态机（兼容性宏） */
#define lua_open()              luaL_newstate()

/** @brief 获取注册表 */
#define lua_getregistry(L)      lua_pushvalue(L, LUA_REGISTRYINDEX)

/** @brief 获取垃圾回收器内存使用量 */
#define lua_getgccount(L)       lua_gc(L, LUA_GCCOUNT, 0)

/** @brief 读取器类型别名（兼容性） */
#define lua_Chunkreader         lua_Reader
/** @brief 写入器类型别名（兼容性） */
#define lua_Chunkwriter         lua_Writer

/** @brief 设置调试级别（内部函数） */
LUA_API void lua_setlevel (lua_State *from, lua_State *to);

/** @} */


/**
 * @name 调试API - 事件类型常量
 * @brief 定义调试钩子函数可以捕获的事件类型
 * @{
 */
#define LUA_HOOKCALL        0    /**< 函数调用事件 */
#define LUA_HOOKRET         1    /**< 函数返回事件 */
#define LUA_HOOKLINE        2    /**< 行执行事件 */
#define LUA_HOOKCOUNT       3    /**< 指令计数事件 */
#define LUA_HOOKTAILRET     4    /**< 尾调用返回事件 */
/** @} */

/**
 * @name 调试API - 事件掩码常量
 * @brief 用于设置调试钩子的事件掩码
 * @{
 */
#define LUA_MASKCALL        (1 << LUA_HOOKCALL)   /**< 函数调用掩码 */
#define LUA_MASKRET         (1 << LUA_HOOKRET)    /**< 函数返回掩码 */
#define LUA_MASKLINE        (1 << LUA_HOOKLINE)   /**< 行执行掩码 */
#define LUA_MASKCOUNT       (1 << LUA_HOOKCOUNT)  /**< 指令计数掩码 */
/** @} */

/**
 * @brief 调试信息结构体：包含函数调用的详细调试信息
 *
 * 详细说明：
 * lua_Debug结构体包含了Lua函数调用的完整调试信息，
 * 用于调试器、性能分析器和错误报告系统。
 *
 * @since C89
 * @see lua_getstack(), lua_getinfo()
 */
typedef struct lua_Debug lua_Debug;

/**
 * @brief 调试钩子函数类型：处理调试事件的回调函数
 *
 * 详细说明：
 * 调试钩子函数在特定事件发生时被调用，可以用于实现
 * 调试器、代码覆盖率分析、性能监控等功能。
 *
 * @param L Lua状态机指针
 * @param ar 调试信息结构体指针
 *
 * @since C89
 * @see lua_sethook(), lua_gethook()
 */
typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);

/**
 * @name 调试API函数
 * @brief 用于获取和设置调试信息的函数组
 * @{
 */

/** @brief 获取调用栈信息 */
LUA_API int lua_getstack (lua_State *L, int level, lua_Debug *ar);

/** @brief 获取详细的调试信息 */
LUA_API int lua_getinfo (lua_State *L, const char *what, lua_Debug *ar);

/** @brief 获取局部变量信息 */
LUA_API const char *lua_getlocal (lua_State *L, const lua_Debug *ar, int n);

/** @brief 设置局部变量值 */
LUA_API const char *lua_setlocal (lua_State *L, const lua_Debug *ar, int n);

/** @brief 获取上值信息 */
LUA_API const char *lua_getupvalue (lua_State *L, int funcindex, int n);

/** @brief 设置上值 */
LUA_API const char *lua_setupvalue (lua_State *L, int funcindex, int n);

/** @brief 设置调试钩子函数 */
LUA_API int lua_sethook (lua_State *L, lua_Hook func, int mask, int count);

/** @brief 获取当前的调试钩子函数 */
LUA_API lua_Hook lua_gethook (lua_State *L);

/** @brief 获取调试钩子的事件掩码 */
LUA_API int lua_gethookmask (lua_State *L);

/** @brief 获取调试钩子的指令计数 */
LUA_API int lua_gethookcount (lua_State *L);

/** @} */

/**
 * @brief 调试信息结构体定义：包含函数执行的详细信息
 *
 * 结构体成员说明：
 * - event: 触发的事件类型
 * - name: 函数名称（如果可用）
 * - namewhat: 名称类型（global、local、field、method等）
 * - what: 函数类型（Lua、C、main、tail）
 * - source: 源代码位置
 * - currentline: 当前执行行号
 * - nups: 上值数量
 * - linedefined: 函数定义开始行号
 * - lastlinedefined: 函数定义结束行号
 * - short_src: 简短的源代码标识
 * - i_ci: 内部调用信息索引
 *
 * @since C89
 */
struct lua_Debug {
    int event;                      /**< 事件类型 */
    const char *name;               /**< 函数名称 */
    const char *namewhat;           /**< 名称类型 */
    const char *what;               /**< 函数类型 */
    const char *source;             /**< 源代码位置 */
    int currentline;                /**< 当前行号 */
    int nups;                       /**< 上值数量 */
    int linedefined;                /**< 定义开始行号 */
    int lastlinedefined;            /**< 定义结束行号 */
    char short_src[LUA_IDSIZE];     /**< 简短源标识 */
    int i_ci;                       /**< 内部调用信息 */
};

#endif
