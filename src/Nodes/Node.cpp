#include "Node.h"

namespace workshop
{
int Node::s_Count = 0;

Node::Node(const std::string& name): m_Name(name)
{
	m_ID = s_Count;
	s_Count++;

	m_Attributes.emplace_back(NodeAttributeType_Input, "In");
	m_Attributes.emplace_back(NodeAttributeType_Output, "Out");
}
void Node::Draw()
{
	imnodes::BeginNode(m_ID);

	imnodes::BeginNodeTitleBar();
	ImGui::TextUnformatted(m_Name.c_str());
	imnodes::EndNodeTitleBar();

	for (auto attrib : m_Attributes) { attrib.Draw(); }

	imnodes::EndNode();
}
} // namespace workshop