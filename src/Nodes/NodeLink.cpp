#include "NodeLink.h"

namespace workshop
{
int NodeLink::s_Count = 0;
std::unordered_map<int, NodeLink*> NodeLink::s_Links;

NodeLink::NodeLink(int start_attribute, int end_attribute, int* id): m_attributes(start_attribute, end_attribute)
{
	m_ID = s_Count;
	s_Count++;

	if (id != nullptr)
		*id = m_ID;

	s_Links.emplace(m_ID, this);
}

NodeLink::~NodeLink()
{
	// s_Links.erase(m_ID);
}

void NodeLink::Draw()
{
	imnodes::Link(m_ID, m_attributes.first, m_attributes.second);
}

} // namespace workshop