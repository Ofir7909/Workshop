#include "Viewport.h"

#include <glad/glad.h>

#include "Vertex.h"

namespace workshop
{
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
	m_Shader = std::make_shared<Shader>("res/Shaders/basic.shader");

	// Vertex Buffer
	BufferLayout layout = {{ShaderDataType::Float3, "aPosition"}, {ShaderDataType::Float3, "aColor"}};
	m_VertexBuffer		= std::make_shared<VertexBuffer>(vertices, vertices.size() * sizeof(vertices[0]), layout);

	m_IndexBuffer = std::make_shared<IndexBuffer>(indicies, indicies.size());

	m_VertexArray = std::make_shared<VertexArray>(m_VertexBuffer, m_IndexBuffer);

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
	m_VertexArray->Bind();
	m_Shader->Bind();

	// Render
	glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}
} // namespace workshop
