//
// Created by 徐剑 on 2025/11/7.
//

#ifndef LANGUAGE_JNI_PROJECT_ENCRYPTION_H
#define LANGUAGE_JNI_PROJECT_ENCRYPTION_H
#include <string>
#include <vector>
#include <fstream>
#include <openssl/err.h>


// ---- Base64 decode helper ----
static std::vector<unsigned char> base64Decode(const std::string &in);
// ---- Load embedded public key (we'll embed as pieces to make static analysis稍难) ----
static EVP_PKEY* load_embedded_pubkey();
// ---- read file into string ----
static bool readFile(const std::string &path, std::string &out);
// ---- simple JSON field extractor (non-robust, for demo only) ----
// find value of "expiry":"YYYY-MM-DD" or "hw":"VALUE"
static bool extractJsonField(const std::string &json, const std::string &field, std::string &value);
// ---- verify signature (RSA PSS not used in this demo; using RSA PKCS1 v1.5 for simplicity) ----
static bool verifySignature(EVP_PKEY* pubkey, const std::string &payload, const std::vector<unsigned char> &sig);


#endif //LANGUAGE_JNI_PROJECT_ENCRYPTION_H