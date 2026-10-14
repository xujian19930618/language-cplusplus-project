
add_library(cplusplus STATIC
        src/basics/pointers/pointer_array.cpp
        src/basics/pointers/pointers.cpp
        src/basics/pointers/pointer_function.cpp
        src/basics/pointers/references.cpp
        src/oop/class/Box.cpp
        src/oop/class/class_test.cpp
        src/oop/class/Shape.cpp
)
target_include_directories(cplusplus PUBLIC inc study/class_oop)

set_target_properties(cplusplus PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 共享库输出目录（macOS/Linux）
        RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 可执行文件/Windows 共享库输出目录
        ARCHIVE_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 静态库输出目录（可选）
)