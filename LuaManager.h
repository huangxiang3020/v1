#pragma once
#include <string>

class LuaManager
{
public:
	static LuaManager& instance();
	LuaManager(const LuaManager&) = delete;
	LuaManager& operator=(const LuaManager&) = delete;
	void doString(const std::string& s) const;

private:
	LuaManager();
	~LuaManager();
};
