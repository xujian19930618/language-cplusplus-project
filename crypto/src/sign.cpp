//
// Created by 徐剑 on 2026/1/14.
//

#include "crypto.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <sstream>

namespace crypto {

    // ⚠️ 私钥：只存在于 keygen
    static const char* PRIVATE_KEY_PEM = R"(-----BEGIN EC PRIVATE KEY-----
YOUR_PRIVATE_KEY_HERE
-----END EC PRIVATE KEY-----)";

    static std::string serialize(const LicenseData& d) {
        return d.device_id + "|" + d.expire_date;
    }

    static std::string base64_encode(const unsigned char* buf, size_t len) {
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO* mem = BIO_new(BIO_s_mem());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        BIO_push(b64, mem);
        BIO_write(b64, buf, len);
        BIO_flush(b64);

        BUF_MEM* bptr;
        BIO_get_mem_ptr(b64, &bptr);
        std::string out(bptr->data, bptr->length);
        BIO_free_all(b64);
        return out;
    }

    std::string sign_license(const LicenseData& data) {
        std::string msg = serialize(data);

        BIO* bio = BIO_new_mem_buf(PRIVATE_KEY_PEM, -1);
        EVP_PKEY* pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);

        EVP_MD_CTX* ctx = EVP_MD_CTX_new();
        EVP_DigestSignInit(ctx, nullptr, EVP_sha256(), nullptr, pkey);
        EVP_DigestSignUpdate(ctx, msg.data(), msg.size());

        size_t sig_len = 0;
        EVP_DigestSignFinal(ctx, nullptr, &sig_len);
        unsigned char* sig = new unsigned char[sig_len];
        EVP_DigestSignFinal(ctx, sig, &sig_len);

        std::string result = base64_encode(sig, sig_len);

        delete[] sig;
        EVP_MD_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        BIO_free(bio);

        return result;
    }

} // namespace crypto