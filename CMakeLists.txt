cmake_minimum_required(VERSION 4.0)
project(language-cplusplus-project)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(utils)
add_subdirectory(crypto)
add_subdirectory(agent)
add_subdirectory(app)
add_subdirectory(cplusplus)

find_package(OpenSSL REQUIRED)

# 最终可执行文件
add_executable(exec
        $<TARGET_OBJECTS:utils>
        $<TARGET_OBJECTS:encrypt>
        $<TARGET_OBJECTS:decrypt>
        $<TARGET_OBJECTS:agent>
#        $<TARGET_OBJECTS:cplusplus>
        $<TARGET_OBJECTS:algjar>
)

# 链接第三方库
target_link_libraries(exec PRIVATE openssl::openssl)

# 防止 “cannot determine linker language”
set_target_properties(exec PROPERTIES LINKER_LANGUAGE CXX)

#add_library(UsbDriver SHARED
#        Src/UsbDriver.cpp
#        Src/Logger.cpp
#        Src/JVMMonitor.cpp
#        Src/JClassUtil.cpp
#        Src/AlgorithmLoader.cpp
#        Src/PackDecryptorBuffer.cpp
#        Src/PackEncryptor.cpp
#        Src/Base64Util.cpp
#        Src/VerifyFile.cpp
#        src/CoreLogic.cpp
#)
#add_executable(jni main.cpp
#        encrypt/src/Encryptor.cpp
#        encrypt/inc/Encryptor.h
#        decrypt/src/Decryptor.cpp
#        decrypt/inc/Decryptor.h
#        agent/src/agentService.cpp
#        agent/inc/agentService.h
#        app/main.cpp
#)


## 为了将最终产物复制到指定位置
set(FINAL_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY ${FINAL_OUTPUT_DIR})


# 2. 配置目标产物的输出目录（适用于 add_library()/add_executable() 定义的目标）
# 方式1：全局配置（所有目标的产物都生成到 FINAL_OUTPUT_DIR）
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR})  # 共享库（.dylib/.so）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR})  # 静态库（.a/.lib）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR})  # 可执行文件（.exe）

# 方式2：单独配置 UsbDriver 目标（仅该目标的产物生成到自定义目录，推荐）
set_target_properties(agent PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 共享库输出目录（macOS/Linux）
        RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 可执行文件/Windows 共享库输出目录
        ARCHIVE_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}  # 静态库输出目录（可选）
)

# 配置 utils 静态库
set_target_properties(utils PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}
)
# 配置 decrypt 静态库
set_target_properties(decrypt PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}
)
# 配置 decrypt 静态库
set_target_properties(encrypt PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}
)
# 配置 app 可执行文件
#set_target_properties(algjar PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}
#)
# 配置 exec 可执行文件
set_target_properties(exec PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${FINAL_OUTPUT_DIR}
)

# 3. 可选：配置 Debug/Release 模式的产物输出目录（避免产物混淆）
set_target_properties(agent PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY_DEBUG ${FINAL_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_RELEASE ${FINAL_OUTPUT_DIR}
)
