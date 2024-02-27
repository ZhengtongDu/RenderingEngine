/**
 * @file main.cpp
 * @brief 主程序文件
 *
 * 本文件包含主程序入口点和应用程序的初始化。
 */

#include "Application.h"

/**
 * @brief 程序的主入口点。
 *
 * 初始化Application类的实例并运行应用程序。
 * 
 * @param argc 命令行参数的数量
 * @param argv 命令行参数的数组
 * @return 程序退出状态。返回0表示正常退出。
 */
int main(int argc, char** argv) {
    Application app;
    app.Run();
    return 0;
}
