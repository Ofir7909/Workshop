#include "Application.h"

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <UI/DockspaceWindow.h>
#include <UI/NodeEditorWindow.h>
#include <UI/ViewportWindow.h>

namespace workshop
{
// glfw error callback
void GLFWErrorCallback(int error, const char* description)
{
	WORKSHOP_ERROR("GLFW Error: {}", description);
}

void GLAPIENTRY OpenGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
									const GLchar* message, const void* userParam)
{
	// clang-format off
	static std::map<GLenum, std::string> glToString = {	
		// Source (source)
		{GL_DEBUG_SOURCE_API, "API"},
		{GL_DEBUG_SOURCE_WINDOW_SYSTEM, "Window System"},
		{GL_DEBUG_SOURCE_SHADER_COMPILER, "Shader Compiler"},
		{GL_DEBUG_SOURCE_THIRD_PARTY, "Third Party"},
		{GL_DEBUG_SOURCE_APPLICATION, "Application"},
		{GL_DEBUG_SOURCE_OTHER, "Other"},
		
		// Type (type)
		{GL_DEBUG_TYPE_ERROR, "Error"},
		{GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "Deprecated Behavior"},
		{GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "Undefined Behavior"},
		{GL_DEBUG_TYPE_PORTABILITY, "Portability"},
		{GL_DEBUG_TYPE_PERFORMANCE, "Performance"},
		{GL_DEBUG_TYPE_OTHER, "Other"},
		{GL_DEBUG_TYPE_MARKER, "Marker"},
		{GL_DEBUG_TYPE_PUSH_GROUP, "Push Group"},
		{GL_DEBUG_TYPE_POP_GROUP, "Pop Group"},
		
		// Error Codes (id)
		{GL_NO_ERROR, "No Error"},
		{GL_INVALID_ENUM, "Invalid Enum"},
		{GL_INVALID_VALUE, "Invalid Value"},
		{GL_INVALID_OPERATION, "Invalid Operation"},
		{GL_STACK_OVERFLOW, "Stack Overflow"},
		{GL_STACK_UNDERFLOW, "Stack Underflow"},
		{GL_OUT_OF_MEMORY, "Out Of Memory"},

		// Severity (severity)
		{GL_DEBUG_SEVERITY_HIGH, "HIGH"},
		{GL_DEBUG_SEVERITY_MEDIUM, "MEDIUM"},
 		{GL_DEBUG_SEVERITY_LOW, "LOW"},
		{GL_DEBUG_SEVERITY_NOTIFICATION, "Notification"},		
	};
	// clang-format on

	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		return;

	if (type == GL_DEBUG_TYPE_ERROR) {
		WORKSHOP_WARN("***OPENGL ERROR*** {0}\nSource: {1}\nType: {2}\nSeverity: {3}\n{4}", glToString[id],
					  glToString[source], glToString[type], glToString[severity], message);
		return;
	}
	WORKSHOP_WARN("OpenGL CALLBACK: {0}\nSource: {1}\nType: {2}\nSeverity: {3}\n{4}", glToString[id],
				  glToString[source], glToString[type], glToString[severity], message);
}

Application::Application(char* name)
{
	// Initialize our logging library.
	Log::Init();

	// Init GLFW
	glfwSetErrorCallback(GLFWErrorCallback);
	int glfw_err_code = glfwInit();
	WORKSHOP_ASSERT(glfw_err_code, "Failed to Init GLFW");

	WORKSHOP_INFO("Using OpenGL version {0}.{1}", 4, 6);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// cerate window
	m_Window = glfwCreateWindow(WIDTH, HEIGHT, name, NULL, NULL);
	WORKSHOP_ASSERT(m_Window != NULL, "Failed to Create a Window");
	WORKSHOP_INFO("Created a new window({0} x {1})", WIDTH, HEIGHT);

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(0); // Disable Vsync

	// Init GLAD
	int glad_err_code = gladLoadGL();
	WORKSHOP_ASSERT(glad_err_code, "Failed to Init GLAD");

	// set openGL error callback
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(OpenGLErrorCallback, 0);

	// Set up the UI
	m_UIManager = std::make_unique<UIManager>(m_Window);
	m_UIManager->AddWindow<DockspaceWindow>(); // The Dockspace must be first!!!
	m_UIManager->AddWindow<NodeEditorWindow>();
	m_UIManager->AddWindow<ViewportWindow>();

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
