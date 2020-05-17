#pragma once

#include "Common.h"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imnodes.h>

#include "UIWindow.h"

namespace workshop
{
class UIManager
{
  public:
	UIManager(GLFWwindow* window);
	~UIManager();

	void Draw();

	std::vector<UIWindow*> GetWindows() const { return m_Windows; }
	void AddWindow(UIWindow* window) { m_Windows.emplace_back(window); }

  private:
	std::vector<UIWindow*> m_Windows;
};
} // namespace workshop