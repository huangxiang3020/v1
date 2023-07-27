#include "Spin.h"

void Spin::update()
{
	const auto rotation = getNode()->getLocalRotation();
	const auto q = glm::quat(glm::radians(glm::vec3(0, 1, 0)));
	getNode()->setLocalRotation(rotation * q);
}
