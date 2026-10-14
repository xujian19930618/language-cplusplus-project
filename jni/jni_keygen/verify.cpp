//
// Created by 徐剑 on 2026/1/14.
//


#include <iostream>
#include "crypto.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <device_id> <expire_date> <signature>\n";
        return 1;
    }
    crypto::LicenseData lic1 {argv[1], argv[2]};

    std::cout << lic1.device_id << lic1.expire_date << std::endl;

    std::string basic_string = argv[3];

    std::cout << basic_string << std::endl;


    bool verify_license = crypto::verify_license(lic1, basic_string);
    std::cout << verify_license << std::endl;


    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}
