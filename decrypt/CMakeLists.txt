add_library(decrypt
        src/decrypt.cpp
)
target_include_directories(decrypt PUBLIC inc)
target_link_libraries(decrypt PUBLIC utils)