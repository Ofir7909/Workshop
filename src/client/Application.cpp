#include "Application.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
	if (s_Instance) {
		LOG_ERROR("Threre is already an application! Cannot be 2!");
	}
	s_Instance = this;

	Log::Init();
	m_Window = CreateScope<Window>();

	const std::string glsl_version = "#version 460";

	// ImGui Panels
	Scope<PanelManager> panelManager = CreateScope<PanelManager>(m_Window->GetGLFWWindow(), glsl_version);
	panelManager->AddPanel<TestPanel>("Hello world");
	panelManager->AddPanel<ViewportPanel>();

	// render loop
	while (!m_Window->ShouldClose()) {
		// Update deltaTime
		Time::UpdateTime();

		//  Draw UI to buffer
		panelManager->Draw(m_Window->GetSize());

		// Poll Events and draw to screen.
		m_Window->Update();
	}

	// Cleanup
	// Need to call distructor before glfw terminatation.
	panelManager.reset();
}