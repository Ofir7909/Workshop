#include "Node.h"

namespace workshop
{
int Node::s_Count = 0;

Node::Node(const NodeProperties& properties, const ImVec2& position): m_Properties(properties)
{
	m_ID = s_Count;
	s_Count++;

	// Set position
	imnodes::SetNodeScreenSpacePos(m_ID, position);

	for (const auto& attrib : m_Properties.AttributesProperties) { m_Attributes.emplace_back(attrib, (Node*)this); }
}
void Node::Draw()
{
	// Set Colors
	imnodes::PushColorStyle(imnodes::ColorStyle_TitleBar,
							IM_COL32(m_Properties.color.r, m_Properties.color.g, m_Properties.color.b, 255));

	glm::ivec3 highlightColor = glm::clamp((glm::vec3)m_Properties.color * 1.2f, glm::vec3(0), glm::vec3(255));
	IM_COL32(highlightColor.r * 255, highlightColor.g * 255, highlightColor.b * 255, 255);

	unsigned int tempColor = IM_COL32(highlightColor.r, highlightColor.g, highlightColor.b, 255);
	imnodes::PushColorStyle(imnodes::ColorStyle_TitleBarHovered, tempColor);
	imnodes::PushColorStyle(imnodes::ColorStyle_TitleBarSelected, tempColor);

	// Draw
	imnodes::BeginNode(m_ID);

	imnodes::BeginNodeTitleBar();
	ImGui::TextUnformatted(m_Properties.label.c_str());
	imnodes::EndNodeTitleBar();

	for (auto& attrib : m_Attributes) { attrib.Draw(); }

	imnodes::EndNode();

	// Clean up
	imnodes::PopColorStyle();
	imnodes::PopColorStyle();
	imnodes::PopColorStyle();
}
} // namespace workshop