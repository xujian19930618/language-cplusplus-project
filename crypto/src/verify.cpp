//
// Created by 徐剑 on 2026/1/14.
//

#include "crypto.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <vector>

namespace crypto {

    // 公钥：可以公开
    static const char* PUBLIC_KEY_PEM = R"(-----BEGIN PUBLIC KEY-----
YOUR_PUBLIC_KEY_HERE
-----END PUBLIC KEY-----)";

    static std::string serialize(const LicenseData& d) {
        return d.device_id + "|" + d.expire_date;
    }

    static std::vector<unsigned char> base64_decode(const std::string& input) {
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO* mem = BIO_new_mem_buf(input.data(), input.size());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        BIO_push(b64, mem);

        std::vector<unsigned char> buf(input.size());
        int len = BIO_read(b64, buf.data(), buf.size());
        buf.resize(len);

        BIO_free_all(b64);
        return buf;
    }

    bool verify_license(
        const LicenseData& data,
        const std::string& signature_base64
    ) {
        std::string msg = serialize(data);
        auto sig = base64_decode(signature_base64);

        BIO* bio = BIO_new_mem_buf(PUBLIC_KEY_PEM, -1);
        EVP_PKEY* pkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);

        EVP_MD_CTX* ctx = EVP_MD_CTX_new();
        EVP_DigestVerifyInit(ctx, nullptr, EVP_sha256(), nullptr, pkey);
        EVP_DigestVerifyUpdate(ctx, msg.data(), msg.size());

        int ok = EVP_DigestVerifyFinal(ctx, sig.data(), sig.size());

        EVP_MD_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        BIO_free(bio);

        return ok == 1;
    }

} // namespace crypto