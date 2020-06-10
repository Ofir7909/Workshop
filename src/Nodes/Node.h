#pragma once

#include "Common.h"
#include <imgui.h>
#include <imnodes.h>

#include <glm/glm.hpp>

#include "NodeAttribute.h"

namespace workshop
{
struct NodeProperties
{
	std::string filename;
	std::string label;
	std::string category;
	std::string description;
	glm::ivec3 color;
	std::vector<NodeAttributeProperties> AttributesProperties;
};

class Node
{
  public:
	Node(const NodeProperties& properties, const ImVec2& position);
	void Draw();

  private:
	int m_ID;
	NodeProperties m_Properties;
	std::vector<NodeAttribute> m_Attributes;

  private:
	static int s_Count;
};
} // namespace workshop
