/**
 * @file Application.h
 * @brief 用来调用程序的接口头文件
 *
 * 本头文件用来处理opengl相关初始化事项，进一步细分代码结构
 */

#ifndef APPLICATION_H
#define APPLICATION_H

// #include "Renderer.h"
// #include "EventHandler.h"

// #include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h> // 包含glfw3.h
#include <glm/glm.hpp>
#include <memory>
#include "ResourceManager.h"

/**
 * @class Application
 * @brief 程序接口类，用于整合各个模块的内容
 *
 */
class Application {
public:
    Application(const char *windowName = "GUI APP");
    ~Application();
    void Run();

private:
    // Renderer renderer;
    // EventHandler eventHandler;
    // 其他应用程序状态和逻辑
    GLFWwindow* window;
    std::unique_ptr<ResourceManager> resourceManager;
    void initializeGL();
};


#endif // !APPLICATION_H