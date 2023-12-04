cmake_minimum_required(VERSION 3.10)

project(OpenGLDemo)

# 设置OpenGL偏好
set(OpenGL_GL_PREFERENCE GLVND)

# 指定C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 找到OpenGL
find_package(OpenGL REQUIRED)

# 找到GLFW
find_package(glfw3 3.3 REQUIRED)

# 找到GLEW
find_package(GLEW REQUIRED)

# 包含头文件目录
include_directories(include ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

# 添加可执行文件
add_executable(OpenGLDemo src/main.cpp src/GLSetup.cpp)

# 链接库文件
target_link_libraries(OpenGLDemo ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES})
