#pragma once

#include "Common.h"

#include <imnodes.h>

namespace workshop
{
class NodeLink
{
  public:
	NodeLink(int start_attribute, int end_attribute);
	void Draw();

  private:
	int m_ID;
	int m_attributes[2];

  private:
	static int s_Count;
};

int NodeLink::s_Count = 0;

NodeLink::NodeLink(int start_attribute, int end_attribute): m_attributes {start_attribute, end_attribute}
{
	m_ID = s_Count;
	s_Count++;
}

void NodeLink::Draw()
{
	imnodes::Link(m_ID, m_attributes[0], m_attributes[1]);
}

} // namespace workshop