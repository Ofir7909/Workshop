#include "PanelManager.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

PanelManager::PanelManager(GLFWwindow* glfwWindow, const std::string glslVersion)
{
	// imgui setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	  // Enable Docking

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init(glslVersion.c_str());

	// Setup Dear ImGui style
	// TODO: Cooler style
	ImGui::StyleColorsDark();
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg].w = 1.0f;
}

PanelManager::~PanelManager()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void MenuBar()
{
	ImGui::BeginMainMenuBar();
	ImGui::Text("Test Menubar");
	ImGui::Button("Test");
	ImGui::EndMainMenuBar();
}

void PanelManager::Draw(const glm::ivec2& window_size)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Dockspace
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	// Menubar
	MenuBar();

	ranges::for_each(m_Panels, [](const auto& p) {
		ImGui::Begin(p->GetTitle().c_str());
		p->Draw();
		ImGui::End();
	});
	ImGui::ShowDemoWindow(); // TEMP

	ImGui::Render();
	glViewport(0, 0, window_size.x, window_size.y);
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
