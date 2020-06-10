#pragma once

#include "../Common.h"
#include <imgui.h>
#include <imnodes.h>

namespace workshop
{
class Node;

enum NodeAttributeType
{
	NodeAttributeType_Input,
	NodeAttributeType_Output
};

struct NodeAttributeProperties
{
	NodeAttributeType type;
	std::string label;

	static inline NodeAttributeType StringToType(std::string str)
	{
		return (str == "input") ? NodeAttributeType_Input : NodeAttributeType_Output;
	}
};

class NodeAttribute
{
  public:
	NodeAttribute(const NodeAttributeProperties& properties, Node* parent);
	~NodeAttribute();

	void Draw();
	int ConnectedTo() const;
	inline NodeAttributeProperties const& GetProperties() const { return m_Properties; }

	inline Node* GetParent() const { return m_ParentNode; }

  private:
	int m_ID;
	NodeAttributeProperties m_Properties;
	Node* m_ParentNode;

  public:
	static std::unordered_map<int, NodeAttribute*> GetAll() { return s_NodeAttributes; }

  private:
	static int s_Count;
	static std::unordered_map<int, NodeAttribute*> s_NodeAttributes;
};

} // namespace workshop