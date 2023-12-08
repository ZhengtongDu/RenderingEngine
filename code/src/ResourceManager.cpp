#include "ResourceManager.h"
#include "stb_image.h"
#include <iostream>

unsigned int ResourceManager::LoadTexture(const char *path) {
    // 检查纹理是否已经加载过，如果没有则加载
    auto &textures = GetInstance().textures;
    auto it = textures.find(path);
    if (it != textures.end()) {
        return it->second; // 如果已经加载，返回纹理ID
    } else {
        // 加载纹理...
        unsigned int textureID;
        // 使用stb_image.h加载图片数据，并创建OpenGL纹理...
        // 如果加载成功，存储纹理ID
        textures[path] = textureID;
        return textureID;
    }
}