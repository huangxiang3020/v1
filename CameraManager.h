#pragma once
#include "Camera.h"

class Camera;
class CameraManager
{
public:
	static CameraManager& instance();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;

	void add(const std::shared_ptr<Camera>& camera);
	void remove(const std::shared_ptr<Camera>& camera);
	std::vector<std::shared_ptr<Camera>>& getCameras();

private:
	CameraManager() = default;
	std::vector<std::shared_ptr<Camera>> mCameras;
};
