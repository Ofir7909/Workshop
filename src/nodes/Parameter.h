#pragma once

#include "common.h"

class BaseNode;

using ParameterValue = std::variant<int32_t, float, std::string, bool, glm::vec2, glm::vec3, glm::vec4>;

enum class ParameterDataType
{
	INT,
	FLOAT,
	STRING,
	BOOL,
	VEC2,
	VEC3,
	VEC4,
	RGB,
	RGBA,
};

/**
 * Parameters are used to modify the behaviour of nodes
 */
class Parameter
{
  public:
	template<typename T>
	Parameter(ParameterDataType type, const std::string& name, const T& defaultValue, BaseNode* parent):
		m_Type(type), m_Name(name), m_DefaultValue(defaultValue), m_Value(defaultValue), m_Node(parent)
	{
	}

	const std::string& GetName() const { return m_Name; }

	template<typename T>
	const T& GetValue() const
	{
		auto type = GetParameterDataTypeOfT<T>();
		LOG_ASSERT(m_Type == type, "Parameter {} is not of type {}", m_Name, typeid(T).name());
		return std::get<T>(m_Value);
	}

  public:
	template<typename T>
	static ParameterDataType GetParameterDataTypeOfT()
	{
		if constexpr (std::is_same_v<T, int>) {
			return ParameterDataType::INT;
		} else if constexpr (std::is_same_v<T, float>) {
			return ParameterDataType::FLOAT;
		} else if constexpr (std::is_same_v<T, std::string>) {
			return ParameterDataType::STRING;
		} else if constexpr (std::is_same_v<T, bool>) {
			return ParameterDataType::BOOL;
		} else if constexpr (std::is_same_v<T, glm::vec2>) {
			return ParameterDataType::VEC2;
		} else if constexpr (std::is_same_v<T, glm::vec3>) {
			return ParameterDataType::VEC3;
		} else if constexpr (std::is_same_v<T, glm::vec4>) {
			return ParameterDataType::VEC4;
		} else if constexpr (std::is_same_v<T, Color_RGB>) {
			return ParameterDataType::RGB;
		} else if constexpr (std::is_same_v<T, Color_RGBA>) {
			return ParameterDataType::RGBA;
		} else {
			LOG_ERROR("Unknown type {}", typeid(T).name());
		}
	}

  private:
	ParameterDataType m_Type;
	std::string m_Name;
	ParameterValue m_Value;
	const ParameterValue m_DefaultValue;
	BaseNode* m_Node;
};