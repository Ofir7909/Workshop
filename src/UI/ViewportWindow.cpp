#include "ViewportWindow.h"

namespace workshop
{
ViewportWindow::ViewportWindow()
{
	m_Viewport = std::make_unique<Viewport>();
}

void ViewportWindow::Draw()
{
	ImGui::Begin("Viewport");
	auto windowSize = ImGui::GetContentRegionMax();
	windowSize.y -= 30; // Try to find a better solution
	ImGui::Image((void*)m_Viewport->GetColorBufferID(), windowSize);
	m_Viewport->Draw(windowSize.x, windowSize.y);

	ImGui::End();
}
} // namespace workshop