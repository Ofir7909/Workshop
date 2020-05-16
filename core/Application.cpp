#include "Application.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace workshop
{
Application::Application(char* name)
{
	// Init GLFW
	int glfw_err_code = glfwInit();
	assertf(glfw_err_code, "[!] Failed to Init GLFW");

	// cerate window
	m_Window = glfwCreateWindow(WIDTH, HEIGHT, name, NULL, NULL);
	assertf(m_Window != NULL, "[!] Failed to Create a Window");
	std::cout << "[-] Created a new window(WIDTHxHEIGHT)" << WIDTH << HEIGHT << std::endl;

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1); // Enable Vsync

	// Init GLAD
	int glad_err_code = gladLoadGL();
	assertf(glad_err_code, "[!] Failed to Init GLAD");

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
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_Window)) {
		/* Render here */

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{ // IMGUI WINDOW
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

		ImGui::ShowDemoWindow();

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
		// finish imgui frame
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_Window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		// Clear the screen
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw imgui to the buffer
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

Application::~Application()
{
	// clean imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// clean glfw
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

} // namespace workshop
