#include "EventHandler.h"

EventHandler::EventHandler(GLFWwindow* window) : window(window) {
    // 初始化事件处理器
}

void EventHandler::PollEvents() {
    glfwPollEvents();
    // 处理其他事件
}

bool EventHandler::ShouldClose() const {
    return glfwWindowShouldClose(window);
}

// 其他事件处理方法的实现
