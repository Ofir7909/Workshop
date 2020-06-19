#pragma once

#include "Common.h"

#include "Buffer.h"

namespace workshop
{
class VertexArray
{
  public:
	VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& IndexBuffer)
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);

		vertexBuffer->Bind();
		IndexBuffer->Bind();

		glBindVertexArray(0);
	}
	~VertexArray() {}

	void Bind() const { glBindVertexArray(m_RendererID); }
	static void Unbind() { glBindVertexArray(0); }

  private:
	unsigned int m_RendererID;
};
} // namespace workshop