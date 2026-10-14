
add_executable(keygen keygen.cpp)
target_link_libraries(keygen PRIVATE utils encrypt)

add_executable(verify verify.cpp)
target_link_libraries(verify PRIVATE utils decrypt)


