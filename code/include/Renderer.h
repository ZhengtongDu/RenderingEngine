#ifndef RENDERER_H
#define RENDERER_H 

#include "Camera.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <iostream>
#include "stb_image.h"
#include "shader_s.h"
#include "ResourceManager.h"
#include <utility>
#include <map>

/**
 * @class Renderer
 * @brief 渲染模块类，被Application类调用，用于处理程序中和OpenGL有关部分的响应
 *
 */
class Renderer {
public:
    Renderer(GLFWwindow* _window, const unsigned int& _screenWidth, const unsigned int& _screenHeight);
    void RenderFrame();
    // 其他成员函数...

    // 回调函数声明
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
    void processInput(GLFWwindow *window);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

private:
    GLFWwindow* window;
    Camera camera; // 摄像机对象
    //Light light;   // 光源对象
    // 可能还有其他渲染状态和配置

    // 配置变量
    unsigned int screenWidth;
    unsigned int screenHeight;
    float lastX;
    float lastY;
    bool firstMouse;

    // 计时
    float deltaTime; // 当前帧与上一帧的时间差
    float lastFrame; // 上一帧的时间
    float responseTime; // 响应时间，用于处理按键事件的防抖

};


#endif // !RENDERER_H
