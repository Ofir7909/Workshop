#pragma once

#include "Common.h"

#include "GraphEntity.h"

namespace workshop
{
class NodeGraph;

class Socket : public GraphEntity
{
  public:
	enum class Type : unsigned char
	{
		Input,
		Output
	};

  protected:
	Socket(NodeGraph* graph, Type type, const std::string& label = "Socket"):
		GraphEntity(graph), m_Label(label), m_Type(type)
	{
	}

  public:
	virtual ~Socket() {};

	const std::string& GetLabel() const { return m_Label; }
	Type GetType() const { return m_Type; }

	virtual void Update() {}

  protected:
	std::string m_Label;
	Type m_Type;
};

class FloatSocket : public Socket
{
  public:
	FloatSocket(NodeGraph* graph, Type type, const std::string& label = "Float Slider"): Socket(graph, type, label) {}

	virtual void Update() override
	{
		// Here add clamp check
	}
};
} // namespace workshop