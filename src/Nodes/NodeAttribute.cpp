#include "NodeAttribute.h"

#include "NodeLink.h"

namespace workshop
{
int NodeAttribute::s_Count = 0;
std::unordered_map<int, NodeAttribute*> NodeAttribute::s_NodeAttributes;

NodeAttribute::NodeAttribute(const NodeAttributeProperties& properties, Node* parent):
	m_Properties(properties), m_ParentNode(parent)
{
	m_ID = s_Count;
	s_Count++;

	s_NodeAttributes.emplace(m_ID, this);
}

NodeAttribute::~NodeAttribute()
{
	// s_NodeAttributes.erase(m_ID);
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

// Return the ID of the connected attribute. if not connected return -1.
int NodeAttribute::ConnectedTo() const
{
	for (auto& [linkID, link] : NodeLink::GetAll()) {
		if (m_ID == link->first())
			return link->second();
		else if (m_ID == link->second())
			return link->first();
	}
	return -1;
}
} // namespace workshop