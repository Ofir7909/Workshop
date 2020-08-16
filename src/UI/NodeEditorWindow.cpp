#include "NodeEditorWindow.h"

namespace workshop
{
void NodeEditorWindow::Draw()
{
	// start the window
	ImGui::Begin("node editor");
	imnodes::BeginNodeEditor();

	// Draw Nodes
	for (const auto& node : m_Graph->GetNodes()) {
		imnodes::BeginNode(node->ID);

		imnodes::BeginNodeTitleBar();
		ImGui::TextUnformatted(node->GetLabel().c_str());
		imnodes::EndNodeTitleBar();

		for (const auto& socket : node->GetSockets()) {
			if (socket->GetType() == Socket::Type::Input)
				imnodes::BeginInputAttribute(socket->ID);
			else if (socket->GetType() == Socket::Type::Output)
				imnodes::BeginOutputAttribute(socket->ID);
			else {
				WORKSHOP_ERROR("Socket has no valid type!");
			}
			ImGui::Text(socket->GetLabel().c_str());
			imnodes::EndAttribute();
		}
		// for (const auto& attrib : m_Attributes) { attrib->Draw(); }

		imnodes::EndNode();
	}

	// Set Colors
	/*imnodes::PushColorStyle(imnodes::ColorStyle_TitleBar,
							IM_COL32(m_Properties.color.r, m_Properties.color.g, m_Properties.color.b, 255));

	glm::ivec3 highlightColor = glm::clamp((glm::vec3)m_Properties.color * 1.2f, glm::vec3(0), glm::vec3(255));
	IM_COL32(highlightColor.r * 255, highlightColor.g * 255, highlightColor.b * 255, 255);

	unsigned int tempColor = IM_COL32(highlightColor.r, highlightColor.g, highlightColor.b, 255);
	imnodes::PushColorStyle(imnodes::ColorStyle_TitleBarHovered, tempColor);
	imnodes::PushColorStyle(imnodes::ColorStyle_TitleBarSelected, tempColor);

	// Clean up
	imnodes::PopColorStyle();
	imnodes::PopColorStyle();
	imnodes::PopColorStyle();
	*/

	// Draw nodes
	// for (const auto& node : m_Graph->GetNodes()) { node->Draw(); }

	// Draw links
	// for (const auto& link : m_Graph->GetLinks()) { link.second->Draw(); }

	// End the window
	imnodes::EndNodeEditor();
	ImGui::End();

	// Check for Update Links
	/*
	int start_attr, end_attr;
	if (imnodes::IsLinkCreated(&start_attr, &end_attr)) {
		m_NodeManager->TryAddLink(start_attr, end_attr);
	}
	*/

	// Add Node Menu (right mouse click)
	/*if (ImGui::GetIO().MouseClicked[1]) {
		ImGui::OpenPopup("add_node_menu");
	}

	if (ImGui::BeginPopup("add_node_menu")) {
		ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
		ImGui::Text("Add Node");

		for (const auto& name : NodeManager::GetNodeNames()) {
			if (ImGui::MenuItem(name.c_str())) {
				// Add Node
				m_Graph->AddNode();

				WORKSHOP_INFO("Added Node {}", name);
			}
		}
		ImGui::EndPopup();
	}
	*/
}

} // namespace workshop