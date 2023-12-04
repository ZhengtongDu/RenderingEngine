# 代码层次布置

1. **项目目录结构**:
   - `/include` - 放置头文件。
   - `/src` - 放置源文件。
   - `/external` - 外部库文件。
   - `/assets` - 资源文件，如纹理、模型等。
   - `/shaders` - GLSL着色器文件。
   - `/tests` - 测试代码。

2. **主要组件**:
   - `main.cpp` - 程序入口，设置OpenGL和ImGui环境。
   - `Application.h/cpp` - 应用程序核心，管理渲染循环和事件。
   - `ImGuiLayer.h/cpp` - ImGui层，用于渲染UI和处理UI事件。
   - `RenderLayer.h/cpp` - OpenGL渲染器，处理所有OpenGL渲染调用。
   - `OCCTInterface.h/cpp` - OCCT接口，用于与OCCT库交互。
   - `GeometryEditor.h/cpp` - 几何图形编辑器，用于几何图形的创建和编辑。

3. **预留OCCT接口**:
   - 在`OCCTInterface`中定义接口函数，以便将OCCT集成到应用程序中。
   - 提供方法加载、显示和操作OCCT几何数据。
