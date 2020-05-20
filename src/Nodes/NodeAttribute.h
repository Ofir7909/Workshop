#pragma once

#include "../Common.h"
#include <imgui.h>
#include <imnodes.h>

namespace workshop
{
enum NodeAttributeType
{
	NodeAttributeType_Input,
	NodeAttributeType_Output
};

struct NodeAttributeProperties
{
	NodeAttributeType type;
	std::string label;
};

class NodeAttribute
{
  public:
	NodeAttribute(const NodeAttributeProperties& properties);
	void Draw();

  private:
	int m_ID;
	NodeAttributeProperties m_Properties;

  private:
	static int s_Count;
};

} // namespace workshop
