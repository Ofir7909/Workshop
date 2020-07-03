#pragma once

#include "Common.h"

#include "Buffer.h"

namespace workshop
{
class VertexArray
{
  public:
	VertexArray();
	~VertexArray() {}

	void Bind() const;
	static void Unbind();

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

  private:
	unsigned int m_RendererID;
	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};
} // namespace workshop