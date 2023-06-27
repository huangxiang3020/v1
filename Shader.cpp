#include "Shader.h"
#include <glad/gl.h>
#include <iostream>

Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode)
{
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	const uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");

	mId = glCreateProgram();
	glAttachShader(mId, vertexShader);
	glAttachShader(mId, fragmentShader);
	glLinkProgram(mId);
	checkCompileErrors(mId, "PROGRAM");
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const
{
	glUseProgram(mId);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(mId, name.c_str()), static_cast<int32_t>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(mId, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(mId, name.c_str()), value);
}

void Shader::checkCompileErrors(uint32_t shader, const std::string& type) const
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog <<
				"\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog <<
				"\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
