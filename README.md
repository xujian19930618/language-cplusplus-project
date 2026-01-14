

## JNI

### utils 工具类
### encrypt 加密模块
### decrypt 解密模块
### agent   Agent模块
### app    接口调用

### cplusplus c++学习
```c++
	1.	基础语法 → 练习变量、流程控制、函数
	2.	指针与引用 → 手写数组/函数指针
	3.	结构体 & 枚举 → 模拟小模块
	4.	类与 OOP → 封装 GPIO、UART 类
	5.	STL & 模板 → 练习数据结构、算法
	6.	现代 C++ → Lambda、智能指针、线程
	7.	嵌入式实践 → 完整 MCU 驱动类封装
```
```bash
├── 01_Basics/               # 基础语法
│   ├── variables.cpp        # 变量、常量、作用域
│   ├── control_flow.cpp     # if, switch, for, while
│   ├── functions.cpp        # 函数、默认参数、重载
│   └── arrays_strings.cpp   # 数组与字符串
│
├── 02_Pointers_References/  # 指针与引用
│   ├── pointers.cpp
│   ├── pointer_array.cpp
│   ├── pointer_function.cpp
│   └── references.cpp
│
├── 03_Struct_Enum/          # 结构体、联合体、枚举
│   ├── struct_example.cpp
│   ├── union_example.cpp
│   └── enum_example.cpp
│
├── 04_Class_OOP/            # 类与面向对象
│   ├── class_basics.cpp     # 类定义、对象
│   ├── constructors.cpp     # 构造函数、析构函数
│   ├── inheritance.cpp      # 继承与派生类
│   ├── polymorphism.cpp     # 虚函数、多态
│   └── operator_overload.cpp# 运算符重载
│
├── 05_STL_Template/         # STL 与模板
│   ├── vector_example.cpp
│   ├── map_set_example.cpp
│   ├── algorithms.cpp       # sort, find, count
│   └── templates.cpp        # 函数模板、类模板
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
├── include/                 # 公共头文件（可选）
│   └── common.h
│
├── CMakeLists.txt           # 构建配置
└── README.md
```