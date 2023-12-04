#ifndef RENDERLAYER_H
#define RENDERLAYER_H

class RenderLayer {
public:
    RenderLayer();
    ~RenderLayer();

    void Initialize();
    void Render();

private:
    unsigned int VAO, VBO, EBO;
    unsigned int shaderProgram;
};

#endif // RENDERLAYER_H
