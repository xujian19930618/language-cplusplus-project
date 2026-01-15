//
// Created by 徐剑 on 2026/1/15.
// 继承

#ifndef LANGUAGE_CPLUSPLUS_PROJECT_SHAPE_H
#define LANGUAGE_CPLUSPLUS_PROJECT_SHAPE_H

// 基类
class Shape {
public:
    void setWidth(int w);
    void setHeight(int h);

protected:
    int width;
    int height;
};

// 基类 PaintCost
class PaintCost
{
public:
    int getCost(int area);
};

// 派生类
class Rectangle : public Shape, public PaintCost {
public:
    int getArea();
};


#endif //LANGUAGE_CPLUSPLUS_PROJECT_SHAPE_H
