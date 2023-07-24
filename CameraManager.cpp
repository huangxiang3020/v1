#include "CameraManager.h"


CameraManager& CameraManager::instance()
{
	static CameraManager instance;
	return instance;
}


void CameraManager::add(const std::shared_ptr<Camera>& camera)
{
	mCameras.push_back(camera);
}

void CameraManager::remove(const std::shared_ptr<Camera>& camera)
{
	for (auto it = mCameras.begin(); it != mCameras.end(); ++it)
	{
		if (*it == camera)
		{
			it = mCameras.erase(it);
			if (it == mCameras.end()) break;
		}
	}
}

std::vector<std::shared_ptr<Camera>>& CameraManager::getCameras()
{
	return mCameras;
}
