#pragma once
#include "Camera.h"

class Camera;
class CameraManager
{
public:
	static CameraManager& instance();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;

	void add(Camera* camera);
	void remove(Camera* camera);
	std::vector<Camera*>& getCameras();

private:
	CameraManager() = default;
	std::vector<Camera*> mCameras;
};
