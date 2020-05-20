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
	std::unordered_map<int, NodeLink> m_NodesLinks;
	std::map<std::string, NodeProperties> m_NodeDefinitions; // Each entry is a diffrent node type(loaded from
															 // a json file)
};
} // namespace workshop