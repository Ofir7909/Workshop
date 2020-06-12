#include "NodeManager.h"

#include <json.hpp>

namespace workshop
{
NodeManager::NodeManager()
{
	LoadNodes("res/Nodes/NodeDefinitions.json");
}

NodeManager::~NodeManager()
{
}

void NodeManager::LoadNodes(const std::string& filepath)
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
		assertf(attributes.is_array(), "Error Parsing json, 'attributes' of node %s is not an array !",
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

void NodeManager::AddNode(const NodeProperties& properties, const ImVec2& position)
{
	m_Nodes.emplace_back(std::make_unique<Node>(properties, position));
}

void NodeManager::TryAddLink(int start_attr, int end_attr)
{
	// Check for:
	// 1. Both attributes exist - V
	// 2. Attributes are diffrent type (input/output) - V
	// 3. Input Attribute is not connected - V
	// 4. Attributes value type is diffrent (or can be exchanged) for example (int
	// to float)
	// 5. They dont belong to the same node. - V
	auto attributes = NodeAttribute::GetAll();

	// Check the Attributes exist
	if (attributes.find(start_attr) == attributes.end() || attributes.find(end_attr) == attributes.end()) {
		return;
	}
	// Assign them to inputAttribute and outputAttribute at random, if they are
	// reveresed we will swap them later.
	NodeAttribute* inputAttribute  = attributes.at(start_attr);
	NodeAttribute* outputAttribute = attributes.at(end_attr);

	// If they are the same type exit.
	if (inputAttribute->GetProperties().type == outputAttribute->GetProperties().type)
		return;

	// Check if we assigned them in the wrong order, if so swap them.
	if (inputAttribute->GetProperties().type != NodeAttributeType_Input) {
		NodeAttribute* tmp = inputAttribute;
		inputAttribute	   = outputAttribute;
		outputAttribute	   = tmp;
	}

	// If input is Connected, for now exit. later we might want to override the
	// link.
	if (inputAttribute->ConnectedTo() != -1)
		return;

	// If Both have the same parent, exit.
	if (inputAttribute->GetParent() == outputAttribute->GetParent())
		return;

	int id;
	m_NodesLinks.emplace(id, std::make_unique<NodeLink>(start_attr, end_attr, &id));
}
} // namespace workshop