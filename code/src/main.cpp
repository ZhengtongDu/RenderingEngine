// src/main.cpp

#include "GLSetup.h"

int main() {
    GLSetup glSetup;

    if (!glSetup.initialize(800, 600, "OpenGL Demo")) {
        return -1;
    }

    // 矩形的顶点数据
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // 左下角
         0.5f, -0.5f, 0.0f, // 右下角
         0.5f,  0.5f, 0.0f, // 右上角
        -0.5f,  0.5f, 0.0f  // 左上角
    };

    // 设置顶点数组
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(glSetup.window)) {
        // 清除颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制矩形
        glDrawArrays(GL_QUADS, 0, 4);

        // 交换缓冲区和轮询IO事件
        glfwSwapBuffers(glSetup.window);
        glfwPollEvents();
    }

    // 释放资源
    glDeleteBuffers(1, &VBO);

    return 0;
}
