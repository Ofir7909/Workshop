#include "NodeLink.h"

namespace workshop
{
int NodeLink::s_Count = 0;

NodeLink::NodeLink(int start_attribute, int end_attribute, int* id): m_attributes {start_attribute, end_attribute}
{
	m_ID = s_Count;
	s_Count++;

	if (id != nullptr)
		*id = m_ID;
}

void NodeLink::Draw()
{
	imnodes::Link(m_ID, m_attributes[0], m_attributes[1]);
}

} // namespace workshop