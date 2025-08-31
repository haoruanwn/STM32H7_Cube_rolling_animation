#pragma once

#include "lcd_spi_200.h"
#include "Cube.hpp"
#include <array>
#include <vector>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include "TrigLUT.hpp"

// 【关键修正】将 ToRGB565 从模板函数改为普通的 constexpr 函数
// 它的功能与屏幕尺寸无关，不应该作为模板。
constexpr uint16_t ToRGB565(uint32_t color) {
    uint16_t r = (color >> 19) & 0x1F;
    uint16_t g = (color >> 10) & 0x3F;
    uint16_t b = (color >> 3) & 0x1F;
    return (r << 11) | (g << 5) | b;
}

template <uint16_t ScreenWidth, uint16_t ScreenHeight>
class Renderer {
public:
    Renderer() = default;

    void clear() {
        std::fill(backBuffer.begin(), backBuffer.end(), ToRGB565(LCD_BLACK));
    }

    void drawCube(const Cube& cube, float angleX_deg, float angleY_deg, float angleZ_deg) {
        std::array<Point2D, 8> projectedPoints;

        // 为了方便，定义一个LUT的别名，并指定精度（例如0.1度）
        // 这个别名本身不会产生任何代码，只是为了书写方便
        using LUT = CompileTimeTrigLUT<360, 10>;

        // 【核心修改】用静态查表函数替换昂贵的sinf/cosf计算
        float sinX = LUT::sin(angleX_deg), cosX = LUT::cos(angleX_deg);
        float sinY = LUT::sin(angleY_deg), cosY = LUT::cos(angleY_deg);
        float sinZ = LUT::sin(angleZ_deg), cosZ = LUT::cos(angleZ_deg);

        // 后面的所有旋转和投影计算代码都保持不变
        for (size_t i = 0; i < cube.getVertices().size(); ++i) {
            const auto& p = cube.getVertices()[i];

            float x1 = p.x * cosY - p.z * sinY;
            float z1 = p.x * sinY + p.z * cosY;

            float y2 = p.y * cosX - z1 * sinX;
            float z2 = p.y * sinX + z1 * cosX;

            float x3 = x1 * cosZ - y2 * sinZ;
            float y3 = x1 * sinZ + y2 * cosZ;

            Point3D rotated = {x3, y3, z2};

            float scale = 100.0f;
            projectedPoints[i].x = static_cast<int>(rotated.x * scale) + ScreenWidth / 2;
            projectedPoints[i].y = static_cast<int>(rotated.y * scale) + ScreenHeight / 2;
        }

        for (const auto& edge : cube.getEdges()) {
            const Point2D& p1 = projectedPoints[edge.first];
            const Point2D& p2 = projectedPoints[edge.second];
            drawLine(p1.x, p1.y, p2.x, p2.y, ToRGB565(LCD_GREEN));
        }
    }

    void present() {
        LCD_CopyBuffer(0, 0, ScreenWidth, ScreenHeight, backBuffer.data());
    }

private:
    void drawLine(int x0, int y0, int x1, int y1, uint16_t color) {
        int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = -std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = dx + dy, e2;

        for (;;) {
            if (x0 >= 0 && x0 < ScreenWidth && y0 >= 0 && y0 < ScreenHeight) {
                backBuffer[y0 * ScreenWidth + x0] = color;
            }
            if (x0 == x1 && y0 == y1) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; x0 += sx; }
            if (e2 <= dx) { err += dx; y0 += sy; }
        }
    }

    static std::array<uint16_t, ScreenWidth * ScreenHeight> backBuffer
        __attribute__((section(".frame_buffer")));
};