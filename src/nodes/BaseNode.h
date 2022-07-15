#pragma once

#include "common.h"

#include "Parameter.h"
#include "Socket.h"

/*
 * BaseNode is the base class for nodes.
 * It's not meant to be used directly, and should only be inherited by other classes.
 */
class BaseNode
{
  protected:
	BaseNode() {}

  public:
	virtual ~BaseNode() {}

	const std::string& GetName() const { return m_Name; }

	Parameter* GetParameter(size_t index);
	Parameter* GetParameter(const std::string& name);

	Socket* GetInput(size_t index);
	Socket* GetInput(const std::string& name);

	Socket* GetOutput(size_t index);
	Socket* GetOutput(const std::string& name);

  protected:
	void AddInSocket(SocketDataType dataType, const std::string& name);
	void AddOutSocket(SocketDataType dataType, const std::string& name);

	template<typename T>
	void AddParameter(const std::string& name, const T& defaultValue)
	{
		auto type = Parameter::GetParameterDataTypeOfT<T>();
		m_Parameters.push_back(CreateScope<Parameter>(type, name, defaultValue, this));
	}

	virtual void Process() = 0;

  protected:
	std::string m_Name;
	std::vector<Scope<Socket>> m_Inputs;
	std::vector<Scope<Socket>> m_Outputs;
	std::vector<Scope<Parameter>> m_Parameters;
};