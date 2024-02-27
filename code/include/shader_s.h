#ifndef SHADER_S_H
#define SHADER_S_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>  
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @class Shader
 * @brief 着色器类，用来导入着色器并进行相关赋值操作
 *
 */
class Shader
{
public:
    // program ID
    unsigned int ID;

    // constructor generates the shader on the fly
    // ----------------------------------------------

    Shader(const char* vertexPath, const char* fragmentPath);

    // use/active program
    void use();
    //uniform tools function
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4& mat) const;
    void setVec3(const std::string &name, const float x, const float y, const float z) const;
    void setVec3(const std::string &name, const glm::vec3& vec) const;
};



#endif // SHADER_S_H