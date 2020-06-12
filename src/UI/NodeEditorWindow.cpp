#include "NodeEditorWindow.h"

namespace workshop
{
NodeEditorWindow::NodeEditorWindow()
{
	m_NodeManager = std::make_unique<NodeManager>();
}

void NodeEditorWindow::Draw()
{
	// start the window
	ImGui::Begin("node editor");
	imnodes::BeginNodeEditor();

	// Draw nodes
	for (const auto& node : m_NodeManager->GetNodes()) { node->Draw(); }

	// Draw links
	for (const auto& link : m_NodeManager->GetLinks()) { link.second->Draw(); }

	// End the window
	imnodes::EndNodeEditor();
	ImGui::End();

	// Check for Update Links
	int start_attr, end_attr;
	if (imnodes::IsLinkCreated(&start_attr, &end_attr)) {
		m_NodeManager->TryAddLink(start_attr, end_attr);
	}

	// Add Node Menu (right mouse click)
	if (ImGui::GetIO().MouseClicked[1]) {
		ImGui::OpenPopup("add_node_menu");
	}

	if (ImGui::BeginPopup("add_node_menu")) {
		ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
		ImGui::Text("Add Node");
		for (const auto& [name, definition] : m_NodeManager->GetNodeDefinitions()) {
			if (ImGui::MenuItem(name.c_str())) {
				m_NodeManager->AddNode(definition, click_pos);
			}
		}
		ImGui::EndPopup();
	}
}

} // namespace workshop