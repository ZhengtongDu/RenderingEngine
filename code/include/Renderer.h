#ifndef RENDERER_H
#define RENDERER_H 

#include <GLFW/glfw3.h> // 若需要，包含其他OpenGL头文件

class Renderer {
public:
    Renderer();
    ~Renderer();
    void BeginFrame();
    void EndFrame();
    void Draw(); // 根据Geometry数据绘制几何体
    // 其他渲染相关的方法
};

#endif // !RENDERER_H
