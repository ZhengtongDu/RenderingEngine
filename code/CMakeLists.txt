cmake_minimum_required(VERSION 3.10)
project(MyGuiApp)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找OpenGL，并设置OpenGL的策略（如果你使用的是CMake 3.11及以上版本）
find_package(OpenGL REQUIRED)
cmake_policy(SET CMP0072 NEW)

# 查找GLM库
find_package(glm REQUIRED)

# 添加ImGui库
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui")
add_library(imgui
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
)
target_include_directories(imgui PUBLIC "${IMGUI_DIR}")
target_include_directories(imgui PUBLIC "${IMGUI_DIR}/backends")

# 添加Glad库
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/external/glad")
add_library(glad "${GLAD_DIR}/glad.c")
target_include_directories(glad PUBLIC "${GLAD_DIR}/include")

# 添加STB Image的实现文件
set(STB_IMAGE_DIR "${CMAKE_SOURCE_DIR}/external/stb")
add_library(stb_image "${STB_IMAGE_DIR}/stb_image.cpp")
target_include_directories(stb_image PUBLIC "${STB_IMAGE_DIR}")

# 将源文件添加到此变量
set(SOURCE_FILES
    "src/main.cpp"
    "src/Application.cpp"
    # 如果有其他源文件，也应该添加到这里
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 链接OpenGL、GLFW、ImGui、Glad和GLM库
target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
    imgui
    glad
    stb_image
    ${CMAKE_DL_LIBS} # 链接动态链接库
)

# 包含头文件目录
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
    # 如果有其他依赖，也应该包含它们的头文件目录
)
