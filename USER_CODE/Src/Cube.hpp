#pragma once

#include "MathTypes.hpp"
#include <array>
#include <utility>
#include "FixedPoint.hpp"

class Cube {
public:
    explicit Cube(float size);

    const std::array<Point3D, 8>& getVertices() const { return vertices; }
    const std::array<std::pair<int, int>, 12>& getEdges() const { return edges; }

private:
    std::array<Point3D, 8> vertices;
    // [OPTIMIZATION] 使用 constexpr 确保在编译期初始化
    static constexpr std::array<std::pair<int, int>, 12> edges = {{
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // 底面
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // 顶面
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // 侧边
    }};
};