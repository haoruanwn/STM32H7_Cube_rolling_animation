#include "user_code_interface.h"
#include "Renderer.hpp"
#include "Cube.hpp"
#include "lcd_spi_200.h"

template <uint16_t ScreenWidth, uint16_t ScreenHeight>
std::array<uint16_t, ScreenWidth * ScreenHeight> Renderer<ScreenWidth, ScreenHeight>::backBuffer
    __attribute__((section(".frame_buffer")));

void User_Code_Entry(void) {
    // [OPTIMIZATION] 使用模板实例化 Renderer，在编译期确定大小，无堆内存分配
    Renderer<LCD_Width, LCD_Height> renderer;
    Cube cube(1.0f);

    float angleX = 0.0f;
    float angleY = 0.0f;

    while (1) {
        angleX += 0.02f;
        angleY += 0.01f;

        renderer.clear();
        renderer.drawCube(cube, angleX, angleY, 0.0f);
        renderer.present();
    }
}