#pragma once

#include "common.h"

#include <glad/glad.h>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
  public:
	Shader(const std::string& filepath)
	{
		auto sources = ParseShaderFromFile(filepath);
		m_ID = CreateShaderProgram(sources.VertexSource, sources.FragmentSource);
		glUseProgram(m_ID);
	}
	~Shader() { glDeleteProgram(m_ID); }

	void Bind() const { glUseProgram(m_ID); }
	static void Unbind() { glUseProgram(0); }

	void SetUniform1f(const std::string& name, float v) { glProgramUniform1f(m_ID, GetUniformLocation(name), v); }

	void SetUniform3f(const std::string& name, const glm::vec3& v)
	{
		glProgramUniform3f(m_ID, GetUniformLocation(name), v.x, v.y, v.z);
	}

	void SetUniform4f(const std::string& name, const glm::vec4& v)
	{
		glProgramUniform4f(m_ID, GetUniformLocation(name), v.x, v.y, v.z, v.w);
	}

	void SetUniformMat4(const std::string& name, const glm::mat4& v)
	{
		glProgramUniformMatrix4fv(m_ID, GetUniformLocation(name), 1, GL_FALSE, &v[0][0]);
	}

  private:
	static ShaderProgramSource ParseShaderFromFile(const std::string& filepath);
	static uint32_t CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
	static uint32_t CompileShader(uint32_t type, const std::string& source);

	int GetUniformLocation(const std::string& name)
	{
		auto cacheLocation = m_UniformCache.find(name);
		if (cacheLocation != m_UniformCache.end()) {
			return cacheLocation->second;
		}

		int location = glGetUniformLocation(m_ID, name.c_str());
		if (location == -1) {
			LOG_WARN("Can't find shader uniform '{}'", name);
		}
		m_UniformCache.emplace(name, location);
		return location;
	}

  private:
	uint32_t m_ID;
	std::unordered_map<std::string, int> m_UniformCache;
};