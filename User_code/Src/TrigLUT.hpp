#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <utility>
#include "FixedPoint.hpp"

// 定义 M_PI (如果 cmath 中没有)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Precision: 精度乘数，例如 Precision=10 时，可以分辨 0.1 度
template <size_t TableSize = 360, size_t Precision = 10>
class CompileTimeTrigLUT {
private:
    // 实际的数组大小
    static constexpr size_t ArraySize = TableSize * Precision;

    // 辅助函数：在编译期计算单个sin值
    static constexpr FixedPoint sin_calculator(size_t i) {
        // 【修改2】使用 sinf 并确保所有常量都是 float 类型，避免 double 转换
        return FixedPoint(std::sinf(static_cast<float>(i) / Precision * ((float)M_PI / 180.0f)));
    }

    // 辅助函数：在编译期计算单个cos值
    static constexpr FixedPoint cos_calculator(size_t i) {
        // 【修改2】同样，使用 cosf
        return FixedPoint(std::cosf(static_cast<float>(i) / Precision * ((float)M_PI / 180.0f)));
    }

    // 使用 std::integer_sequence 和参数包展开来在编译期填充数组
    template <std::size_t... I>
    static constexpr std::array<FixedPoint, ArraySize> generate_sin_table(std::index_sequence<I...>) {
        return {{ sin_calculator(I)... }};
    }

    template <std::size_t... I>
    static constexpr std::array<FixedPoint, ArraySize> generate_cos_table(std::index_sequence<I...>) {
        // 【修改3】返回值类型应为 FixedPoint 数组
        return {{ cos_calculator(I)... }};
    }

public:
    // 这两个表在编译时就已经完全计算好并填充完毕
    static constexpr std::array<FixedPoint, ArraySize> sin_table =
        generate_sin_table(std::make_index_sequence<ArraySize>{});

    static constexpr std::array<FixedPoint, ArraySize> cos_table =
        generate_cos_table(std::make_index_sequence<ArraySize>{});

    // 【修改4】重构运行时查询函数
    // 输入：float 类型的角度值
    // 返回：FixedPoint 类型的结果，用于后续计算
    static constexpr FixedPoint sin(float angle_degree) {
        float angle = std::fmod(angle_degree, static_cast<float>(TableSize));
        if (angle < 0) {
            angle += static_cast<float>(TableSize);
        }
        // 计算索引时使用浮点数进行，然后四舍五入到最近的整数索引
        auto index = static_cast<size_t>(std::round(angle * Precision));
        return sin_table[index % ArraySize];
    }

    static constexpr FixedPoint cos(float angle_degree) {
        float angle = std::fmod(angle_degree, static_cast<float>(TableSize));
        if (angle < 0) {
            angle += static_cast<float>(TableSize);
        }
        auto index = static_cast<size_t>(std::round(angle * Precision));
        return cos_table[index % ArraySize];
    }
};