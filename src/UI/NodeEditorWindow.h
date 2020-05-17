#pragma once

#include "Common.h"
#include "UIWindow.h"

#include "Nodes/Node.h"
#include "Nodes/NodeLink.h"
#include <imnodes.h>

namespace workshop
{
class NodeEditorWindow : public UIWindow
{
  public:
	NodeEditorWindow();
	virtual void Draw() override;

  private:
	std::vector<Node> m_Nodes;
	std::vector<NodeLink> m_NodesLinks;
};

NodeEditorWindow::NodeEditorWindow()
{
	m_Nodes.emplace_back("Test Node 1 REALY LONG NAMEMEEMEMMEMEMEMEM");
	m_Nodes.emplace_back("Test Node 2");
	m_Nodes.emplace_back("Test Node 3");
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

} // namespace workshop