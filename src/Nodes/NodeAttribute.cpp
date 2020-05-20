#include "NodeAttribute.h"

namespace workshop
{
int NodeAttribute::s_Count = 0;

NodeAttribute::NodeAttribute(const NodeAttributeProperties& properties): m_Properties(properties)
{
	m_ID = s_Count;
	s_Count++;
}

void NodeAttribute::Draw()
{
	if (m_Properties.type == NodeAttributeType_Input)
		imnodes::BeginInputAttribute(m_ID);
	else
		imnodes::BeginOutputAttribute(m_ID);

	ImGui::Text(m_Properties.label.c_str());
	imnodes::EndAttribute();
}
} // namespace workshop