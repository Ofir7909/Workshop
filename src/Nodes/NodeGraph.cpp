#include "NodeGraph.h"

namespace workshop
{
/*
void NodeGraph::TryAddLink(int start_attr, int end_attr)
{
	// Check for:
	// 1. Both attributes exist - V
	// 2. Attributes are diffrent type (input/output) - V
	// 3. Input Attribute is not connected - V
	// 4. Attributes value type is diffrent (or can be exchanged) for example (int
	// to float)
	// 5. They dont belong to the same node. - V
	auto attributes = NodeAttribute::GetAll();

	// Check the Attributes exist
	if (attributes.find(start_attr) == attributes.end() || attributes.find(end_attr) == attributes.end()) {
		return;
	}
	// Assign them to inputAttribute and outputAttribute at random, if they are
	// reveresed we will swap them later.
	NodeAttribute* inputAttribute  = attributes.at(start_attr);
	NodeAttribute* outputAttribute = attributes.at(end_attr);

	// If they are the same type exit.
	if (inputAttribute->GetProperties().type == outputAttribute->GetProperties().type)
		return;

	// Check if we assigned them in the wrong order, if so swap them.
	if (inputAttribute->GetProperties().type != NodeAttributeType_Input) {
		NodeAttribute* tmp = inputAttribute;
		inputAttribute	   = outputAttribute;
		outputAttribute	   = tmp;
	}

	// If input is Connected, for now exit. later we might want to override the
	// link.
	if (inputAttribute->ConnectedTo() != -1)
		return;

	// If Both have the same parent, exit.
	if (inputAttribute->GetParent() == outputAttribute->GetParent())
		return;

	int id;
	m_NodesLinks.emplace(id, std::make_unique<NodeLink>(start_attr, end_attr, &id));
}
*/
} // namespace workshop