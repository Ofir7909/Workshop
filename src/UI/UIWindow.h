#pragma once

#include "Common.h"
#include <imgui.h>

namespace workshop
{
class UIWindow
{
  public:
	virtual void Draw() = 0;

  protected:
	bool m_Show = true;
	ImGuiWindowFlags m_WindowFlags;
};
} // namespace workshop