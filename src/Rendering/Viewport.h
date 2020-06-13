#pragma once

#include "../Common.h"

#include "Shader.h"

namespace workshop
{
class Viewport
{
  public:
	Viewport();
	void Draw();

  private:
	Shader m_Shader;
};
} // namespace workshop