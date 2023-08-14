#include <lua.hpp>
#include "LuaManager.h"

static lua_State* L;

LuaManager& LuaManager::instance()
{
	static LuaManager instance;
	return instance;
}

void LuaManager::doString(const std::string& s) const
{
	luaL_dostring(L, s.c_str());
}

LuaManager::LuaManager()
{
	L = luaL_newstate();
	luaL_openlibs(L);
}

LuaManager::~LuaManager()
{
	lua_close(L);
}
