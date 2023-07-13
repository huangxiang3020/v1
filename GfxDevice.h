#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include "DrawContext.h"

class GfxDevice
{
public:
	int32_t initalize();
	void clearColor(const glm::vec4& color) const;
	void processInput() const;
	void swap() const;
	bool shouldQuit() const;
	void terminate() const;

private:
	GLFWwindow* mWindow = nullptr;
};
