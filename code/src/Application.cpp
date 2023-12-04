#include "RenderLayer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    // ... 初始化GLFW和创建窗口 ...

    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // 处理初始化失败
    }

    // 创建渲染层
    RenderLayer renderLayer;
    renderLayer.Initialize();

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 输入处理...

        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 调用RenderLayer的渲染方法
        renderLayer.Render();

        // 交换缓冲区和轮询IO事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理资源
    glfwTerminate();
    return 0;
}
