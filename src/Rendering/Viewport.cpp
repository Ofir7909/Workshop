#include "Viewport.h"

#include <glad/glad.h>

#include "Vertex.h"

namespace workshop
{
unsigned int fbo;
unsigned int VAO;

Viewport::Viewport()
{
	// clang-format off
	std::vector<Vertex> vertices{
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f)}
	};

	std::vector<unsigned int> indicies{
		0,1,2,
		2,3,0
	};
	// clang-format on

	// Shader
	m_Shader = std::make_unique<Shader>("res/Shaders/basic.shader");

	// Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Vertex Buffer
	BufferLayout layout = {{ShaderDataType::Float3, "aPosition"}, {ShaderDataType::Float3, "aColor"}};
	m_VertexBuffer		= std::make_unique<VertexBuffer>(vertices, vertices.size() * sizeof(vertices[0]), layout);

	// Index Buffer
	m_IndexBuffer = std::make_unique<IndexBuffer>(indicies, indicies.size());

	glBindVertexArray(0); // Always unbind first
	IndexBuffer::Unbind();
	VertexBuffer::Unbind();
	Shader::Unbind();
}

void Viewport::Draw()
{
	// Clear the screen
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind all objects.
	glBindVertexArray(VAO);
	m_Shader->Bind();

	// Render
	// glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
} // namespace workshop
