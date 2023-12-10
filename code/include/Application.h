#ifndef APPLICATION_H
#define APPLICATION_H

// #include "Renderer.h"
// #include "EventHandler.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h> // 包含glfw3.h
#include <glm/glm.hpp>
#include <memory>
#include <string>

class Application {
public:
    Application(char *windowName = "GUI APP");
    ~Application();
    void Run();

private:
    // Renderer renderer;
    // EventHandler eventHandler;
    // 其他应用程序状态和逻辑
    GLFWwindow* window;
    std::unique_ptr<Renderer> renderTool;
};


#endif // !APPLICATION_H