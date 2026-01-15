//
// Created by 徐剑 on 2026/1/15.
//

#ifndef LANGUAGE_CPLUSPLUS_PROJECT_BOX_H
#define LANGUAGE_CPLUSPLUS_PROJECT_BOX_H


class Box {
public:
    double length;      // 盒子的长度
    double breadth;     // 盒子的宽度
    double height;      // 盒子的高度
    // 成员函数声明
    double get(void);
    void set(double new_length, double new_breadth, double new_height);
};


#endif //LANGUAGE_CPLUSPLUS_PROJECT_BOX_H