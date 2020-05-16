#pragma once

#include "Common.h"

namespace workshop
{
class DemoWindow : public UIWindow
{
  public:
	virtual void Draw() override;
};

void DemoWindow::Draw()
{
	if (m_Show) {
		ImGui::Begin("Demo Window", &m_Show);
		ImGui::Text("Hello from Demo window! :)");
		if (ImGui::Button("Close Me"))
			m_Show = false;
		ImGui::End();
	}
}
} // namespace workshop