#pragma once

#include "common.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Input
{
  public:
	static glm::vec2 GetMosuePosition();
	static bool IsMouseButtonPressed(int button);

	static bool IsKeyPressed(int key);
	static float GetAxis(int keyNegative, int keyPositive);
};