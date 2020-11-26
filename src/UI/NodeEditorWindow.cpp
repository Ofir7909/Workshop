#include "NodeEditorWindow.h"

namespace workshop
{
void NodeEditorWindow::Draw()
{
	// start the window
	ImGui::Begin("node editor");
	imnodes::BeginNodeEditor();

	// End the window
	imnodes::EndNodeEditor();
	ImGui::End();
}

} // namespace workshop