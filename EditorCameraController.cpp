#include "InputManager.h"
#include "TimeManger.h"
#include "EditorCameraController.h"


void EditorCameraController::update()
{
	const auto delta = TimeManger::instance().getDeltaTime();
	const auto scroll = InputManager::instance().getScroll();
	goForward(delta * scroll.y);

	if (InputManager::instance().getMouseDown(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (!mFreeMode)
		{
			mFreeMode = true;
			mLastMousePosition = InputManager::instance().getMousePosition();
		}
		else
		{
			const auto mousePosition = InputManager::instance().getMousePosition();
			const auto offset = mousePosition - mLastMousePosition;
			pitch(offset.x);
			yaw(-offset.y);
			mLastMousePosition = mousePosition;
		}

		if (InputManager::instance().getKeyDown(GLFW_KEY_A))
		{
			strafeLeft(delta);
		}
		else if (InputManager::instance().getKeyDown(GLFW_KEY_D))
		{
			strafeRight(delta);
		}
		else if (InputManager::instance().getKeyDown(GLFW_KEY_W))
		{
			goForward(delta);
		}
		else if (InputManager::instance().getKeyDown(GLFW_KEY_S))
		{
			goBack(delta);
		}
	}
	else
	{
		mFreeMode = false;
	}
}

void EditorCameraController::goForward(float value) const
{
	constexpr float factor = 10;
	value *= factor;
	auto localPosition = getNode()->getLocalPosition();
	const auto forward = glm::normalize(getNode()->getLocalToWorldMatrix()[2]);
	localPosition -= glm::vec3(forward.x, forward.y, forward.z) * value;
	getNode()->setLocalPosition(localPosition);
}

void EditorCameraController::goBack(float value) const
{
	goForward(-value);
}

void EditorCameraController::strafeLeft(float value) const
{
	constexpr float factor = 10;
	value *= factor;
	auto localPosition = getNode()->getLocalPosition();
	const auto right = glm::normalize(getNode()->getLocalToWorldMatrix()[0]);
	localPosition -= glm::vec3(right.x, right.y, right.z) * value;
	getNode()->setLocalPosition(localPosition);
}

void EditorCameraController::strafeRight(float value) const
{
	strafeLeft(-value);
}

void EditorCameraController::yaw(float value) const
{
	constexpr float factor = 0.1f;
	value *= factor;
	const auto rotation = getNode()->getLocalRotation();
	const auto q = glm::quat(glm::radians(glm::vec3(value, 0, 0)));
	getNode()->setLocalRotation(rotation * q);
}

void EditorCameraController::pitch(float value) const
{
	constexpr float factor = 0.1f;
	value *= factor;
	const auto rotation = getNode()->getLocalRotation();
	const auto q = glm::quat(glm::radians(glm::vec3(0, -value, 0)));
	getNode()->setLocalRotation(q * rotation);
}
