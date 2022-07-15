#include "Input.h"

#include "Application.h"

// Helper Functions
GLFWwindow* GetWindow()
{
	return Application::Get().GetWindow().GetGLFWWindow();
}

// Mouse
glm::vec2 Input::GetMosuePosition()
{
	auto win = GetWindow();
	double x, y;
	glfwGetCursorPos(win, &x, &y);
	return {x, y};
}

bool Input::IsMouseButtonPressed(int button)
{
	auto win = GetWindow();
	return glfwGetMouseButton(win, button);
}

// Keyboard
bool Input::IsKeyPressed(int key)
{
	auto win = GetWindow();
	auto state = glfwGetKey(win, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

float Input::GetAxis(int keyNegative, int keyPositive)
{
	return IsKeyPressed(keyPositive) - IsKeyPressed(keyNegative);
}