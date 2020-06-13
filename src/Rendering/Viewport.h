#pragma once

#include "../Common.h"

#include "Buffer.h"
#include "Shader.h"

namespace workshop
{
class Viewport
{
  public:
	Viewport();
	void Draw();

  private:
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<VertexBuffer> m_VertexBuffer;
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
};
} // namespace workshop