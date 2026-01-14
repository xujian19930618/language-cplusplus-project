//
// Created by 胡圣杰 on 2025/6/19.
//
#include "encrypt.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  // 链接 Winsock 库
#else
#include <arpa/inet.h>
#endif

// 读取公钥
EVP_PKEY* loadPublicKey(const std::string& pubkeyPath) {
    FILE* fp = fopen(pubkeyPath.c_str(), "r");
    if (!fp) {
        std::cerr << "Failed to open public key file: " << pubkeyPath << std::endl;
        return nullptr;
    }
    EVP_PKEY* pubkey = PEM_read_PUBKEY(fp, nullptr, nullptr, nullptr);
    fclose(fp);
    if (!pubkey) std::cerr << "Failed to read public key" << std::endl;
    return pubkey;
}

// 读取文件到内存
static bool readFile(const std::string& path, std::vector<uint8_t>& data) {
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs) return false;
    data.assign(std::istreambuf_iterator<char>(ifs), {});
    return true;
}

// 写入文件
static bool writeFile(const std::string& path, const std::vector<uint8_t>& data) {
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs) return false;
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    return true;
}

// RSA 公钥加密数据（适合加密 AES 密钥）
// 输入：pubkey，明文数据input
// 输出：密文output
bool rsaEncrypt(EVP_PKEY* pubkey, const std::vector<uint8_t>& input, std::vector<uint8_t>& output) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(pubkey, nullptr);
    if (!ctx) return false;
    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    size_t outlen = 0;
    if (EVP_PKEY_encrypt(ctx, nullptr, &outlen, input.data(), input.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    output.resize(outlen);
    if (EVP_PKEY_encrypt(ctx, output.data(), &outlen, input.data(), input.size()) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    output.resize(outlen);
    EVP_PKEY_CTX_free(ctx);
    return true;
}

// AES-256-GCM 加密大文件
// 输入：明文plaintext，密钥key，IV，输出密文ciphertext和认证标签tag
bool aesGcmEncrypt(const std::vector<uint8_t>& plaintext,
                   const std::vector<uint8_t>& key,
                   std::vector<uint8_t>& iv,
                   std::vector<uint8_t>& ciphertext,
                   std::vector<uint8_t>& tag) {
    const int iv_len = 12; // GCM推荐12字节IV
    iv.resize(iv_len);
    if (!RAND_bytes(iv.data(), iv_len)) return false;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) return false;

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    if (EVP_EncryptInit_ex(ctx, nullptr, nullptr, key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    ciphertext.resize(plaintext.size());
    int outlen1 = 0;
    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &outlen1, plaintext.data(), (int)plaintext.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    int outlen2 = 0;
    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + outlen1, &outlen2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    ciphertext.resize(outlen1 + outlen2);

    tag.resize(16); // GCM tag长度16字节
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }

    EVP_CIPHER_CTX_free(ctx);
    return true;
}

// 写入自定义格式文件
// 格式：
// 4字节魔数 'CJAR'
// 1字节版本 1
// 4字节大端uint32 加密的AES密钥长度
// 加密的AES密钥 bytes
// 12字节IV
// 16字节GCM标签
// 剩余为AES加密的数据
bool writeAFile(const std::string& path,
                const std::vector<uint8_t>& encryptedAesKey,
                const std::vector<uint8_t>& iv,
                const std::vector<uint8_t>& tag,
                const std::vector<uint8_t>& encryptedData) {
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs) return false;

    ofs.write("CJAR", 4);
    uint8_t version = 1;
    ofs.write(reinterpret_cast<const char*>(&version), 1);

    uint32_t keylen = htonl((uint32_t)encryptedAesKey.size());
    ofs.write(reinterpret_cast<const char*>(&keylen), 4);

    ofs.write(reinterpret_cast<const char*>(encryptedAesKey.data()), encryptedAesKey.size());
    ofs.write(reinterpret_cast<const char*>(iv.data()), iv.size());
    ofs.write(reinterpret_cast<const char*>(tag.data()), tag.size());
    ofs.write(reinterpret_cast<const char*>(encryptedData.data()), encryptedData.size());

    return true;
}

// 主加密函数，混合加密入口
bool encryptJarToA(const std::string& jarPath,
                   const std::string& publicKeyPath,
                   const std::string& outputPath) {
    // 读JAR文件
    std::vector<uint8_t> jarData;
    if (!readFile(jarPath, jarData)) {
        std::cerr << "Failed to read JAR file: " << jarPath << std::endl;
        return false;
    }

    // 生成随机AES-256密钥
    std::vector<uint8_t> aesKey(32);
    if (!RAND_bytes(aesKey.data(), (int)aesKey.size())) {
        std::cerr << "Failed to generate AES key" << std::endl;
        return false;
    }

    // 读取RSA公钥
    EVP_PKEY* pubkey = loadPublicKey(publicKeyPath);
    if (!pubkey) return false;

    // RSA加密AES密钥
    std::vector<uint8_t> encryptedAesKey;
    if (!rsaEncrypt(pubkey, aesKey, encryptedAesKey)) {
        std::cerr << "Failed to RSA encrypt AES key" << std::endl;
        EVP_PKEY_free(pubkey);
        return false;
    }
    EVP_PKEY_free(pubkey);

    // AES-GCM加密JAR文件数据
    std::vector<uint8_t> iv, ciphertext, tag;
    if (!aesGcmEncrypt(jarData, aesKey, iv, ciphertext, tag)) {
        std::cerr << "AES-GCM encryption failed" << std::endl;
        return false;
    }

    // 写入.a文件
    if (!writeAFile(outputPath, encryptedAesKey, iv, tag, ciphertext)) {
        std::cerr << "Failed to write output file: " << outputPath << std::endl;
        return false;
    }

    // std::cout << "Encryption success!" << std::endl;
    return true;
}


EVP_PKEY* loadPublicKeyFromString(const char* publicKeyData) {
    if (!publicKeyData || *publicKeyData == '\0') {
        std::cerr << "错误: 公钥数据为空" << std::endl;
        return nullptr;
    }

    BIO* bio = BIO_new_mem_buf(publicKeyData, -1);
    if (!bio) {
        std::cerr << "错误: 创建 BIO 失败" << std::endl;
        return nullptr;
    }

    // 使用更通用的方法读取公钥
    EVP_PKEY* pubkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    if (!pubkey) {
        // 兼容性更好的错误处理
        std::cerr << "错误: 加载公钥失败 - 可能原因：" << std::endl;
        std::cerr << "1. 密钥格式不正确（必须是PEM格式）" << std::endl;
        std::cerr << "2. 密钥内容损坏或不完整" << std::endl;
        std::cerr << "3. 使用了不支持的密钥类型" << std::endl;

        // 尝试获取更详细的错误信息
        unsigned long err = 0;
        char err_buf[256] = {0};

        // 兼容不同版本的方法
        while ((err = ERR_get_error()) != 0) {
            ERR_error_string_n(err, err_buf, sizeof(err_buf));
            std::cerr << "OpenSSL 错误: " << err_buf << std::endl;
        }

        // 如果没有获取到错误，输出通用提示
        if (err_buf[0] == '\0') {
            std::cerr << "请检查公钥内容是否以 '-----BEGIN PUBLIC KEY-----' 开头" << std::endl;
        }
    }

    return pubkey;
}

// 主加密函数，混合加密入口
bool encryptJarToA(const std::string& jarPath,
                   const char* publicKeyData,
                   const std::string& outputPath,
                   int flag) {
    // 读JAR文件
    std::vector<uint8_t> jarData;
    if (!readFile(jarPath, jarData)) {
        std::cerr << "Failed to read JAR file: " << jarPath << std::endl;
        return false;
    }

    // 生成随机AES-256密钥
    std::vector<uint8_t> aesKey(32);
    if (!RAND_bytes(aesKey.data(), (int)aesKey.size())) {
        std::cerr << "Failed to generate AES key" << std::endl;
        return false;
    }

    // 读取RSA公钥
    EVP_PKEY* pubkey = loadPublicKeyFromString(publicKeyData);
    if (!pubkey) std::cerr << "Failed to read public key" << std::endl;
    if (!pubkey) return false;

    // RSA加密AES密钥
    std::vector<uint8_t> encryptedAesKey;
    if (!rsaEncrypt(pubkey, aesKey, encryptedAesKey)) {
        std::cerr << "Failed to RSA encrypt AES key" << std::endl;
        EVP_PKEY_free(pubkey);
        return false;
    }
    EVP_PKEY_free(pubkey);

    // AES-GCM加密JAR文件数据
    std::vector<uint8_t> iv, ciphertext, tag;
    if (!aesGcmEncrypt(jarData, aesKey, iv, ciphertext, tag)) {
        std::cerr << "AES-GCM encryption failed" << std::endl;
        return false;
    }

    // 写入.a文件
    if (!writeAFile(outputPath, encryptedAesKey, iv, tag, ciphertext)) {
        std::cerr << "Failed to write output file: " << outputPath << std::endl;
        return false;
    }

    // std::cout << "Encryption success!" << std::endl;
    return true;
}