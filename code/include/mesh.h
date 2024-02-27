#ifndef MESH_H
#define MESH_H

#include "glad/glad.h"
#include "shader_s.h"

#include <GLFW/glfw3.h>  

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

/**
 * @class Mesh
 * @brief 网格类，内部存储各种网格相关的信息
 *
 */
class Mesh {
public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // function
    Mesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<Texture>& _textures);
    void Draw(Shader shader);

private:
    // rendering data
    unsigned int VAO, VBO, EBO;
    // function
    void setupMesh();
};


#endif // MESH_H