#pragma once

#include "Common.h"
#include <imgui.h>

namespace workshop
{
class UIWindow
{
  public:
	virtual ~UIWindow() = default;

	virtual void Draw() = 0;

  protected:
	UIWindow()	= default;
	bool m_Show = true;
	ImGuiWindowFlags m_WindowFlags;
};
} // namespace workshop