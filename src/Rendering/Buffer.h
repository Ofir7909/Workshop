#pragma once

#include "Common.h"
#include "Vertex.h"

namespace workshop
{
class VertexBuffer
{
  public:
	VertexBuffer(const std::vector<Vertex>& vertices, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	static void Unbind();

  private:
	unsigned int m_RendererID;
};

class IndexBuffer
{
  public:
	IndexBuffer(const std::vector<unsigned int>& indices, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	static void Unbind();

  private:
	unsigned int m_RendererID;
};

} // namespace workshop
