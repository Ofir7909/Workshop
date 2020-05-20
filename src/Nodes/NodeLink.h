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
} // namespace workshop