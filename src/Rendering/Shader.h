#pragma once

#include "Common.h"

namespace workshop
{
class Shader
{
  public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	static void Unbind();

	// void SetUniform4f(const std::string& name, int value);

  private:
	// int GetUniformLocation(const std::string& name);

	unsigned int CreateShaderProgram(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);

  private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
};
} // namespace workshop
