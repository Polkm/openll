#ifndef __LUA_CLASS_H__
#define __LUA_CLASS_H__

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

template<typename T>
T** lua_classconstructor(lua_State* L, const char* metaName) {
	auto udata = (T**)lua_newuserdata(L, sizeof(T*));

	luaL_getmetatable(L, metaName);
	lua_setmetatable(L, -2);
	return udata;
}

template<typename T>
T* lua_classcheck(lua_State* L, int index, const char* metaName) {
    return *(T**)luaL_checkudata(L, index, metaName);
}

void lua_classregester(lua_State* L, const luaL_Reg* funcs, const char* metaName);

#endif