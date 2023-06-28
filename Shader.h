#pragma once
#include <cstdint>
#include <string>
#include <glm/vec4.hpp>

class Shader
{
public:
	Shader(const std::string& vertexCode, const std::string& fragmentCode);
	void use() const;
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec4(const std::string& name, const glm::vec4& vec4) const;
	~Shader();

private:
	uint32_t mId = 0;
	void checkCompileErrors(unsigned int shader, const std::string& type) const;
};
