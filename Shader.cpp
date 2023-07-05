#include "Shader.h"
#include <glad/gl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vPath, const std::string& fPath)
{
	std::ifstream vfile(vPath);
	std::ifstream ffile(fPath);
	std::stringstream vShaderStream, fShaderStream;
	if (vfile.is_open() && ffile.is_open()) {  
		vShaderStream << vfile.rdbuf();
		fShaderStream << ffile.rdbuf();
		// close file handlers
		vfile.close();
		ffile.close();
	}
	else {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ:" << vPath << " " << fPath << std::endl;
	}

	load(vShaderStream.str(), fShaderStream.str());
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

void Shader::setVec4(const std::string& name, const glm::vec4& vec4) const
{
	glUniform4f(glGetUniformLocation(mId, name.c_str()), vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat4) const
{
	glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}

Shader::~Shader()
{
	glDeleteProgram(mId);
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

void Shader::load(const std::string& vertexCode, const std::string& fragmentCode)
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
