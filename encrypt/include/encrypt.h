//
// Created by 徐剑 on 2025/11/6.
//

#ifndef JNI_PACKENCRYPTOR_H
#define JNI_PACKENCRYPTOR_H

#pragma once
#include <iostream>

// 函数声明
bool encryptJarToA(const std::string& jarPath,
				   const std::string& publicKeyPath,
				   const std::string& outputPath);

bool encryptJarToA(
		const std::string& jarPath,
		const char* publicKeyData,  // 改为接受密钥数据
		const std::string& outputPath,
		int flag
);

#endif //JNI_PACKENCRYPTOR_H