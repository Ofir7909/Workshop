#pragma once

#include "Common.h"
#include "glm/glm.hpp"

#include "VertexArray.h"

namespace workshop
{
class Renderer
{
  public:
	static void BeginScene();
	static void EndScene();
	static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
};
} // namespace workshop
