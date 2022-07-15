#include "common.h"

// Glad must be included before glfw
#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Window.h"
#include "core/Time.h"
#include "nodes/geometry_nodes/Node_Translate.h"
#include "panels/PanelManager.h"
#include "panels/ViewportPanel.h"

class TestPanel : public BasePanel
{
  public:
	TestPanel(const std::string& msg): BasePanel("Test panel"), m_Msg(msg) {}
	void Draw() override
	{
		ImGui::Text(m_Msg.c_str());
		ImGui::Button("Click Me!");
	}

  private:
	std::string m_Msg;
};

class Application
{
  public:
	static Application& Get() { return *s_Instance; }

  public:
	Application();
	~Application() = default;

	const Window& GetWindow() const { return *m_Window; }

  private:
	static Application* s_Instance;

  private:
	Scope<Window> m_Window;
};
