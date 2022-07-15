#pragma once

#include "common.h"

#include "VertexBuffer.h"

struct VertexBufferElement
{
	GLenum type;
	uint32_t count;
	GLboolean normalized;

	static size_t GetSizeOfT(GLenum type)
	{
		switch (type) {
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		LOG_ERROR("Type not implemented.");
		return 0;
	}
};

class VertexBufferLayout
{
  public:
	VertexBufferLayout() {}

	auto begin() { return m_Elements.begin(); }
	auto end() { return m_Elements.end(); }
	auto begin() const { return m_Elements.begin(); }
	auto end() const { return m_Elements.end(); }

	template<typename T>
	void Push(uint32_t count)
	{
		LOG_ERROR("Unimplemented Type in VertexBufferLayout");
	}
	template<>
	void Push<float>(uint32_t count)
	{
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfT(GL_FLOAT) * count;
	}
	template<>
	void Push<GLuint>(uint32_t count)
	{
		m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfT(GL_UNSIGNED_INT) * count;
	}

	uint32_t GetStride() const { return m_Stride; }

  private:
	std::vector<VertexBufferElement> m_Elements;
	uint32_t m_Stride = 0;
};

class VertexArray
{
  public:
	VertexArray()
	{
		glGenVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);
	}

	~VertexArray() { glDeleteVertexArrays(1, &m_ID); }

	void Bind() const { glBindVertexArray(m_ID); }
	static void Unbind() { glBindVertexArray(0); }

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		vb.Bind();
		this->Bind();
		std::for_each(layout.begin(), layout.end(),
					  [idx = 0u, offset = 0ull, stride = layout.GetStride()](const auto& e) mutable {
						  glEnableVertexAttribArray(idx);
						  glVertexAttribPointer(idx, e.count, e.type, e.normalized, stride, (const void*)offset);

						  offset += VertexBufferElement::GetSizeOfT(e.type) * e.count;
						  idx++;
					  });
	}

  private:
	uint32_t m_ID;
};