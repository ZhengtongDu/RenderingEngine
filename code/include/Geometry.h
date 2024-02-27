#ifndef GEOMETRYEDITOR_H
#define GEOMETRYEDITOR_H

#include <vector>

// 定义几何体数据结构

/**
 * @class Geometry
 * @brief 几何类，用来存储不同的几何体数据结构
 *
 * 这部分内容还有待补充，暂时不使用
 */
class Geometry {
public:
    Geometry();
    ~Geometry();
    // 几何体操作方法
private:
    std::vector<float> vertices; // 顶点数据
    // 其他几何体相关数据
};

#endif // GEOMETRYEDITOR_H
