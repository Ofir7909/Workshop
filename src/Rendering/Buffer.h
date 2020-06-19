#pragma once

#include "Common.h"
#include "Vertex.h"

#include <glad/glad.h>

namespace workshop
{
enum class ShaderDataType
{
	None = 0,
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	Int,
	Int2,
	Int3,
	Int4,
	Bool

};

struct BufferElement
{
	std::string Name;
	ShaderDataType Type;
	bool Normalized;
	unsigned int Size	= 0;
	unsigned int Offset = 0;

	BufferElement() {}
	BufferElement(ShaderDataType type, const std::string& name, bool normalized = false):
		Type(type), Name(name), Normalized(normalized)
	{
		Size = ShaderDataTypeSize();
	}

	unsigned int ShaderDataTypeSize()
	{
		switch (Type) {
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3: return 4 * 3 * 3;
		case ShaderDataType::Mat4: return 4 * 4 * 4;
		case ShaderDataType::Int: return 4;
		case ShaderDataType::Int2: return 4 * 2;
		case ShaderDataType::Int3: return 4 * 3;
		case ShaderDataType::Int4: return 4 * 4;
		case ShaderDataType::Bool: return 1;
		}
		WORKSHOP_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	unsigned int GetComponentCount() const
	{
		switch (Type) {
		case ShaderDataType::Float: return 1;
		case ShaderDataType::Float2: return 2;
		case ShaderDataType::Float3: return 3;
		case ShaderDataType::Float4: return 4;
		case ShaderDataType::Mat3: return 3 * 3;
		case ShaderDataType::Mat4: return 4 * 4;
		case ShaderDataType::Int: return 1;
		case ShaderDataType::Int2: return 2;
		case ShaderDataType::Int3: return 3;
		case ShaderDataType::Int4: return 4;
		case ShaderDataType::Bool: return 1;
		}

		WORKSHOP_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	GLenum GetComponentBaseType() const
	{
		switch (Type) {
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Bool: return GL_BOOL;
		}

		WORKSHOP_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
};

class BufferLayout
{
  public:
	BufferLayout() {}
	BufferLayout(const std::initializer_list<BufferElement>& elements);

	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

  private:
	std::vector<BufferElement> m_Elements;
	unsigned int m_Stride = 0;
};

class VertexBuffer
{
  public:
	VertexBuffer() {}
	VertexBuffer(const std::vector<Vertex>& vertices, unsigned int size, const BufferLayout& layout);
	~VertexBuffer();

	void Bind() const;
	static void Unbind();

	const BufferLayout& GetLayout() const { return m_Layout; }
	void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

  private:
	unsigned int m_RendererID;
	BufferLayout m_Layout;
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
