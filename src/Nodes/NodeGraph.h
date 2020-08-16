#pragma once

#include "Common.h"

#include "Socket.h"

namespace workshop
{
class Node;

class NodeGraph
{
	using SocketVector_type = std::vector<std::tuple<unsigned int, Socket::Type, std::shared_ptr<Socket>>>;

  public:
	NodeGraph()	 = default;
	~NodeGraph() = default;

	// void TryAddLink(int start_attr, int end_attr);

	template<typename T, typename... Args>
	void AddNode(const Args&... args)
	{
		m_Nodes.emplace_back(std::make_unique<T>(this, args...));
	}

	template<typename T, typename... Args>
	std::shared_ptr<T> AddSocket(unsigned int nodeID, Socket::Type type, const Args&... args)
	{
		auto socket = std::make_shared<T>(this, type, args...);
		m_Sockets.emplace_back(std::make_tuple(nodeID, type, socket));
		return socket;
	}

	const std::vector<std::unique_ptr<Node>>& GetNodes() const { return m_Nodes; }
	const SocketVector_type& GetSockets() const { return m_Sockets; }

  private:
	std::vector<std::unique_ptr<Node>> m_Nodes;
	SocketVector_type m_Sockets;
};

} // namespace workshop