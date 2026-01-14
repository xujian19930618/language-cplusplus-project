add_library(utils
        src/utils.cpp
        include/utils.h
)

target_include_directories(utils PUBLIC include)

find_package(OpenSSL REQUIRED)

target_link_libraries(utils PUBLIC openssl::openssl)