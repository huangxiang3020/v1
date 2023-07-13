#include <glm/glm.hpp>
#include "GfxDevice.h"
#include "Camera.h"
#include "Cube.h"

int main(int argc, char* argv[])
{
	auto device = GfxDevice();
	const auto ret = device.initalize();
	if (ret != 0)
	{
		return ret;
	}

	// Camera
	auto camera = Camera();
	camera.setLocalPosition(glm::vec3(0, 0, -10));
	camera.setLocalEulerAngles(glm::vec3(-30, 0, 0));
	camera.setAspect(640.f / 480);
	camera.setFar(1000);
	camera.setNear(1);
	camera.setFov(45);

	auto cube = Cube();

	while (!device.shouldQuit())
	{
		device.processInput();
		device.clearColor(glm::vec4(1, 1, 1, 1));
		cube.draw(camera);
		device.swap();
	}

	device.terminate();

	return 0;
}
