#pragma once

#include "common.h"

class VertexBuffer
{
  public:
	VertexBuffer(const void* data, size_t size)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	~VertexBuffer() { glDeleteBuffers(1, &m_ID); }

	void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }
	static void Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

  private:
	uint32_t m_ID;
};