#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

class ResourceManager {
public:
    // 删除复制构造函数和赋值操作符，确保只有一个实例
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    // 提供一个全局访问点
    static ResourceManager& GetInstance() {
        static ResourceManager instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }

    unsigned int LoadTexture(const char *path);
    // 其他资源加载函数...

private:
    // 私有构造函数和析构函数
    ResourceManager() {}
    ~ResourceManager() {}

    // 存储资源的容器
    std::map<std::string, unsigned int> textures; // 纹理资源映射
    // 可能还有其他资源类型，如模型、声音等
};

#endif // RESOURCEMANAGER_H