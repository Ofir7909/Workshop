#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace workshop
{
Shader::Shader(const std::string& filepath): m_Filepath(filepath)
{
	m_RendererID = CreateShaderProgram(filepath);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

int Shader::GetUniformLocation(const std::string& name)
{
	auto iter = m_UniformLocationCache.find(name);

	if (iter != m_UniformLocationCache.end()) {
		return iter->second; // return the location stored in cache
	}

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1) {
		WORKSHOP_WARN("Uniform doesn't exist: %s", name);
	}
	m_UniformLocationCache[name] = location;
	return location;
}

unsigned int Shader::CreateShaderProgram(const std::string& filepath)
{
	enum class ShaderType
	{
		NONE	 = -1,
		VERTEX	 = 0,
		FRAGMENT = 1
	};

	// Parse the shader file
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			} else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			} else {
				WORKSHOP_ERROR("Failed to parse the shader!");
			}
		} else {
			if (type == ShaderType::NONE) {
				continue;
			}

			ss[(int)type] << line << '\n';
		}
	}

	// Compiling sub shaders
	unsigned int vertexShader	= CompileShader(GL_VERTEX_SHADER, ss[(int)ShaderType::VERTEX].str());
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, ss[(int)ShaderType::FRAGMENT].str());

	// Linking
	unsigned int id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	// Error handling
	int success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		int length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> message(length);
		glGetProgramInfoLog(m_RendererID, length, &length, &message[0]);
		WORKSHOP_ERROR("Error linking shader\n{0}", message.data());

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(id);
		return 0;
	}

	// Clean up
	glDetachShader(id, vertexShader);
	glDetachShader(id, fragmentShader);

	return id;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	// Compiling
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	// Error Handling
	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> message(length);
		glGetShaderInfoLog(id, length, &length, &message[0]);

		WORKSHOP_ERROR("Failed to compile {0} shader!\n{1}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"),
					   message.data());

		glDeleteShader(id);
		return 0;
	}
	return id;
}
} // namespace workshop