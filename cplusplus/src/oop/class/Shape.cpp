//
// Created by 徐剑 on 2026/1/15.
//

#include "../../../study/class_oop/Shape.h"


// 基类成员函数
void Shape::setWidth(int w)
{
    width = w;
}

void Shape::setHeight(int h)
{
    height = h;
}

int PaintCost::getCost(int area)
{
    return area * 70;
}

// 派生类成员函数
int Rectangle::getArea()
{
    return width * height;
}