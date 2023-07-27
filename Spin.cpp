#include "Spin.h"

Spin::Spin(const std::shared_ptr<Node>& node) : Component(node)
{
}

void Spin::update()
{
	static float angle = 0;
	angle++;
	getNode()->setLocalEulerAngles(glm::vec3(0, angle, 0));
}
