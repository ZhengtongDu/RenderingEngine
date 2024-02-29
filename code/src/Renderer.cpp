#include "Renderer.h"

    // static void framebuffer_size_callback_wrapper(GLFWwindow* window, int width, int height);
    // static void mouse_callback_wrapper(GLFWwindow* window, double xpos, double ypos);
    // static void scroll_callback_wrapper(GLFWwindow* window, double xoffset, double yoffset);

// Renderer.cpp
Renderer::Renderer(GLFWwindow* _window, const unsigned int& _screenWidth, const unsigned int& _screenHeight) : window(_window), screenWidth(_screenWidth), screenHeight(_screenHeight), camera(/* 初始化参数 */) { // , light(/* 初始化参数 */) {
    // 初始化渲染相关的设置

    // 摄像机
    float lastX = screenWidth / 2.0f;
    float lastY = screenHeight / 2.0f;
    bool firstMouse = true;

    // 计时
    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间
    float responseTime = 0.0f; // 响应时间，用于处理按键事件的防抖


    glfwMakeContextCurrent(window);

    // 设置用户指针，以便在静态回调函数中获取 Application 类的实例
    glfwSetWindowUserPointer(window, this);

    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_wrapper);
    // glfwSetCursorPosCallback(window, mouse_callback_wrapper);
    // glfwSetScrollCallback(window, scroll_callback_wrapper);

    // // 告诉GLFW捕获我们的鼠标
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: 加载所有OpenGL函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "初始化GLAD失败" << std::endl;
        return;
    }

    // 启用深度测试
    glEnable(GL_DEPTH_TEST);

    glfwSwapInterval(1); // 启用垂直同步

    // 初始化ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // 设置ImGui样式
    ImGui::StyleColorsClassic();

    // 绑定ImGui与GLFW
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // 例如，加载着色器、设置光照参数等
}

void Renderer::RenderFrame() {
    // 使用 camera 和 light 的数据进行渲染
    // ...
}

void Renderer::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Renderer::processInput(GLFWwindow *window)
{
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
/*     if (responseTime > 500.0f && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        casterType = (casterType == 3 ? 1 : (casterType + 1));
        if(casterType == 1)
            std::cout << "point light mode" << std::endl;
        if(casterType == 2)
            std::cout << "parallel light mode" << std::endl;
        if(casterType == 3)
            std::cout << "flash light mode" << std::endl;
        responseTime = 0.0f;
    }
 */
}

void Renderer::mouse_callback(GLFWwindow *window, double xposIn, double yposIn){
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// 鼠标滚轮回调函数
void Renderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


    static void framebuffer_size_callback_wrapper(GLFWwindow* window, int width, int height) {
        // 获取 Renderer 类的实例
        Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
        if (renderer) {
            renderer->framebuffer_size_callback(window, width, height); // 调用实例的成员函数
        }
    }

    static void mouse_callback_wrapper(GLFWwindow* window, double xpos, double ypos) {
        Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
        if (renderer) {
            renderer->mouse_callback(window, xpos, ypos);
        }
    }

    static void scroll_callback_wrapper(GLFWwindow* window, double xoffset, double yoffset) {
        Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
        if (renderer) {
            renderer->scroll_callback(window, xoffset, yoffset);
        }
    }