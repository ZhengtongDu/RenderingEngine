#include "ImGuiLayer.h"
#include "imgui.h"

ImGuiLayer::ImGuiLayer() {
    // ImGui initialization
}

ImGuiLayer::~ImGuiLayer() {
    // ImGui cleanup
}

void ImGuiLayer::Begin() {
    // Start the ImGui frame
    ImGui::NewFrame();
}

void ImGuiLayer::End() {
    // End the ImGui frame
    ImGui::Render();
    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
