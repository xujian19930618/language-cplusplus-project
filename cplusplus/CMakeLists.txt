
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
        study/class_oop/Box.h
        study/class_oop/class_test.cpp
        study/class_oop/class_test.h
        study/class_oop/Shape.cpp
        study/class_oop/Shape.h
)
target_include_directories(cplusplus PUBLIC inc study)