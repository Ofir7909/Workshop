#pragma once

#include "Common.h"

namespace workshop
{
class NodeGraph;

class GraphEntity
{
  protected:
	GraphEntity(NodeGraph* graph): ID(s_Counter), m_Graph(graph) { s_Counter++; }

  public:
	virtual ~GraphEntity() = default;

  public:
	const unsigned int ID;

  protected:
	NodeGraph* m_Graph;

  private:
	static unsigned int s_Counter;
};
} // namespace workshop