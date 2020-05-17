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

class NodeAttribute
{
  public:
	NodeAttribute(NodeAttributeType type, const std::string& name);
	void Draw();

  private:
	int m_ID;
	std::string m_Name;
	NodeAttributeType m_Type;

  private:
	static int s_Count;
};

} // namespace workshop
