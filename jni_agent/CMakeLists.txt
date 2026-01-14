add_library(agent SHARED
        src/Agent.cpp
        inc/Agent.h
        jni/HelloJni.cpp
)
#target_include_directories(agent PUBLIC inc)

find_package(JNI REQUIRED)
target_include_directories(agent
        PUBLIC inc
        PRIVATE ${JNI_INCLUDE_DIRS}
)

target_link_libraries(agent PRIVATE utils decrypt)
# ${JNI_LIBRARIES}