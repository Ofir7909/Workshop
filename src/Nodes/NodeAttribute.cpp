#include "NodeAttribute.h"

namespace workshop
{
int NodeAttribute::s_Count = 0;

NodeAttribute::NodeAttribute(NodeAttributeType type, const std::string& name): m_Type(type), m_Name(name)
{
	m_ID = s_Count;
	s_Count++;
}

void NodeAttribute::Draw()
{
	if (m_Type == NodeAttributeType_Input)
		imnodes::BeginInputAttribute(m_ID);
	else
		imnodes::BeginOutputAttribute(m_ID);

	ImGui::Text(m_Name.c_str());
	imnodes::EndAttribute();
}
} // namespace workshop