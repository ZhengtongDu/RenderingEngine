#pragma once
#include "ImGuiLayer.h"
#include "RenderLayer.h"
#include "GeometryEditor.h"

class Application {
public:
    Application();
    ~Application();
    void Run();

private:
    bool running = true;
    ImGuiLayer imguiLayer;
    RenderLayer renderLayer;
    GeometryEditor geometryEditor;
};
