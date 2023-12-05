#include "Application.h"

Application::Application() {
    // 初始化GLFW，设置OpenGL上下文和ImGui等
}

Application::~Application() {
    // 清理资源
}

void Application::Run() {
    while (!eventHandler.ShouldClose()) {
        eventHandler.PollEvents();
        renderer.BeginFrame();
        // GUI代码
        renderer.EndFrame();
    }
}
