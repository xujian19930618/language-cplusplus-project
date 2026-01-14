add_library(decrypt
        src/decrypt.cpp
)
target_include_directories(decrypt PUBLIC include)
target_link_libraries(decrypt PUBLIC utils)