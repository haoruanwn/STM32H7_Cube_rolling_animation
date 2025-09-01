#include "Cube.hpp"

// 使用成员初始化列表，并修正数值初始化逻辑
Cube::Cube(float size) : vertices{{
    {-FixedPoint(size/2), -FixedPoint(size/2), -FixedPoint(size/2)},
    { FixedPoint(size/2), -FixedPoint(size/2), -FixedPoint(size/2)},
    { FixedPoint(size/2),  FixedPoint(size/2), -FixedPoint(size/2)},
    {-FixedPoint(size/2),  FixedPoint(size/2), -FixedPoint(size/2)},
    {-FixedPoint(size/2), -FixedPoint(size/2),  FixedPoint(size/2)},
    { FixedPoint(size/2), -FixedPoint(size/2),  FixedPoint(size/2)},
    { FixedPoint(size/2),  FixedPoint(size/2),  FixedPoint(size/2)},
    {-FixedPoint(size/2),  FixedPoint(size/2),  FixedPoint(size/2)}
}}
{
    // 构造函数体现在为空，因为所有工作都在初始化列表中完成了
}