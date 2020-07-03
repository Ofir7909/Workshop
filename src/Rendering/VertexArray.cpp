#include "VertexArray.h"

namespace workshop
{
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	this->Bind();
	vertexBuffer->Bind();

	// Attributes
	int index		   = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout.GetElements()) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.GetComponentCount(), element.GetComponentBaseType(), element.Normalized,
							  layout.GetStride(), (const void*)element.Offset);

		index++;
	}

	m_VertexBuffers.emplace_back(vertexBuffer);
}
void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	this->Bind();
	indexBuffer->Bind();

	m_IndexBuffer = indexBuffer;
}
} // namespace workshop