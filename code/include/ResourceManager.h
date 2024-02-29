#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include "mesh.h"




/**
 * @class ResourceManager
 * @brief 资源管理类，用来处理模型文件I/O操作、加载操作
 *
 * 这个类目前还没有写好
 */
class ResourceManager {
public:

    ResourceManager() {}
    ~ResourceManager() {}

    unsigned int LoadTexture(const char *path);
    // 其他资源加载函数...

    bool loadMesh(std::string& fileName, std::vector<float>& retVector);
    // 存储资源的容器
    std::map<std::string, Texture> Textures;
    std::map<std::string, Shader> Shaders;
    std::map<std::string, Mesh> Meshes;

    // 创建纹理的函数
    Texture& LoadTexture(std::string file, std::string name);
    Texture& GetTexture(std::string name);

    // 创建着色器的函数
    Shader& LoadShader(std::string vShaderFile, std::string fShaderFile, std::string name);
    Shader& GetShader(std::string name);

    // 加载模型的函数
    Mesh& LoadMesh(std::string file, std::string name);
    Mesh& GetMesh(std::string name);

    // 绑定VAO和VBO等的函数
    void SetupMesh(Mesh& mesh);

    // 清除所有资源
    void Clear();


private:

    // 加载和编译着色器的辅助函数
    Shader loadShaderFromFile(std::string vShaderFile, std::string fShaderFile);

    // 加载纹理的辅助函数
    Texture loadTextureFromFile(std::string file);

    // 加载模型的辅助函数
    // Mesh loadMeshFromFile(std::string file);

    // 存储资源的容器
    std::map<std::string, unsigned int> textures; // 纹理资源映射
    // 可能还有其他资源类型，如模型、声音等
};

#endif // RESOURCEMANAGER_H
