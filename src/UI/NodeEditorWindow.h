#pragma once

#include "Common.h"
#include "UIWindow.h"

#include "Nodes/Node.h"
#include "Nodes/NodeLink.h"
#include <imnodes.h>

#include <json.hpp>

namespace workshop
{
class NodeEditorWindow : public UIWindow
{
  public:
	NodeEditorWindow();
	virtual void Draw() override;
	void LoadNodes(std::string filepath);

  private:
	std::vector<Node> m_Nodes; // Nodes on the Editor.
	std::vector<NodeLink> m_NodesLinks;
	std::vector<NodeProperties> m_NodeDefinitions; // Each entry is a diffrent node type(loaded from a
												   // json file)
};

NodeEditorWindow::NodeEditorWindow()
{
	// m_NodeDefinitions.emplace_back(NodeProperties {"Test Name", "Cat5",
	// "Descirption"}); m_NodeDefinitions.emplace_back(NodeProperties {"Add Node",
	// "Cat5", "Descirption"}); m_NodeDefinitions.emplace_back(
	//	NodeProperties {"A RElly long name asdasdas asdfasdfas Test Name",
	//"Cat5", "Descirption"});

	LoadNodes("res/Nodes/NodeDefinitions.json");

	m_Nodes.emplace_back(m_NodeDefinitions[0]);
	m_Nodes.emplace_back(m_NodeDefinitions[1]);
	m_Nodes.emplace_back(m_NodeDefinitions[0]);
	m_Nodes.emplace_back(m_NodeDefinitions[1]);
	m_Nodes.emplace_back(m_NodeDefinitions[2]);
}

void NodeEditorWindow::Draw()
{
	// start the window
	ImGui::Begin("node editor");
	imnodes::BeginNodeEditor();

	// Draw nodes
	for (auto node : m_Nodes) node.Draw();

	// Draw links
	for (auto link : m_NodesLinks) { link.Draw(); }

	// End tje window
	imnodes::EndNodeEditor();
	ImGui::End();

	// Update Links
	int start_attr, end_attr;
	if (imnodes::IsLinkCreated(&start_attr, &end_attr)) {
		m_NodesLinks.emplace_back(start_attr, end_attr);
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
			auto type		 = (attrib.at("type") == "input") ? NodeAttributeType_Input : NodeAttributeType_Output;
			attribProps.type = type;

			props.AttributesProperties.emplace_back(attribProps);
		}
		m_NodeDefinitions.emplace_back(props);
	}
}

} // namespace workshop