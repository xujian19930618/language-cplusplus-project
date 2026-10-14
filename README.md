
# C++ 项目 - 现代CMake构建实践

一个使用现代CMake和Conan进行构建的C++项目，包含JNI接口、加密解密功能和学习代码示例。

## 项目特性

- **现代CMake**: 使用CMake 3.20+，遵循现代最佳实践
- **依赖管理**: 使用Conan进行C++依赖管理
- **JNI集成**: Java Native Interface支持
- **加密功能**: OpenSSL集成
- **模块化设计**: 清晰的模块分离和依赖管理
- **跨平台**: 支持macOS、Linux和Windows

## 项目结构

```
├── CMakeLists.txt          # 主构建文件
├── conanfile.py           # Conan依赖配置
├── src/                   # 主程序源代码
│   └── main.cpp
├── utils/                 # 工具库
│   ├── CMakeLists.txt
│   ├── inc/
│   └── src/
├── jni_crypto/            # 加密解密模块
│   ├── CMakeLists.txt
│   ├── inc/
│   └── src/
├── jni_agent/             # JNI代理模块
│   ├── CMakeLists.txt
│   ├── inc/
│   ├── src/
│   └── jni/
├── jni_keygen/            # 密钥生成工具
│   ├── CMakeLists.txt
│   ├── keygen.cpp
│   └── verify.cpp
├── cplusplus/             # C++学习代码
│   ├── CMakeLists.txt
│   ├── inc/
│   ├── src/
│   └── study/             # 学习示例
└── build/                 # 构建输出目录
    ├── bin/               # 可执行文件
    └── lib/               # 库文件
```

## 构建要求

- CMake 3.20+
- Conan 2.x
- C++20 兼容编译器
- OpenSSL 开发库
- JDK (用于JNI)

## 快速开始

### 1. 安装依赖

```bash
# 安装Conan依赖
conan install . -g CMakeDeps -g CMakeToolchain --build=missing
```

### 2. 配置项目

```bash
# 配置构建
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```

### 3. 构建项目

```bash
# 构建所有目标
cmake --build build
```

### 4. 运行程序

```bash
# 运行主程序
./build/bin/language-cplusplus-project

# 运行密钥生成工具
./build/bin/keygen

# 运行验证工具
./build/bin/verify
```

## 模块说明

### utils (工具库)
核心工具函数库，提供基础功能支持。

### jni_crypto (加密模块)
- **encrypt**: 加密功能库
- **decrypt**: 解密功能库

### jni_agent (JNI代理)
提供Java Native Interface功能，支持Java与C++互操作。

### jni_keygen (密钥工具)
- **keygen**: 密钥生成可执行程序
- **verify**: 密钥验证可执行程序

### cplusplus (学习代码)
C++学习示例代码，包含：
- 基础语法 (变量、控制流、函数、数组字符串)
- 指针与引用
- 结构体、联合体、枚举
- 类与面向对象编程
- STL与模板

## 开发最佳实践

### CMake规范
- 使用现代CMake语法 (`target_*` 命令)
- 正确设置包含目录和链接依赖
- 使用 `PUBLIC`、`PRIVATE`、`INTERFACE` 正确区分依赖范围
- 设置适当的C++标准

### 代码组织
- 头文件放在 `inc/` 目录
- 源文件放在 `src/` 目录
- 每个模块使用独立的CMakeLists.txt
- 使用命名空间避免命名冲突

### 依赖管理
- 使用Conan管理第三方依赖
- 正确配置 `find_package` 和目标链接
- 区分构建时和安装时包含路径

## 构建选项

| 选项 | 描述 | 默认值 |
|------|------|--------|
| `CMAKE_BUILD_TYPE` | 构建类型 (Debug/Release) | Release |
| `CMAKE_CXX_STANDARD` | C++标准版本 | 20 |
| `CMAKE_INSTALL_PREFIX` | 安装路径 | /usr/local |

## 故障排除

### 常见问题

1. **OpenSSL未找到**
   ```bash
   conan install . --build=missing
   ```

2. **JNI头文件未找到**
   - 确保安装了JDK
   - 检查 `JAVA_HOME` 环境变量

3. **构建失败**
   ```bash
   rm -rf build
   conan install . -g CMakeDeps -g CMakeToolchain --build=missing
   cmake -S . -B build -G Ninja
   cmake --build build
   ```

## 贡献

欢迎提交Issue和Pull Request！

## 许可证
```
[请添加适当的许可证信息]
│
├── 06_Modern_CPP/           # C++11/14/17 新特性
│   ├── auto_decltype.cpp
│   ├── smart_pointer.cpp
│   ├── lambda_example.cpp
│   ├── move_semantics.cpp
│   └── threading.cpp        # std::thread, mutex
│
├── 07_Embedded_Style/       # 嵌入式风格 C++
│   ├── gpio_class.cpp       # 封装 GPIO
│   ├── uart_class.cpp       # 封装 UART
│   ├── timer_class.cpp      # 定时器封装
│   └── memory_pool.cpp      # 静态内存池
│
├── inc/                 # 公共头文件（可选）
│   └── common.h
│
├── CMakeLists.txt           # 构建配置
└── README.md
```


#### C/C++


| **分类** | **学习内容**                 | **为什么重要**         |
| -------- | ---------------------------- | ---------------------- |
| 语言基础 | 变量、指针、引用、函数、数组 | 掌握 C/C++ 基本语法    |
| 内存管理 | 栈、堆、智能指针、内存对齐   | 理解原生程序的内存行为 |
| 面向对象 | 类、继承、多态、虚函数       | 掌握 C++ 的对象模型    |
| C++ 进阶 | 模板、移动语义、完美转发     | 理解现代 C++           |
| STL      | 容器、算法、迭代器           | 提高开发效率           |
| 并发编程 | 线程、互斥锁、原子操作       | 为后续系统编程打基础   |

#### Cmake

| **分类**                 | **主要学习内容**                        |
| ------------------------ | --------------------------------------- |
| `basic/`                 | `project()`、`cmake_minimum_required()` |
| `variables/`             | 变量、缓存变量、作用域                  |
| `properties/`            | `RUNTIME_OUTPUT_DIRECTORY` 等属性       |
| `targets/`               | `add_executable()`、目标属性            |
| `libraries/`             | 静态库、动态库、目标链接                |
| `include_directories/`   | `target_include_directories()`          |
| `compile_options/`       | `target_compile_options()`、编译宏      |
| `link_options/`          | `target_link_options()`、链接参数       |
| `generator_expressions/` | `$<...>` 生成器表达式                   |
| `find_package/`          | 查找和使用第三方依赖                    |
| `install/`               | 安装目标、安装头文件                    |
| `export/`                | 导出目标、创建可复用的库                |
| `toolchain/`             | 工具链文件                              |
| `presets/`               | `CMakePresets.json`                     |
| `cross_compile/`         | 交叉编译                                |
| `custom_commands/`       | 自定义构建步骤                          |


#### JNI


| **分类** | **学习内容**                                             |
| -------- | -------------------------------------------------------- |
| 基础调用 | Java 调用 C/C++ 方法                                     |
| 动态注册 | `RegisterNatives()`                                      |
| 生命周期 | `JNI_OnLoad()`、`JNI_OnUnload()`                         |
| 数据类型 | Java 基本类型与 JNI 类型的对应关系                       |
| 字符串   | `GetStringUTFChars()`、`NewStringUTF()` 等               |
| 数组     | Java 数组与原生数组之间的数据交换                        |
| 对象     | 创建 Java 对象、调用 Java 方法                           |
| 引用管理 | Local Reference、Global Reference、Weak Global Reference |
| 异常     | Java 异常与原生代码之间的交互                            |
| 线程     | `JNIEnv*` 的线程约束、原生线程附加与分离                 |
| 性能     | 减少不必要的数据复制、批量调用                           |

#### System

| **分类** | **学习内容**                   |
| -------- | ------------------------------ |
| 进程     | 进程创建、退出、进程间关系     |
| 线程     | 线程创建、退出、线程安全       |
| 同步     | 互斥锁、条件变量、原子操作     |
| 文件     | 文件描述符、文件读写、文件权限 |
| 网络     | TCP、UDP、Socket 编程          |
| 动态库   | 共享库的加载、符号查找         |
| 内存映射 | `mmap()` 等机制                |
| IPC      | 管道、共享内存、消息队列       |


#### 动态库、静态库与 ABI

* .a、.lib、.so、.dylib 的区别。
* 静态链接与动态链接。
* 符号导出与符号可见性。
* 动态库依赖关系。
* C/C++ ABI。
* C++ 名字修饰（Name Mangling）。
* 跨编译器、跨运行库的兼容性。
* 动态库版本管理。


#### 密码学与安全开发
| **分类**   | **学习内容**           |
| ---------- | ---------------------- |
| 随机数     | 安全随机数生成器       |
| 哈希       | SHA-256 等             |
| 消息认证   | HMAC                   |
| 对称加密   | AES-GCM 等认证加密模式 |
| 非对称密码 | RSA、椭圆曲线密码学    |
| 密钥生成   | 密钥生成、编码和导出   |
| 数字签名   | 签名、验签             |
| 证书       | X.509 证书基础         |
| 密钥存储   | 密钥保护、文件权限     |
| 安全内存   | 敏感数据生命周期管理   |

#### 单元测试与调试工具
| **工具或技术**             | **作用**                          |
| -------------------------- | --------------------------------- |
| GoogleTest                 | 编写 C++ 单元测试                 |
| AddressSanitizer           | 检测常见内存错误                  |
| UndefinedBehaviorSanitizer | 检测部分未定义行为                |
| ThreadSanitizer            | 检测部分数据竞争                  |
| GDB                        | 调试原生程序                      |
| LLDB                       | 调试原生程序，尤其适合 Apple 平台 |
| Valgrind                   | 内存检查等动态分析                |
| Benchmark                  | 测量代码性能                      |