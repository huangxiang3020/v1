#include "InputManager.h"

InputManager& InputManager::instance()
{
	static InputManager instance;
	return instance;
}

bool InputManager::getMouseDown(int32_t button) const
{
	const int32_t state = glfwGetMouseButton(mWindow, button);
	return state == GLFW_PRESS;
}

glm::vec2 InputManager::getMousePosition() const
{
	double xpos, ypos;
	glfwGetCursorPos(mWindow, &xpos, &ypos);
	return {xpos, ypos};
}

glm::vec2 InputManager::getScroll() const
{
	return mScrollOffset;
}

bool InputManager::getKeyDown(int32_t keyCode) const
{
	return glfwGetKey(mWindow, keyCode) == GLFW_PRESS;
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	InputManager::instance().mScrollOffset += glm::vec2(xOffset, yOffset);
}

void InputManager::setWindow(GLFWwindow* window)
{
	mWindow = window;
	glfwSetScrollCallback(mWindow, scrollCallback);
}

void InputManager::processInput()
{
	mScrollOffset = {};
	glfwPollEvents();
	if (getKeyDown(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(mWindow, true);
	}
}
