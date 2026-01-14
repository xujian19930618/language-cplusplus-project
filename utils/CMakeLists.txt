add_library(utils
        src/utils.cpp
        inc/utils.h
)

target_include_directories(utils PUBLIC inc)

find_package(OpenSSL REQUIRED)

target_link_libraries(utils PUBLIC openssl::openssl)