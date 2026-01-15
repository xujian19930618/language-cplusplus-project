
#include "main.h"
#include <iostream>

#include "class_oop/class_test.h"

int main() {


    basics();

    class_oop();


    // auto lang = "C++";
    // std::cout << "Hello and welcome to " << lang << "!\n";
    //
    // for (int i = 1; i <= 5; i++) {
    //     std::cout << "i = " << i << std::endl;
    // }

    return 0;
}

int basics() {
    printf("hello world\n");
    return 0;
}


int class_oop() {
    box_test();
    shape_test();
    return 0;
}
