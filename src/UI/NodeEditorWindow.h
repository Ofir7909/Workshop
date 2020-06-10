#pragma once

#include "Common.h"
#include "UIWindow.h"

#include "Nodes/NodeManager.h"
#include <imnodes.h>
namespace workshop
{
class NodeEditorWindow : public UIWindow
{
  public:
	NodeEditorWindow();
	virtual void Draw() override;

  private:
	std::unique_ptr<NodeManager> m_NodeManager;
};
} // namespace workshop