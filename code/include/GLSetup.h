// include/GLSetup.h

#ifndef GLSETUP_H
#define GLSETUP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLSetup {
public:
    GLFWwindow* window;

    GLSetup();
    ~GLSetup();
    bool initialize(int width, int height, const char* title);
};

#endif // GLSETUP_H