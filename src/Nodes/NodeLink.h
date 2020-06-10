#pragma once

#include "Common.h"

#include <imnodes.h>

namespace workshop
{
class NodeLink
{
  public:
	NodeLink(int start_attribute, int end_attribute, int* id = nullptr);
	~NodeLink();

	void Draw();
	inline int first() const { return m_attributes.first; }
	inline int second() const { return m_attributes.second; }

  private:
	int m_ID;
	std::pair<int, int> m_attributes;

  public:
	static std::unordered_map<int, NodeLink*> GetAll() { return s_Links; }

  private:
	static int s_Count;
	static std::unordered_map<int, NodeLink*> s_Links;
};
} // namespace workshop