#pragma once

#include "common.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "BasePanel.h"

class PanelManager
{
  public:
	PanelManager(GLFWwindow* glfwWindow, const std::string glslVersion);
	~PanelManager();

	template<typename T, typename... Args>
	void AddPanel(const Args&... args)
	{
		m_Panels.emplace_back(CreateScope<T>(args...));
	}

	void Draw(const glm::ivec2& window_size);

  private:
	std::vector<Scope<BasePanel>> m_Panels;
};