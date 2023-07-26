#pragma once
#include <cstdint>
#include <string>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class Shader
{
public:
	Shader() = default;
	void load(const std::string& vPath, const std::string& fPath);
	void use() const;
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec4(const std::string& name, const glm::vec4& vec4) const;
	void setVec3(const std::string& name, const glm::vec3& vec3) const;
	void setMat4(const std::string& name, const glm::mat4& mat4) const;
	~Shader();

private:
	uint32_t mId = 0;
	void checkCompileErrors(unsigned int shader, const std::string& type) const;
	void loadCode(const std::string& vertexCode, const std::string& fragmentCode);
};
