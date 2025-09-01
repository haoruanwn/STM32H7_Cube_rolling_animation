#pragma once
#include <cstdint>

class FixedPoint {
public:
    int32_t m_value; // Q16.16 格式

    static constexpr int FRACTIONAL_BITS = 16;

    // 【修改3】将所有构造函数声明为 constexpr
    constexpr FixedPoint() : m_value(0) {}
    constexpr FixedPoint(int val) : m_value(val << FRACTIONAL_BITS) {}
    constexpr FixedPoint(float val) : m_value(static_cast<int32_t>(val * (1 << FRACTIONAL_BITS))) {}

    // 转换函数
    int toInt() const { return m_value >> FRACTIONAL_BITS; }
    float toFloat() const { return static_cast<float>(m_value) / (1 << FRACTIONAL_BITS); }

    // 重载运算符
    constexpr FixedPoint operator+(const FixedPoint& other) const { return fromRaw(m_value + other.m_value); }
    constexpr FixedPoint operator-(const FixedPoint& other) const { return fromRaw(m_value - other.m_value); }
    constexpr FixedPoint operator*(const FixedPoint& other) const {
        int64_t temp = static_cast<int64_t>(m_value) * other.m_value;
        return fromRaw(static_cast<int32_t>(temp >> FRACTIONAL_BITS));
    }
    // 【新增1】重载除法运算符（这里实现一个简单的除以整数）
    constexpr FixedPoint operator/(int divisor) const {
        return fromRaw(m_value / divisor);
    }
    // 【新增2】重载一元负号运算符
    constexpr FixedPoint operator-() const {
        return fromRaw(-m_value);
    }

private:
    // 【修改3】辅助函数也必须是 constexpr
    static constexpr FixedPoint fromRaw(int32_t raw_value) {
        FixedPoint fp;
        fp.m_value = raw_value;
        return fp;
    }
};