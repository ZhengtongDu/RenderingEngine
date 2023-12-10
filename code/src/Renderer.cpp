#include "Renderer.h"

// Renderer.cpp
Renderer::Renderer(GLFWwindow* window) : window(window), camera(/* 初始化参数 */) { // , light(/* 初始化参数 */) {
    // 初始化渲染相关的设置
    // 例如，加载着色器、设置光照参数等
}

void Renderer::RenderFrame() {
    // 使用 camera 和 light 的数据进行渲染
    // ...
}
