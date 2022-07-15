#pragma once

#include "common.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window
{
  public:
	Window(const std::string& title = "Workshop", uint32_t width = 1600, uint32_t height = 900);
	~Window();

	void Update();

	// TEMP
	bool ShouldClose() const { return glfwWindowShouldClose(m_GLFWWindow); }

	GLFWwindow* GetGLFWWindow() const { return m_GLFWWindow; }
	glm::ivec2 GetSize() const;
	bool GetVSync() const { return m_Data.VSync; }
	void SetVSync(bool VSync);

  private:
	struct WindowData
	{
		std::string Title;
		uint32_t Width, Height;
		bool VSync;
	};

	WindowData m_Data;
	GLFWwindow* m_GLFWWindow;
};