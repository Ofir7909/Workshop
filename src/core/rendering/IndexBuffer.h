#pragma once

#include "common.h"

class IndexBuffer
{
  public:
	IndexBuffer(const void* data, uint32_t count)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	}
	~IndexBuffer() { glDeleteBuffers(1, &m_ID); }

	void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); }
	static void Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	uint32_t GetCount() const { return m_Count; }

  private:
	uint32_t m_ID;
	uint32_t m_Count;
};