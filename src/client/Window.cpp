#include "Window.h"

#include <glad/glad.h>

static uint8_t s_GLFWWindowCount = 0;

void GLFWErrorCallback(int error, const char* description)
{
	LOG_ERROR("GLFW Error ({}): {}", error, description);
}

void GLAPIENTRY OpenGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
									const GLchar* message, const void* userParam)
{
	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		LOG_ERROR("OpenGL Error (source: {}, type: {}): {}", source, type, message);
		return;
	}
	LOG_INFO("OpenGL Callback (source: {}, type: {}): {}", source, type, message);
}

Window::Window(const std::string& title, uint32_t width, uint32_t height):
	m_Data {.Title = title, .Width = width, .Height = height}
{
	LOG_INFO("Creating GLFW Window {} ({}, {})", m_Data.Title, m_Data.Width, m_Data.Height);

	// First Time, Init GLFW
	if (s_GLFWWindowCount == 0) {
		glfwSetErrorCallback(GLFWErrorCallback);

		int success = glfwInit();
		LOG_ASSERT(success, "Failed to initalize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	m_GLFWWindow = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
	s_GLFWWindowCount++;

	glfwMakeContextCurrent(m_GLFWWindow);
	glfwSetWindowUserPointer(m_GLFWWindow, &m_Data);
	int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	LOG_ASSERT(success, "Failed to initalize GLAD");

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGLErrorCallback, 0);

	glViewport(0, 0, m_Data.Width, m_Data.Height);

	// GLFW Callbacks
	glfwSetWindowSizeCallback(m_GLFWWindow, [](GLFWwindow* window, int width, int height) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.Width = width;
		data.Height = height;

		glViewport(0, 0, width, height);
	});
}

Window::~Window()
{
	glfwDestroyWindow(m_GLFWWindow);
	s_GLFWWindowCount--;

	if (s_GLFWWindowCount == 0) {
		glfwTerminate();
	}
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_GLFWWindow);
}

glm::ivec2 Window::GetSize() const
{
	return {m_Data.Width, m_Data.Height};
}

void Window::SetVSync(bool VSync)
{
	glfwSwapInterval((int)VSync);
	m_Data.VSync = VSync;
}
