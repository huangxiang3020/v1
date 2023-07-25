#pragma once
#include <memory>
#include <string>

class ResourceManager
{
public:
	template <typename T>
	std::shared_ptr<T> load(std::string path);
	template <typename T>
	std::shared_ptr<T> load(std::string path1, std::string path2);

	static ResourceManager& instance();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

private:
	ResourceManager() = default;
};

template <typename T>
std::shared_ptr<T> ResourceManager::load(std::string path)
{
	std::shared_ptr<T> asset = std::make_shared<T>();
	asset->load(path);
	return asset;
}

template <typename T>
std::shared_ptr<T> ResourceManager::load(std::string path1, std::string path2)
{
	std::shared_ptr<T> asset = std::make_shared<T>();
	asset->load(path1, path2);
	return asset;
}
