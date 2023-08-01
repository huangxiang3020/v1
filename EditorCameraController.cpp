#include "InputManager.h"
#include "TimeManger.h"
#include "EditorCameraController.h"


void EditorCameraController::update()
{
	const auto delta = TimeManger::instance().getDeltaTime();
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

	// const auto scroll = InputManager::instance().getScroll();
	// if (scroll.y > 0)
	// {
	// 	auto localPosition = getNode()->getLocalPosition();
	// 	localPosition.y += delta * scroll.y;
	// 	getNode()->setLocalPosition(localPosition);
	// }
	// else if (scroll.y < 0)
	// {
	// 	auto localPosition = getNode()->getLocalPosition();
	// 	localPosition.y += delta * scroll.y;
	// 	getNode()->setLocalPosition(localPosition);
	// }

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
			auto localPosition = getNode()->getLocalPosition();
			localPosition.y += delta * offset.y;
			localPosition.x += delta * offset.x;
			getNode()->setLocalPosition(localPosition);
		}
	}
	else
	{
		mFreeMode = false;
	}
}
