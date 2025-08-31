#include "user_code_interface.h"
#include "Renderer.hpp"
#include "Cube.hpp"
#include "lcd_spi_200.h"

template <uint16_t ScreenWidth, uint16_t ScreenHeight>
std::array<uint16_t, ScreenWidth * ScreenHeight> Renderer<ScreenWidth, ScreenHeight>::backBuffer
    __attribute__((section(".frame_buffer")));

void User_Code_Entry(void) {
    Renderer<LCD_Width, LCD_Height> renderer;
    Cube cube(1.0f);

    // 【修改】变量以角度(degree)为单位，更直观
    float angleX_deg = 0.0f;
    float angleY_deg = 0.0f;

    while (1) {
        // 每次更新1度，速度可以按需调整
        angleX_deg += 6.0f;
        angleY_deg += 3.0f;

        // 角度值会自动回绕，CompileTimeTrigLUT内部会处理fmod
        // 无需手动处理 if (angleX_deg > 360) ...

        renderer.clear();
        // 【修改】直接将角度值传入drawCube函数
        renderer.drawCube(cube, angleX_deg, angleY_deg, 0.0f);
        renderer.present();
    }
}