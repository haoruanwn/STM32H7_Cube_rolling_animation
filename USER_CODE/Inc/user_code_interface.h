#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 这是从 main.c 调用的唯一入口函数。
 * 所有 C++ 对象的创建和主循环都在这个函数内部启动。
 */
void User_Code_Entry(void);

#ifdef __cplusplus
}
#endif

