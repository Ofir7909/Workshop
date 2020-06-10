#include "UIManager.h"

namespace workshop
{
UIManager::UIManager(GLFWwindow* window)
{
	// Imgui setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// General Config
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// ImGui Theme
	ImGui::StyleColorsDark();
	ImVec4* colors				= ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg].w = 1.0f;

	// ImGui init
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	// Imnodes init
	imnodes::Initialize();
}

UIManager::~UIManager()
{
	// clean imnodes
	imnodes::Shutdown();

	// clean imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UIManager::Draw()
{
	// Start a new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Draw all the windows
	for (auto const& window : m_Windows) { window->Draw(); }

	// Exampe Window 1
	// Just to test docking, Remove it later
	ImGui::ShowDemoWindow();

	// Render to buffer
	ImGui::Render();
	// Draw to the window
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace workshop
