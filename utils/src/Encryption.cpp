//
// Created by 徐剑 on 2025/11/7.
//

#include "Encryption.h"
#include <sstream>
#include <ctime>
#include <iostream>
#include <openssl/pem.h>
#include <openssl/bio.h>

static EVP_PKEY* g_pubkey = nullptr;

static std::vector<unsigned char> base64Decode(const std::string &in) {
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO *bmem = BIO_new_mem_buf(in.data(), (int)in.size());
    bmem = BIO_push(b64, bmem);
    std::vector<unsigned char> out(in.size()); // safe upper bound
    int outlen = BIO_read(bmem, out.data(), (int)out.size());
    BIO_free_all(bmem);
    if (outlen <= 0) return {};
    out.resize(outlen);
    return out;
}

static EVP_PKEY* load_embedded_pubkey() {
    if (g_pubkey) return g_pubkey;

    // 公钥 PEM 字符串分段（示例：用你从 public.pem 复制出来的 PEM 内容）
    // 在实际使用时你应替换为你的公钥 PEM 内容并分段（分成多个 const 字*）
    const char* part1 =
        "-----BEGIN PUBLIC KEY-----\n"
        "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8A";
    const char* part2 =
        "MIIBCgKCAQEAuK2a...REPLACE_WITH_YOUR_PUBKEY_CONTENT...ZqQIDAQAB\n";
    const char* part3 =
        "-----END PUBLIC KEY-----\n";

    std::string pem = std::string(part1) + std::string(part2) + std::string(part3);

    BIO* bio = BIO_new_mem_buf(pem.data(), (int)pem.size());
    if (!bio) return nullptr;
    EVP_PKEY* pkey = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (!pkey) {
        // print openssl err
        unsigned long e;
        while ((e = ERR_get_error()) != 0) {
            char buf[256];
            ERR_error_string_n(e, buf, sizeof(buf));
            fprintf(stderr, "OpenSSL error: %s\n", buf);
        }
    }
    g_pubkey = pkey;
    return pkey;
}


static bool readFile(const std::string &path, std::string &out) {
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    if (!ifs) return false;
    std::ostringstream ss;
    ss << ifs.rdbuf();
    out = ss.str();
    return true;
}


static bool extractJsonField(const std::string &json, const std::string &field, std::string &value) {
    std::string patt = "\"" + field + "\":\"";
    size_t p = json.find(patt);
    if (p == std::string::npos) return false;
    size_t start = p + patt.size();
    size_t end = json.find('"', start);
    if (end == std::string::npos) return false;
    value = json.substr(start, end - start);
    return true;
}

static bool verifySignature(EVP_PKEY* pubkey, const std::string &payload, const std::vector<unsigned char> &sig) {
    if (!pubkey) return false;
    bool ok = false;
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx) return false;
    if (EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, pubkey) == 1) {
        if (EVP_DigestVerify(mdctx, sig.data(), sig.size(),
                             (const unsigned char*)payload.data(), payload.size()) == 1) {
            ok = true;
        }
    }
    EVP_MD_CTX_free(mdctx);
    return ok;
}