cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 找到OpenGL
find_package(OpenGL REQUIRED)

# 添加GLFW
find_package(glfw3 REQUIRED)

# 添加GLAD
add_subdirectory(path/to/glad)

# 添加ImGui
# 假设你有一个添加ImGui的CMake模块或者你需要手动设置
# ...

# 添加OCCT
# 假设你有一个添加OCCT的CMake模块或者你需要手动设置
# ...

# 包含目录
include_directories(
    ${OPENGL_INCLUDE_DIR}
    path/to/glfw/include
    path/to/glad/include
    path/to/imgui/include
    path/to/occt/include
    # 其他包含目录
)

# 设置你的源文件
set(SOURCE_FILES
    main.cpp
    RenderLayer.cpp
    # 其他源文件
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 链接库
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_gl_LIBRARY}
    glfw
    glad
    imgui
    occt
    # 其他链接库
)
