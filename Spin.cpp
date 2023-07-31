#include "Spin.h"
#include "TimeManger.h"

void Spin::update()
{
	const auto delta = TimeManger::instance().getDeltaTime();
	const auto rotation = getNode()->getLocalRotation();
	const auto q = glm::quat(glm::radians(glm::vec3(0, 90 * delta, 0)));
	getNode()->setLocalRotation(q * rotation);
}
