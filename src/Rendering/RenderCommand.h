#pragma once

#include "Common.h"
#include "glm/glm.hpp"

#include "VertexArray.h"

namespace workshop
{
class RenderCommand
{
  public:
	static void SetClearColor(const glm::vec4& color);
	static void Clear();
	static void DrawIndexed(const std::shared_ptr<VertexArray> vertexArray);
};
} // namespace workshop