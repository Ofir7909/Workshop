#pragma once

#include "Common.h"

#include "GraphEntity.h"
#include "NodeGraph.h"
#include "Socket.h"

namespace workshop
{
class Node : public GraphEntity
{
  public:
	Node(NodeGraph* graph, const std::string& label = "Node"): GraphEntity(graph), m_Label(label) {}
	virtual ~Node() = default;

	template<typename T, typename... Args>
	void AddInputSocket(const Args&... args)
	{
		m_Sockets.emplace_back(m_Graph->AddSocket<T>(ID, Socket::Type::Input, args...));
	}
	template<typename T, typename... Args>
	void AddOutputSocket(const Args&... args)
	{
		m_Sockets.emplace_back(m_Graph->AddSocket<T>(ID, Socket::Type::Output, args...));
	}

	const std::string& GetLabel() const { return m_Label; }
	const std::vector<std::shared_ptr<Socket>>& GetSockets() const { return m_Sockets; }

  protected:
	std::string m_Label;
	std::vector<std::shared_ptr<Socket>> m_Sockets;
};

class AdditionNode : public Node
{
  public:
	AdditionNode(NodeGraph* graph): Node(graph, "Add")
	{
		AddInputSocket<FloatSocket>("A");
		AddInputSocket<FloatSocket>();
		AddOutputSocket<FloatSocket>("Result");
	}
	~AdditionNode() {};
};

class SplitNode : public Node
{
  public:
	SplitNode(NodeGraph* graph): Node(graph, "Split")
	{
		AddInputSocket<FloatSocket>("Vector");
		AddOutputSocket<FloatSocket>("X");
		AddOutputSocket<FloatSocket>("Y");
		AddOutputSocket<FloatSocket>("Z");
	}
	~SplitNode() {};
};
} // namespace workshop
