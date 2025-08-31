#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <utility>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template <size_t TableSize = 360, size_t Precision = 1> // Precision: 1表示0.1度, 10表示0.01度
class CompileTimeTrigLUT {
private:
    // 实际的数组大小
    static constexpr size_t ArraySize = TableSize * Precision;

    // 辅助函数：在编译期计算单个sin值
    // 只要传入的 i 是编译期常量，整个函数就会在编译期执行
    static constexpr float sin_calculator(size_t i) {
        return std::sin(static_cast<float>(i) / Precision * (M_PI / 180.0));
    }

    // 辅助函数：在编译期计算单个cos值
    static constexpr float cos_calculator(size_t i) {
        return std::cos(static_cast<float>(i) / Precision * (M_PI / 180.0));
    }

    // 使用 std::integer_sequence 和参数包展开来在编译期填充数组
    template <std::size_t... I>
    static constexpr std::array<float, ArraySize> generate_sin_table(std::index_sequence<I...>) {
        // { sin_calculator(0), sin_calculator(1), sin_calculator(2), ... }
        return {{ sin_calculator(I)... }};
    }

    template <std::size_t... I>
    static constexpr std::array<float, ArraySize> generate_cos_table(std::index_sequence<I...>) {
        return {{ cos_calculator(I)... }};
    }

public:
    // 这两个表在编译时就已经完全计算好并填充完毕
    static constexpr std::array<float, ArraySize> sin_table =
        generate_sin_table(std::make_index_sequence<ArraySize>{});

    static constexpr std::array<float, ArraySize> cos_table =
        generate_cos_table(std::make_index_sequence<ArraySize>{});

    // 运行时查询函数
    static float sin(float angle_degree) {
        float angle = std::fmod(angle_degree, static_cast<float>(TableSize));
        if (angle < 0) {
            angle += static_cast<float>(TableSize);
        }
        auto index = static_cast<size_t>(std::round(angle * Precision));
        return sin_table[index % ArraySize];
    }

    static float cos(float angle_degree) {
        float angle = std::fmod(angle_degree, static_cast<float>(TableSize));
        if (angle < 0) {
            angle += static_cast<float>(TableSize);
        }
        auto index = static_cast<size_t>(std::round(angle * Precision));
        return cos_table[index % ArraySize];
    }
};