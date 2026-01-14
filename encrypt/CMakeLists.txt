add_library(encrypt
        src/encrypt.cpp
)
target_include_directories(encrypt PUBLIC include)
target_link_libraries(encrypt PUBLIC utils)