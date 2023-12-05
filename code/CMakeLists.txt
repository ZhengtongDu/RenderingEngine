cmake_minimum_required(VERSION 3.10)

project(MyGuiApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)


# 包含头文件目录
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    # 如果有其他依赖，也应该包含它们的头文件目录
)

# 添加ImGui库
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui")
add_library(imgui
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_include_directories(imgui PUBLIC ${IMGUI_DIR}/backends)

# 将源文件添加到此变量
set(SOURCE_FILES
    src/main.cpp
    src/Application.cpp
    #src/Geometry.cpp
    #src/Renderer.cpp
    #src/EventHandler.cpp
    # 如果有其他源文件，也应该添加到这里
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 链接OpenGL、GLFW、ImGui和其他必要的库
target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
    imgui
    ${CMAKE_DL_LIBS} # 链接动态链接库
    # 如果需要其他库，也应该在这里链接
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

