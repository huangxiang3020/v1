#pragma once
#include <glm/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class InputManager
{
	friend void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
public:
	static InputManager& instance();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	bool getMouseDown(int32_t button)const;
	glm::vec2 getMousePosition() const;
	glm::vec2 getScroll()const;
	bool getKeyDown(int32_t keyCode) const;
	void setWindow(GLFWwindow* window);
	void processInput();

private:
	InputManager() = default;
	GLFWwindow* mWindow = nullptr;
	glm::vec2 mScrollOffset = {};
};
