#include "Shader.h"

ShaderProgramSource Shader::ParseShaderFromFile(const std::string& filepath)
{
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};
	ShaderType type = ShaderType::NONE;

	std::ifstream fs(filepath);
	LOG_ASSERT(fs, "Cant open file {}", filepath);

	std::stringstream ss[2];

	std::string line;
	while (std::getline(fs, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			} else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			} else {
				LOG_WARN("Found '#shader', but no valid shader type.");
			}
		} else {
			if (type == ShaderType::NONE)
				continue;
			ss[(int)type] << line << '\n';
		}
	}

	return {ss[0].str(), ss[1].str()};
}

uint32_t Shader::CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
{
	uint32_t program = glCreateProgram();
	auto vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
	auto fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glValidateProgram(program);
	GLint result;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
	if (result != GL_TRUE) {
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetProgramInfoLog(program, length, &length, &error[0]);

		LOG_ERROR("Failed to compile shader with error: {}", &error[0]);
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
	uint32_t shaderID = glCreateShader(type);
	auto src = source.c_str();
	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	LOG_ASSERT(
		result, "Shader compile error: {}", [shaderID]() -> auto{
			int length;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
			std::string message(length, ' ');
			glGetShaderInfoLog(shaderID, length, &length, &message[0]);
			return message;
		}());

	return shaderID;
}
