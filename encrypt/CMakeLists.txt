add_library(encrypt
        src/encrypt.cpp
)
target_include_directories(encrypt PUBLIC inc)
target_link_libraries(encrypt PUBLIC utils)