cmake_minimum_required(VERSION 3.31.10)
project(language-cplusplus-project)

set(CMAKE_CXX_STANDARD 20)


### 为了将最终产物复制到指定位置
set(FINAL_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY ${FINAL_OUTPUT_DIR})


## 2. 配置目标产物的输出目录（适用于 add_library()/add_executable() 定义的目标）
## 方式1：全局配置（所有目标的产物都生成到 FINAL_OUTPUT_DIR）
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR})  # 共享库（.dylib/.so）
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR})  # 静态库（.a/.lib）
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR})  # 可执行文件（.exe）

## 方式2：单独配置 UsbDriver 目标（仅该目标的产物生成到自定义目录，推荐）
#set_target_properties(agent PROPERTIES
#        LIBRARY_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 共享库输出目录（macOS/Linux）
#        RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 可执行文件/Windows 共享库输出目录
#        ARCHIVE_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 静态库输出目录（可选）
#)

## 3. 可选：配置 Debug/Release 模式的产物输出目录（避免产物混淆）
#set_target_properties(agent PROPERTIES
#        LIBRARY_OUTPUT_DIRECTORY_DEBUG ${FINAL_OUTPUT_DIR}
#        LIBRARY_OUTPUT_DIRECTORY_RELEASE ${FINAL_OUTPUT_DIR}
#)

add_subdirectory(cplusplus)


add_executable( cplusplus1
        cplusplus/src/main.cpp
)
target_link_libraries(cplusplus1 PRIVATE cplusplus)

# 配置 cplusplus 可执行文件
set_target_properties(cplusplus1 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}
)

## 配置 exec 可执行文件
#set_target_properties(exec PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}
#)