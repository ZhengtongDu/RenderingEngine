#include "Application.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <iostream>
#include "stb_image.h"
#include "shader_s.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <utility>
#include <map>


unsigned int shaderProgram;
unsigned int VBO, VAO;

// 回调函数声明
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
void processInput(GLFWwindow *window);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
unsigned int loadTexture(const char *path);

// 设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 摄像机
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// 计时
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float responseTime = 0.0f; // 响应时间，用于处理按键事件的防抖

// 光源类型
int casterType = 1; // 默认为点光源类型

// GLFW错误回调函数
static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW错误 %d: %s\n", error, description);
}

// 初始化OpenGL
void initializeGL()
{
    // 这里可以放置OpenGL初始化时需要执行的代码
}

// 应用程序构造函数
Application::Application(char* windowName) {
    // 初始化GLFW，设置OpenGL上下文和ImGui等
    // 设置错误回调
    glfwSetErrorCallback(glfw_error_callback);

    // 初始化GLFW
    if (!glfwInit())
        return;

    // 创建窗口
    window = glfwCreateWindow(1280, 720, windowName, nullptr, nullptr);
    if (window == nullptr){
        return;
    }

    renderTool = std::make_unique<Renderer>(window);


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // 告诉GLFW捕获我们的鼠标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    initializeGL();
}

// 应用程序析构函数
Application::~Application() {
    // 清理资源
}

// 应用程序运行函数
void Application::Run() {
    // 设置顶点数据（和缓冲区）并配置顶点属性
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,   0.0f,  -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,   0.0f,   1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,   -1.0f,   0.0f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   -1.0f,   0.0f,   0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   -1.0f,   0.0f,   0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   -1.0f,   0.0f,   0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f,   0.0f,   0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   -1.0f,   0.0f,   0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,    1.0f,   0.0f,   0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f,   0.0f,   0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,   0.0f,   0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f,   0.0f,   0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    1.0f,   0.0f,   0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f,   0.0f,   0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f,  -1.0f,   0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  -1.0f,   0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  -1.0f,   0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  -1.0f,   0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  -1.0f,   0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  -1.0f,   0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,   1.0f,   0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,   1.0f,   0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   1.0f,   0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,   1.0f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,   1.0f,   0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,   1.0f,   0.0f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,   0.0f),
        glm::vec3( 2.0f,  5.0f,  -15.0f),
        glm::vec3(-1.5f, -2.2f,  -2.5f),
        glm::vec3(-3.8f, -2.0f,  -12.3f),
        glm::vec3( 2.4f, -0.4f,  -3.5f),
        glm::vec3(-1.7f,  3.0f,  -7.5f),
        glm::vec3( 1.3f, -2.0f,  -2.5f),
        glm::vec3( 1.5f,  2.0f,  -2.5f),
        glm::vec3( 1.5f,  0.2f,  -1.5f),
        glm::vec3(-1.3f,  1.0f,  -1.5f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // load and create a texture
    unsigned int diffuseMap = loadTexture("../assets/textures/container2.png");
    unsigned int specularMap = loadTexture("../assets/textures/container2_specular.png");

    // set shaders
    // object shader
    Shader lightingShader("../shaders/shader01.vs", "../shaders/shader01.fs");
    lightingShader.use();
    // set object material attributes
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);
    lightingShader.setFloat("material.shininess", 32.0f);
    lightingShader.setVec3("light.lightDirection", -0.2f, -1.0f, -0.3f);
    lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    lightingShader.setFloat("light.constant", 1.0f);
    lightingShader.setFloat("light.linear", 0.09f);
    lightingShader.setFloat("light.quadratic", 0.032f);

    // lamp shader
    Shader lampShader("../shaders/lamp01.vs", "../shaders/lamp01.fs");

    // 主循环
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        //---------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        responseTime += deltaTime * 1000.0f;
        lastFrame = currentFrame;

        // input
        //-------------
        processInput(window);

        // render
        //-------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set MVP matrices
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model(1.0f);

        // set lamp
        lampShader.use();
        glm::vec3 lightPos(1.2f, 1.0f, 4.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.3f));

        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        lampShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // set object
        lightingShader.use();
        lightingShader.setInt("casterType", casterType);
        // render container
        for(int i = 0; i < 10; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.setMat4("model", model);
            lightingShader.setMat4("view", view);
            lightingShader.setMat4("projection", projection);
            lightingShader.setVec3("light.lightPosition", lightPos);
            lightingShader.setVec3("light.flashlightPosition", camera.Position);
            lightingShader.setVec3("light.flashlightDirection", camera.Front);
            lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
            lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
            lightingShader.setVec3("viewPos", camera.Position);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularMap);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);            
        }



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
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
    if (responseTime > 500.0f && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        casterType = (casterType == 3 ? 1 : (casterType + 1));
        if(casterType == 1)
            std::cout << "point light mode" << std::endl;
        if(casterType == 2)
            std::cout << "parallel light mode" << std::endl;
        if(casterType == 3)
            std::cout << "flash light mode" << std::endl;
        responseTime = 0.0f;
    }
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn){
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
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// 加载纹理函数
unsigned int loadTexture(const char *path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if(data) {
        GLenum format;
        if(nrComponents == 1)
            format = GL_RED;
        else if(nrComponents == 3)
            format = GL_RGB;
        else if(nrComponents == 4) {
            format = GL_RGBA;
        }
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "纹理加载失败，路径：" << path << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}
