add_library(agent SHARED
        src/Agent.cpp
        include/Agent.h
        jni/HelloJni.cpp
)
#target_include_directories(agent PUBLIC include)

find_package(JNI REQUIRED)
target_include_directories(agent
        PUBLIC include
        PRIVATE ${JNI_INCLUDE_DIRS}
)

target_link_libraries(agent PUBLIC ${JNI_LIBRARIES} utils encrypt decrypt)