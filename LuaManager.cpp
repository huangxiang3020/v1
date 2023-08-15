#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <iostream>
#include <fstream>
#include "LuaManager.h"

using namespace luabridge;

static lua_State* luaState;

static void print(const char* log)
{
	std::cout << log << std::endl;
}

static void printError(const char* errorMsg)
{
	std::cout << errorMsg << std::endl;
}

static int panic(lua_State* L)
{
	const auto errorMsg = lua_tostring(L, -1);
	printError(errorMsg);
	return 0;
}

static int searcher(lua_State* L)
{
	const char* filename = luaL_checkstring(L, 1);
	std::ifstream luaFile;
	const auto path = std::string("res/lua/") + filename + ".lua";
	luaFile.open(path, std::ios::binary);
	if (!luaFile.is_open())
	{
		const std::string errorMsg = path + " not find";
		printError(errorMsg.c_str());
		return 1;
	}

	luaFile.seekg(0, std::ios::end);
	const auto len = luaFile.tellg();
	const auto f = new char[len];
	luaFile.seekg(0, std::ios::beg);
	luaFile.read(f, len);
	luaFile.close();
	const auto stat = luaL_loadbuffer(L, f, len, filename);
	delete[] f;

	if (stat != LUA_OK)
	{
		const auto errorMsg = lua_tostring(luaState, -1);
		printError(errorMsg);
		lua_pop(luaState, 1);
		return 1;
	}
	return 1;
}

static void addSearcher()
{
	lua_getglobal(luaState, "package");
	lua_getfield(luaState, -1, "searchers");
	lua_pushcclosure(luaState, searcher, 0);
	lua_rawseti(luaState, -2, 5);
	lua_pop(luaState, 2);
}

LuaManager& LuaManager::instance()
{
	static LuaManager instance;
	return instance;
}

void LuaManager::doString(const std::string& s) const
{
	const int ret = luaL_dostring(luaState, s.c_str());
	if (ret != LUA_OK)
	{
		const auto errorMsg = lua_tostring(luaState, -1);
		printError(errorMsg);
		lua_pop(luaState, 1);
	}
}

LuaManager::LuaManager()
{
	luaState = luaL_newstate();
	luaL_openlibs(luaState);
	lua_atpanic(luaState, panic);
	addSearcher();

	getGlobalNamespace(luaState)
		.addFunction("print", print);
}

LuaManager::~LuaManager()
{
	lua_close(luaState);
}
