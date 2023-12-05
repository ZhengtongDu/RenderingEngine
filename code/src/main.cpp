#include "Application.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h> // 包含glfw3.h
#include <iostream>

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**) {
    Application app;
    app.Run();
    return 0;
}


/*

#include "Application.h"

int main(int, char**) {
    Application app;
    app.Run();
    return 0;
}
*/