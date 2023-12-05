#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <GLFW/glfw3.h>

class EventHandler {
public:
    EventHandler(GLFWwindow* window);
    void PollEvents();
    bool ShouldClose() const;

private:
    GLFWwindow* window;
    // 处理特定事件的方法
};

#endif // !EVENTHANDLER_H

