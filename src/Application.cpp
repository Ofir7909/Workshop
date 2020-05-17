#include "Application.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <UI/DockspaceWindow.h>
#include <UI/NodeEditorWindow.h>

namespace workshop
{
// glfw error callback
void GLFWErrorCallback(int error, const char* description)
{
	fprintf(stderr, "[!] GLFWError: %s\n", description);
}

void GLAPIENTRY OpenGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
									const GLchar* message, const void* userParam)
{
	fprintf(stderr, "[!] OpenGL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

Application::Application(char* name)
{
	// Init GLFW
	glfwSetErrorCallback(GLFWErrorCallback);
	int glfw_err_code = glfwInit();
	assertf(glfw_err_code, "[!] Failed to Init GLFW");

	// cerate window
	m_Window = glfwCreateWindow(WIDTH, HEIGHT, name, NULL, NULL);
	assertf(m_Window != NULL, "[!] Failed to Create a Window");
	std::cout << "[-] Created a new window(WIDTHxHEIGHT)" << WIDTH << HEIGHT << std::endl;

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1); // Enable Vsync

	// Init GLAD
	int glad_err_code = gladLoadGL();
	assertf(glad_err_code, "[!] Failed to Init GLAD");

	// set openGL error callback
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGLErrorCallback, 0);

	// Set up the UI
	m_UIManager = std::make_unique<UIManager>(m_Window);
	m_UIManager->AddWindow(new DockspaceWindow());	// the Dockspace has to be the first window!=
	m_UIManager->AddWindow(new NodeEditorWindow()); // the Dockspace has to be the first window!=

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(m_Window)) {
		// Update viewport size
		int display_w, display_h;
		glfwGetFramebufferSize(m_Window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		// Clear the screen
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the ui
		m_UIManager->Draw();

		// Swap front and back buffers
		glfwSwapBuffers(m_Window);

		// Poll for and process events
		glfwPollEvents();
	}
}

Application::~Application()
{
	// We need to delete it early because it call glfw functions
	m_UIManager.reset();

	// clean glfw
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

} // namespace workshop
