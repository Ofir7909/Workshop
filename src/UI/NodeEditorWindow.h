#pragma once

#include "Common.h"
#include "UIWindow.h"

#include <imnodes.h>

namespace workshop
{
class NodeEditorWindow : public UIWindow
{
  public:
	NodeEditorWindow();
	virtual void Draw() override;
};

NodeEditorWindow::NodeEditorWindow()
{
}

void NodeEditorWindow::Draw()
{
	// NOTE TO SELF:
	// Almost everything in imnodes:: need a uniq id.
	//

	ImGui::Begin("node editor");
	imnodes::BeginNodeEditor();

	{ // First node
		imnodes::BeginNode(0);
		imnodes::BeginNodeTitleBar();
		ImGui::TextUnformatted("output node");
		imnodes::EndNodeTitleBar();
		ImGui::Text("Add");
		ImGui::Dummy(ImVec2(150.0f, 45.0f));

		// Output node
		imnodes::BeginOutputAttribute(0, imnodes::PinShape_Quad);
		ImGui::Text("out");
		imnodes::EndAttribute();

		imnodes::BeginInputAttribute(1);
		ImGui::Text("A");
		imnodes::EndAttribute();

		imnodes::EndNode();
	}

	{ // Second node
		imnodes::BeginNode(1);
		ImGui::Text("Add");
		ImGui::Dummy(ImVec2(80.0f, 45.0f));

		// Output node
		imnodes::BeginOutputAttribute(2);
		ImGui::Text("output pin");
		imnodes::EndAttribute();

		imnodes::BeginInputAttribute(3);
		ImGui::Text("A");
		imnodes::EndAttribute();

		imnodes::EndNode();
	}

	// Draw links
	static std::vector<std::pair<int, int>> links;

	for (int i = 0; i < links.size(); ++i) {
		const std::pair<int, int> p = links[i];
		// in this case, we just use the array index of the link
		// as the unique identifier
		imnodes::Link(i, p.first, p.second);
	}

	imnodes::EndNodeEditor();
	ImGui::End();

	int start_attr, end_attr;
	if (imnodes::IsLinkCreated(&start_attr, &end_attr)) {
		links.push_back(std::make_pair(start_attr, end_attr));
	}
}

} // namespace workshop