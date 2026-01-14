add_library(encrypt STATIC src/encrypt.cpp
)
add_library(decrypt STATIC src/decrypt.cpp
)
target_include_directories(decrypt PUBLIC inc)
target_include_directories(encrypt PUBLIC inc)

target_link_libraries(decrypt PRIVATE utils)
target_link_libraries(encrypt PRIVATE utils)
