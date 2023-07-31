#include "Spin.h"
#include "TimeManger.h"
#include "InputManager.h"

void Spin::update()
{
	const auto delta = TimeManger::instance().getDeltaTime();
	const auto rotation = getNode()->getLocalRotation();
	const auto q = glm::quat(glm::radians(glm::vec3(0, 90 * delta, 0)));
	getNode()->setLocalRotation(q * rotation);

	if (InputManager::instance().getKeyDown(GLFW_KEY_LEFT))
	{
		auto localPosition = getNode()->getLocalPosition();
		localPosition.x -= delta;
		getNode()->setLocalPosition(localPosition);
	}
	else if (InputManager::instance().getKeyDown(GLFW_KEY_RIGHT))
	{
		auto localPosition = getNode()->getLocalPosition();
		localPosition.x += delta;
		getNode()->setLocalPosition(localPosition);
	}
	else if (InputManager::instance().getKeyDown(GLFW_KEY_UP))
	{
		auto localPosition = getNode()->getLocalPosition();
		localPosition.y += delta;
		getNode()->setLocalPosition(localPosition);
	}
	else if (InputManager::instance().getKeyDown(GLFW_KEY_DOWN))
	{
		auto localPosition = getNode()->getLocalPosition();
		localPosition.y -= delta;
		getNode()->setLocalPosition(localPosition);
	}
}
