#pragma once

#include "Common.h"

#include "Buffer.h"
#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"

namespace workshop
{
class Viewport
{
  public:
	Viewport();
	void Draw(float width, float height);

  private:
	std::shared_ptr<Camera> m_Camera;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;
};
} // namespace workshop