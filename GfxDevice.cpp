#include "GfxDevice.h"

int32_t GfxDevice::initalize() 
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(640, 480, "v1", nullptr, nullptr);
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

	return 0;
}

void GfxDevice::clearColor(const glm::vec4& color) const
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GfxDevice::processInput() const
{
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(mWindow, true);
}

void GfxDevice::draw(const Camera& camera, const DrawContext& context) const
{
	context.draw(camera);
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

void GfxDevice::terminate() const
{
	glfwTerminate();
}
