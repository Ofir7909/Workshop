#pragma once

#include "Common.h"

#include "Nodes/Node.h"
#include "Nodes/NodeLink.h"

namespace workshop
{
class NodeManager
{
  public:
	NodeManager();
	~NodeManager();

	void LoadNodes(const std::string& filepath);
	void AddNode(const NodeProperties& properties, const ImVec2& position);
	void TryAddLink(int start_attr, int end_attr);

	inline std::vector<Node>& GetNodes() { return m_Nodes; }
	inline std::unordered_map<int, std::unique_ptr<NodeLink>>& GetLinks() { return m_NodesLinks; }
	inline std::map<std::string, NodeProperties>& GetNodeDefinitions() { return m_NodeDefinitions; }

  private:
	std::vector<Node> m_Nodes; // Nodes on the Editor.
	std::unordered_map<int, std::unique_ptr<NodeLink>> m_NodesLinks;
	std::map<std::string, NodeProperties> m_NodeDefinitions; // Each entry is a diffrent node type(loaded from
															 // a json file)
};
} // namespace workshop