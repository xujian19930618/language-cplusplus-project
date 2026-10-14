
#ifndef LANGUAGE_CPLUSPLUS_PROJECT_CRYPTO_H
#define LANGUAGE_CPLUSPLUS_PROJECT_CRYPTO_H

#pragma once
#include <string>

namespace crypto {

    struct LicenseData {
        std::string device_id;
        std::string expire_date; // YYYYMMDD
    };

    // ====== 验证（客户端 / JNI 可用） ======
    bool verify_license(
        const LicenseData& data,
        const std::string& signature_base64
    );

    // ====== 签名（⚠️ 仅 keygen 使用） ======
    std::string sign_license(
        const LicenseData& data
    );

}

#endif //LANGUAGE_CPLUSPLUS_PROJECT_CRYPTO_H
