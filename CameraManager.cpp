#include "CameraManager.h"


CameraManager& CameraManager::instance()
{
	static CameraManager instance;
	return instance;
}


void CameraManager::add(Camera* camera)
{
	mCameras.push_back(camera);
}

void CameraManager::remove(Camera* camera)
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

std::vector<Camera*>& CameraManager::getCameras()
{
	return mCameras;
}
