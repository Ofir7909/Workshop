#pragma once

#include "Common.h"
#include "UIWindow.h"

namespace workshop
{
class DockspaceWindow : public UIWindow
{
  public:
	DockspaceWindow();
	virtual void Draw() override;

  private:
	ImGuiDockNodeFlags m_DockspaceFlags;
};

DockspaceWindow::DockspaceWindow()
{
	m_WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
					ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
					ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	m_DockspaceFlags = ImGuiDockNodeFlags_None;

	if (m_DockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
		m_WindowFlags |= ImGuiWindowFlags_NoBackground;
}

void DockspaceWindow::Draw()
{
	// Set the window position
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->GetWorkPos());
	ImGui::SetNextWindowSize(viewport->GetWorkSize());
	ImGui::SetNextWindowViewport(viewport->ID);

	// Make some changes to the style (only apply to this window thanks to PopStyleVar())
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	// Draw
	ImGui::Begin("DockSpace Demo", &m_Show, m_WindowFlags);
	ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), m_DockspaceFlags);
	ImGui::End();

	// Clear style changes
	ImGui::PopStyleVar(3);
}
} // namespace workshop
