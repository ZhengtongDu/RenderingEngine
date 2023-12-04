cmake_minimum_required(VERSION 3.10)

project(MyGuiApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 找到OpenGL
find_package(OpenGL REQUIRED)

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

# 添加OCCT库（确保路径正确）
set(OCCT_DIR "${CMAKE_SOURCE_DIR}/external/occt")
# ... 这里你需要添加OCCT的库和include路径

# 添加你的源文件
add_executable(MyGuiApp
    src/main.cpp
    # 其他cpp文件
)

# 链接OpenGL、GLFW、ImGui和OCCT到你的项目
target_link_libraries(MyGuiApp
    OpenGL::GL
    glfw
    imgui
    ${CMAKE_DL_LIBS} # 添加这行来链接libdl
    # OCCT库
)

# 包含头文件目录
target_include_directories(MyGuiApp PRIVATE include)
