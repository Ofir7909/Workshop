#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

class Time
{
  public:
	static void UpdateTime()
	{
		auto newTime = glfwGetTime();
		deltaTime = newTime - time;
		time = newTime;
	}

	static float time;
	static float deltaTime;
};
