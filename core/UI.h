#pragma once

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace workshop
{
class UIManager
{
  public:
	UIManager(GLFWwindow* window);
	~UIManager();

	void Draw();
};
} // namespace workshop