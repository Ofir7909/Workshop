#pragma once

#include "Common.h"

#include "Buffer.h"

namespace workshop
{
class VertexArray
{
  public:
	VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer):
		m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer)
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);

		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();

		glBindVertexArray(0);
	}
	~VertexArray() {}

	void Bind() const { glBindVertexArray(m_RendererID); }
	static void Unbind() { glBindVertexArray(0); }

	const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

  private:
	unsigned int m_RendererID;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};
} // namespace workshop