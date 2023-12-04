#include "RenderLayer.h"
#include <glad/glad.h>  // 确保包含了正确的头文件

// ... 着色器加载函数 ...

RenderLayer::RenderLayer() : VAO(0), VBO(0), EBO(0), shaderProgram(0) {
}

RenderLayer::~RenderLayer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

void RenderLayer::Initialize() {
    // ... 与上面Application.cpp中相同的初始化代码 ...
}

void RenderLayer::Render() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
