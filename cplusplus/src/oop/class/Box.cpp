//
// Created by 徐剑 on 2026/1/15.
//

#include "../../../study/class_oop/Box.h"

#include <iostream>
using namespace std;

double Box::get(void) {
    return length * breadth * height;
}
void Box::set(double len, double bre, double hei) {
    length = len;
    breadth = bre;
    height = hei;
}
