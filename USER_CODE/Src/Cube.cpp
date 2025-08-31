#include "Cube.hpp"

Cube::Cube(float size) {
    float s = size / 2.0f;
    vertices = {{
        {-s, -s, -s}, {s, -s, -s}, {s, s, -s}, {-s, s, -s}, // 底面4个点
        {-s, -s,  s}, {s, -s,  s}, {s, s,  s}, {-s, s,  s}  // 顶面4个点
    }};
}