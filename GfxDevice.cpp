#include "GfxDevice.h"
#include "InputManager.h"

int32_t GfxDevice::initalize()
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	mWindow = glfwCreateWindow(1280, 720, "v1", nullptr, nullptr);
	if (!mWindow)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(mWindow);

	const int32_t version = gladLoadGL(glfwGetProcAddress);
	if (version == 0)
	{
		return -1;
	}

	InputManager::instance().setWindow(mWindow);

	return 0;
}

void GfxDevice::clearColor(const glm::vec4& color) const
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GfxDevice::processInput() const
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(mWindow, true);
}

void GfxDevice::swap() const
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

bool GfxDevice::shouldQuit() const
{
	return glfwWindowShouldClose(mWindow);
}

void GfxDevice::quit() const
{
	glfwSetWindowShouldClose(mWindow, true);
}

void GfxDevice::terminate() const
{
	glfwTerminate();
}
