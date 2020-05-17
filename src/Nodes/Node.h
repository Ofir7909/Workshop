#pragma once

#include "Common.h"
#include <imgui.h>
#include <imnodes.h>

#include "Nodes/NodeAttribute.h"

namespace workshop
{
class Node
{
  public:
	Node(const std::string& name);
	void Draw();

  private:
	int m_ID;
	std::string m_Name;
	std::vector<NodeAttribute> m_Attributes;

  private:
	static int s_Count;
};
} // namespace workshop
