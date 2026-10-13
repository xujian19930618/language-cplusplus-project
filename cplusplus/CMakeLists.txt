
add_library(cplusplus STATIC
        study/basics/arrays_strings.cpp
        study/basics/functions.cpp
        study/basics/control_flow.cpp
        study/basics/variables.cpp
        study/pointers/pointer_array.cpp
        study/pointers/pointers.cpp
        study/pointers/pointer_function.cpp
        study/pointers/references.cpp
        study/struct_enum/struct_example.cpp
        study/struct_enum/union_example.cpp
        study/struct_enum/enum_example.cpp
        study/class_oop/Box.cpp
        study/class_oop/class_test.cpp
        study/class_oop/Shape.cpp
)
target_include_directories(cplusplus PUBLIC inc study/class_oop)

set_target_properties(cplusplus PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 共享库输出目录（macOS/Linux）
        RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 可执行文件/Windows 共享库输出目录
        ARCHIVE_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 静态库输出目录（可选）
)