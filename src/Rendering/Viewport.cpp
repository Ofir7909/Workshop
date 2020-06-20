#include "Viewport.h"

#include "RenderCommand.h"
#include "Renderer.h"
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
	RenderCommand::SetClearColor({0.2f, 0.2f, 0.2f, 1.0f});
	RenderCommand::Clear();

	Renderer::BeginScene();
	m_Shader->Bind();

	Renderer::Submit(m_VertexArray);

	Renderer::EndScene();
}
} // namespace workshop
