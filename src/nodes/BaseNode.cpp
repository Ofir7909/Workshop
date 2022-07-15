#include "BaseNode.h"

// Sockets
void BaseNode::AddInSocket(SocketDataType dataType, const std::string& name)
{
	m_Inputs.push_back(CreateScope<Socket>(SocketType::INPUT, dataType, name, this));
}

void BaseNode::AddOutSocket(SocketDataType dataType, const std::string& name)
{
	m_Inputs.push_back(CreateScope<Socket>(SocketType::OUTPUT, dataType, name, this));
}

// Get Parameters

Parameter* BaseNode::GetParameter(size_t index)
{
	if (index >= m_Parameters.size())
		return nullptr;

	return m_Parameters.at(index).get();
}

Parameter* BaseNode::GetParameter(const std::string& name)
{
	if (auto result = ranges::find_if(m_Parameters, [name](const auto& p) { return p->GetName() == name; });
		result != m_Parameters.end()) {
		return (*result).get();
	}

	LOG_WARN("Parameter '{}' does not exist in node '{}'", name, m_Name);
	return nullptr;
}

// Get Sockets

Socket* BaseNode::GetInput(size_t index)
{
	if (index >= m_Inputs.size())
		return nullptr;

	return m_Inputs.at(index).get();
}

Socket* BaseNode::GetInput(const std::string& name)
{
	if (auto result = ranges::find_if(m_Inputs, [name](const auto& s) { return s->GetName() == name; });
		result != m_Inputs.end()) {
		return (*result).get();
	}

	LOG_WARN("Input Socket '{}' does not exist in node '{}'", name, m_Name);
	return nullptr;
}

Socket* BaseNode::GetOutput(size_t index)
{
	if (index >= m_Outputs.size())
		return nullptr;

	return m_Inputs.at(index).get();
}
Socket* BaseNode::GetOutput(const std::string& name)
{
	if (auto result = ranges::find_if(m_Outputs, [name](const auto& s) { return s->GetName() == name; });
		result != m_Outputs.end()) {
		return (*result).get();
	}

	LOG_WARN("Output Socket '{}' does not exist in node '{}'", name, m_Name);
	return nullptr;
}