#include "NodeEditorWindow.h"

namespace workshop
{
NodeEditorWindow::NodeEditorWindow()
{
	LoadNodes("res/Nodes/NodeDefinitions.json");
}

void NodeEditorWindow::Draw()
{
	// start the window
	ImGui::Begin("node editor");
	imnodes::BeginNodeEditor();

	// Draw nodes
	for (auto node : m_Nodes) { node.Draw(); }

	// Draw links
	for (auto link : m_NodesLinks) { link.second.Draw(); }

	// End tje window
	imnodes::EndNodeEditor();
	ImGui::End();

	// Update Links
	int start_attr, end_attr;
	if (imnodes::IsLinkCreated(&start_attr, &end_attr)) {
		int id;
		NodeLink nodeLink(start_attr, end_attr, &id);
		m_NodesLinks.emplace(id, nodeLink);
	}

	// Add Node Menu (right mouse click)
	if (ImGui::GetIO().MouseClicked[1]) {
		ImGui::OpenPopup("add_node_menu");
	}

	if (ImGui::BeginPopup("add_node_menu")) {
		ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
		ImGui::Text("Add Node");
		for (auto nodeDef : m_NodeDefinitions) {
			if (ImGui::MenuItem(nodeDef.first.c_str())) {
				m_Nodes.emplace_back(nodeDef.second, click_pos);
			}
		}
		ImGui::EndPopup();
	}
}

void NodeEditorWindow::LoadNodes(std::string filepath)
{
	using json = nlohmann::json;

	// open json file
	std::ifstream file(filepath);
	assertf(file.is_open(), "Failed to open file %s", filepath.c_str());

	// Parsing the file
	json j;
	file >> j;

	// Node array
	auto nodes = j.at("nodes");
	assertf(nodes.is_array(), "Error Parsing json, 'nodes' is not an array!");

	// For each node
	for (auto node : nodes) {
		NodeProperties props;
		node.at("filename").get_to(props.filename);
		node.at("label").get_to(props.label);
		node.at("category").get_to(props.category);
		node.at("description").get_to(props.description);
		auto col	= node.at("color");
		props.color = glm::ivec3(col[0], col[1], col[2]);

		auto attributes = node.at("attributes");
		assertf(attributes.is_array(), "Error Parsing json, 'attributes' of node % s is not an array !",
				props.filename.c_str());

		for (auto attrib : attributes) {
			NodeAttributeProperties attribProps;
			attrib.at("label").get_to(attribProps.label);
			auto type		 = NodeAttributeProperties::StringToType(attrib.at("type"));
			attribProps.type = type;

			props.AttributesProperties.emplace_back(attribProps);
		}
		m_NodeDefinitions.emplace(props.label, props);
	}
}
} // namespace workshop