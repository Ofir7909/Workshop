#pragma once

#include "Common.h"
#include "UIWindow.h"

#include "Nodes/Node.h"
#include "Nodes/NodeGraph.h"

#include <imnodes.h>
namespace workshop
{
class NodeEditorWindow : public UIWindow
{
  public:
	NodeEditorWindow()
	{
		// Remove from here
		m_Graph = std::make_shared<NodeGraph>();
		m_Graph->AddNode<AdditionNode>();
		m_Graph->AddNode<AdditionNode>();
		m_Graph->AddNode<AdditionNode>();
		m_Graph->AddNode<SplitNode>();
		m_Graph->AddNode<SplitNode>();
	}
	virtual void Draw() override;

  private:
	std::shared_ptr<NodeGraph> m_Graph;
};
} // namespace workshop