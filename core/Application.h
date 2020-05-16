#pragma once

#include "Common.h"

#include <GLFW/glfw3.h>

#include "UI.h"

#ifndef WIDTH
#define WIDTH 800
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif

namespace workshop
{
class Application
{
  public:
	Application(char* name = "new app");
	~Application();

  private:
	GLFWwindow* m_Window;

	std::unique_ptr<UIManager> m_UIManager;
};
} // namespace workshop