#include "Viewport.h"

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

	m_VertexArray = std::make_shared<VertexArray>();

	// Vertex Buffer
	BufferLayout layout = {{ShaderDataType::Float3, "aPosition"}, {ShaderDataType::Float3, "aColor"}};
	m_VertexBuffer		= std::make_shared<VertexBuffer>(vertices, vertices.size() * sizeof(vertices[0]), layout);

	m_IndexBuffer = std::make_shared<IndexBuffer>(indicies, indicies.size());

	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	VertexArray::Unbind();
	IndexBuffer::Unbind();
	VertexBuffer::Unbind();
	Shader::Unbind();
}

void Viewport::Draw()
{
	// Clear the screen
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw
	m_Shader->Bind();
	m_VertexArray->Bind();
	glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
} // namespace workshop
