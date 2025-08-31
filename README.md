# STM32H7 正方体旋转动画

如何编译参考[STM32H750XBH6_CMake_Template](https://github.com/haoruanwn/STM32H750XBH6_CMake_Template)

## 大致效果

![Snipaste_2025-08-31_22-04-46](https://markdownforyuanhao.oss-cn-hangzhou.aliyuncs.com/img1/20250831220522323.png)

没搞DMA，目前刷屏速度比较慢

## 注意事项

![2A331117FDF17C47A3DBFDD410AF2F18](https://markdownforyuanhao.oss-cn-hangzhou.aliyuncs.com/img1/20250831220338959.png)

![D0CC34BCFBD3E49AD0736F70571F95BA](https://markdownforyuanhao.oss-cn-hangzhou.aliyuncs.com/img1/20250831220343015.png)

静态数组存RAM_D2里了，所以给链接脚本留了个副本，确定链接脚本被正确调用
