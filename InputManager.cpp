#include "InputManager.h"

InputManager& InputManager::instance()
{
	static InputManager instance;
	return instance;
}

glm::vec2 InputManager::getMousePosition() const
{
	double xpos, ypos;
	glfwGetCursorPos(mWindow, &xpos, &ypos);
	return {xpos, ypos};
}

bool InputManager::getKeyDown(int32_t keyCode) const
{
	return glfwGetKey(mWindow, keyCode) == GLFW_PRESS;
}

void InputManager::setWindow(GLFWwindow* window)
{
	mWindow = window;
}