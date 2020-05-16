#include "UI.h"

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
}

UIManager::~UIManager()
{
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
	// Example window for now
	{
		// Window with Docking Space
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
										ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
										ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
										ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		static bool isOpen = true;
		ImGui::Begin("DockSpace Demo", &isOpen, window_flags);
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		ImGui::End();

		ImGui::PopStyleVar(3);
	}

	{ // Exampe Window 1
		ImGui::ShowDemoWindow();
	}

	{ // Exampe Window 2
		static bool show_another_window = true;
		// 3. Show another simple window.
		if (show_another_window) {
			ImGui::Begin("Another Window",
						 &show_another_window); // Pass a pointer to our bool variable (the window will have a closing
												// button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
	}

	// Render to buffer
	ImGui::Render();
	// Draw to the window
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace workshop
