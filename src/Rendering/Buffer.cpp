#include "Buffer.h"

namespace workshop
{
// BufferLayout
BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements): m_Elements(elements)
{
	unsigned int offset = 0;

	for (auto& element : m_Elements) {
		element.Offset = offset;
		offset += element.Size;
	}

	m_Stride = offset;
}

// VertexBuffer
VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices, unsigned int size, const BufferLayout& layout):
	m_Layout(layout)
{
	glGenBuffers(1, &m_RendererID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

	// Attributes
	int index = 0;
	for (const auto& element : m_Layout.GetElements()) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.GetComponentCount(), element.GetComponentBaseType(), element.Normalized,
							  m_Layout.GetStride(), (const void*)element.Offset);

		index++;
	}
}
void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// IndexBuffer
IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices, unsigned int count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}
void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace workshop