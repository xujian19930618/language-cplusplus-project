#include <iostream>

#include "crypto.h"

int main() {

    crypto::LicenseData lic1 {"device12345", "20250131"};
    std::string basic_string = crypto::sign_license(lic1);
    std::cout << basic_string << std::endl;
    // bool verify_license = crypto::verify_license(lic1, basic_string);
    // std::cout << verify_license << std::endl;


    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}
