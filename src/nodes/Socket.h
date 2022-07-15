#pragma once

#include "common.h"

#include "core/Geometry.h"

class BaseNode;

using SocketValue = std::variant<Geometry>;

enum class SocketType
{
	INPUT,
	OUTPUT,
};

enum class SocketDataType
{
	GEOMETRY,
	CURVE,
};

/**
 * Socket is the connection of a node, used to pass data between nodes
 */
class Socket
{
  public:
	Socket(SocketType type, SocketDataType dataType, const std::string& name, BaseNode* parent):
		m_Type(type), m_DataType(dataType), m_Name(name), m_ParentNode(parent)
	{
	}
	~Socket() {}

	const std::string& GetName() const { return m_Name; }

	template<typename T>
	T GetValue()
	{
		LOG_ASSERT(!m_Value, "Value is empty");
		auto dataType = GetSocketDataTypeOfT<T>();
		LOG_ASSERT(m_DataType == dataType, "Socket {} is not of type {}", m_Name, typeid(T).name());
		return std::get<T>(*m_Value);
	}

	template<typename T>
	void SetValue(const T& new_value)
	{
		auto dataType = GetSocketDataTypeOfT<T>();
		LOG_ASSERT(m_DataType == dataType, "Socket {} is not of type {}", m_Name, typeid(T).name());
		m_Value.reset();
		m_Value = CreateRef<SocketValue>(new_value);
	}

  public:
	template<typename T>
	static SocketDataType GetSocketDataTypeOfT()
	{
		if constexpr (std::is_same_v<T, Geometry>) {
			return SocketDataType::GEOMETRY;
			//} else if constexpr (std::is_same_v<T, Curve>) {
			//	return SocketDataType::CURVE;
		} else {
			LOG_ERROR("Unknown type {}", typeid(T).name());
		}
	}

  private:
	SocketType m_Type;
	std::string m_Name;
	SocketDataType m_DataType;
	BaseNode* m_ParentNode;
	Ref<SocketValue> m_Value;
};
