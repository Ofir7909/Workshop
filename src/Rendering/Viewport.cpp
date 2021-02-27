#include "Viewport.h"

#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Vertex.h"

namespace workshop
{
Viewport::Viewport()
{
	// clang-format off
	std::vector<Vertex> vertices{
		{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f)},
		{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.1f)},
		{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.2f)},
		{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.3f)},

		{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.4f)},
		{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.5f)},
		{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.6f)},
		{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.7f)}
	};

	std::vector<unsigned int> indicies{
		0, 1, 2, //Front Z=1
		2, 3, 0,
		4, 5, 6, //Back Z=-1
		6, 7, 4,
		0, 1, 5, //Bottom Y=-1
		4, 5, 0,
		2, 3, 7, //Top Y=1
		7, 6, 2,
		1, 2, 6, //Right X=1
		6, 5, 1,
		0, 3, 7, //Left X=-1
		7, 4, 0
	};
	// clang-format on

	m_Camera = std::make_shared<Camera>(glm::vec3 {0.0f, 0.0f, 3.0f}, glm::vec3 {0.0f, 0.0f, 0.0f});

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
	glEnable(GL_DEPTH_TEST);

	// Clear the screen
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 trans = m_Camera->GetViewMatrix();
	trans			= glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
	trans			= glm::scale(trans, glm::vec3(0.5f));
	trans			= glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.4f, 0.7f, 1.0f));

	// Draw
	m_Shader->Bind();
	m_Shader->SetUniformMatrix4f("uMVP", trans);

	m_VertexArray->Bind();
	glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
} // namespace workshop
