#include "Application.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <iostream>
#include "stb_image.h"
#include "shader_s.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include <utility>
#include <map>
#include "QEM.h"
#include <glm/glm.hpp>
#include <vector>
#include <list>

unsigned int shaderProgram;
unsigned int VBO, VAO;

// QEM 算法

bool QEM(std::vector<float>& inputVector);
bool doQEM(GLFWwindow *window);

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
float QEMTime = 0.0f;

// 光源类型
int casterType = 1; // 默认为点光源类型

// GLFW错误回调函数
static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW错误 %d: %s\n", error, description);
}

// 应用程序构造函数
Application::Application(const char* windowName) {
    // 初始化GLFW，设置OpenGL上下文和ImGui等
    // 设置错误回调
    glfwSetErrorCallback(glfw_error_callback);

    // 初始化GLFW
    if (!glfwInit())
        return;

    // 创建窗口
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, windowName, nullptr, nullptr);
    if (window == nullptr){
        return;
    }

    initializeGL();

}

// 初始化OpenGL
void Application::initializeGL()
{
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }


    // renderTool = std::make_unique<Renderer>(window, SCR_WIDTH, SCR_HEIGHT);
}

// 应用程序析构函数
Application::~Application() {
    // 清理资源
}

// 应用程序运行函数
void Application::Run() {

    // 设置顶点数据（和缓冲区）并配置顶点属性

    resourceManager = std::make_unique<ResourceManager>();

    std::string obj_path = "../assets/objects/bunny.obj";
    std::vector<float> bunnyVerticesVector;
    resourceManager->loadMesh(obj_path, bunnyVerticesVector);

    float *bunnyVertices = new float[bunnyVerticesVector.size()];
    for(int i = 0; i < bunnyVerticesVector.size(); i++)
    {
        bunnyVertices[i] = bunnyVerticesVector[i];
    }

    unsigned int bunnyVAO, bunnyVBO;
    glGenVertexArrays(1, &bunnyVAO);
    glGenBuffers(1, &bunnyVBO);

    glBindBuffer(GL_ARRAY_BUFFER, bunnyVBO);
    glBufferData(GL_ARRAY_BUFFER, bunnyVerticesVector.size() * sizeof(float), bunnyVertices, GL_STATIC_DRAW);
    glBindVertexArray(bunnyVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

    // 设置为线框模式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int t = 0;
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
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set MVP matrices
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model(1.0f);

        // set lamp
        glm::vec3 lightPos(1.2f, 1.0f, 4.0f);

        // set object
        lightingShader.use();
        lightingShader.setInt("casterType", casterType);
        // render container
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[0]);
        float angle = 0.0f;
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
        glBindVertexArray(bunnyVAO);
        if(t > 20)
            glDrawArrays(GL_TRIANGLES, 0, bunnyVerticesVector.size() / 6);

        if(doQEM(window) == true)
        {
            QEM(bunnyVerticesVector);
            t = 0;
        }

        t++;
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

bool doQEM(GLFWwindow *window)
{   
    if(abs(lastFrame - QEMTime) < deltaTime * 10)
    {   
        return false;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        std::cout << abs(lastFrame - QEMTime) << std::endl;
        QEMTime = lastFrame;
        return true;
    }
    return false;
}

bool QEM(std::vector<float>& inputVector)
{
    list<OBJIndex> objIndex;
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;

    for(int i = 0; i < inputVector.size(); i++)
    {
        glm::vec3 vertex, normal;
        vertex.x = inputVector[i++];
        vertex.y = inputVector[i++];
        vertex.z = inputVector[i++];
        normal.x = inputVector[i++];
        normal.y = inputVector[i++];
        normal.z = inputVector[i];
        vertices.push_back(vertex);
        normals.push_back(normal);
        OBJIndex tmpIndex;
        tmpIndex.vertexIndex = i;
        tmpIndex.normalIndex = i;
        objIndex.push_back(tmpIndex);
    }

    MeshSimplification m(objIndex, vertices);
    m.print();
    list<OBJIndex> retobjIndex;
    vector<glm::vec3> retvertices;

    retobjIndex = m.getIndices();
    retvertices = m.getVertices();
    
    return true;
}
