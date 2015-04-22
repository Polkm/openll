#include "lua_class.h"

void lua_classregester(lua_State* L, const luaL_Reg* funcs, const char* metaName) {
	luaL_newmetatable(L, metaName);
	luaL_register(L, NULL, funcs);
	lua_pushvalue(L, -1);
	lua_setfield(L, -1, "__index");
	//lua_setglobal(L, globalName);
}


