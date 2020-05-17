#pragma once

#include "Common.h"
#include "UIWindow.h"

#include "Nodes/Node.h"
#include <imnodes.h>

namespace workshop {
class NodeEditorWindow : public UIWindow {
public:
  NodeEditorWindow();
  virtual void Draw() override;

private:
  std::vector<Node> m_Nodes;
};

NodeEditorWindow::NodeEditorWindow() {
  m_Nodes.emplace_back("Test Node 1 REALY LONG NAMEMEEMEMMEMEMEMEM");
  m_Nodes.emplace_back("Test Node 2");
  m_Nodes.emplace_back("Test Node 3");
}

void NodeEditorWindow::Draw() {
  // NOTE TO SELF:
  // Almost everything in imnodes:: need a uniq id.
  //

  ImGui::Begin("node editor");
  imnodes::BeginNodeEditor();

  for (auto node : m_Nodes)
    node.Draw();

  // Draw links
  /*
  static std::vector<std::pair<int, int>> links;

  for (int i = 0; i < links.size(); ++i) {
    const std::pair<int, int> p = links[i];
    // in this case, we just use the array index of the link
    // as the unique identifier
    imnodes::Link(i, p.first, p.second);
  }
  */

  imnodes::EndNodeEditor();
  ImGui::End();

  /*int start_attr, end_attr;
  if (imnodes::IsLinkCreated(&start_attr, &end_attr)) {
    links.push_back(std::make_pair(start_attr, end_attr));
  }
  */
}

} // namespace workshop