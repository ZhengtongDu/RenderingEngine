#ifndef RENDERER_H
#define RENDERER_H 

#include <GLFW/glfw3.h> // 若需要，包含其他OpenGL头文件
#include "Camera.h"
#include "Application.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <iostream>
#include "stb_image.h"
#include "shader_s.h"
#include "ResourceManager.h"
#include <utility>
#include <map>

// Renderer.h
class Renderer {
public:
    Renderer(GLFWwindow* window);
    void RenderFrame();
    // 其他成员函数...

private:
    GLFWwindow* window;
    Camera camera; // 摄像机对象
    //Light light;   // 光源对象
    // 可能还有其他渲染状态和配置
};

#endif // !RENDERER_H
