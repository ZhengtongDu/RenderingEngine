#include "ResourceManager.h"
#include "stb_image.h"
#include <iostream>
#include "OBJ_Loader.h"
#include <Eigen/Core>
#include <Eigen/Dense>

bool ResourceManager::loadMesh(std::string& fileName, std::vector<float>& retVector)
{
    if(fileName == "")
        return false;
    objl::Loader Loader;
    bool loadout = Loader.LoadFile(fileName);

    if(loadout == true) 
    {
        for(int i = 0; i < Loader.LoadedVertices.size(); i++)
        {
            Eigen::Vector3f v1(10 * Loader.LoadedVertices[i].Position.X, 10 * Loader.LoadedVertices[i].Position.Y, 10 * Loader.LoadedVertices[i].Position.Z);
            i++;
            Eigen::Vector3f v2(10 * Loader.LoadedVertices[i].Position.X, 10 * Loader.LoadedVertices[i].Position.Y, 10 * Loader.LoadedVertices[i].Position.Z);
            i++;
            Eigen::Vector3f v3(10 * Loader.LoadedVertices[i].Position.X, 10 * Loader.LoadedVertices[i].Position.Y, 10 * Loader.LoadedVertices[i].Position.Z);
            Eigen::Vector3f e1, e2;
            e1 = v2 - v1, e2 = v3 - v2;
            Eigen::Vector3f normal = e2.cross(e1).normalized();
            retVector.push_back(v1.x());
            retVector.push_back(v1.y());
            retVector.push_back(v1.z());
            retVector.push_back(normal.x());
            retVector.push_back(normal.y());
            retVector.push_back(normal.z());
            retVector.push_back(v2.x());
            retVector.push_back(v2.y());
            retVector.push_back(v2.z());
            retVector.push_back(normal.x());
            retVector.push_back(normal.y());
            retVector.push_back(normal.z());
            retVector.push_back(v3.x());
            retVector.push_back(v3.y());
            retVector.push_back(v3.z());
            retVector.push_back(normal.x());
            retVector.push_back(normal.y());
            retVector.push_back(normal.z());
        }
    }


    // for(int i = 0; i < retVector.size() / 6; i++)
    // {
    //     std::cout << "the " << i << " th point vector: ";
    //     std::cout << retVector[6 * i] << ", " ;
    //     std::cout << retVector[6 * i + 1] << ", " ;
    //     std::cout << retVector[6 * i + 2] << std::endl;
    //     std::cout << "normal vector: ";
    //     std::cout << retVector[6 * i + 3] << ", " ;
    //     std::cout << retVector[6 * i + 4] << ", " ;
    //     std::cout << retVector[6 * i + 5] << std::endl;
    // }

    return true;
}
