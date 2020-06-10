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

	template<typename T>
	void AddWindow()
	{
		m_Windows.emplace_back(std::make_unique<T>());
	}

  private:
	std::vector<std::unique_ptr<UIWindow>> m_Windows;
};
} // namespace workshop