#include "luaBT.h"
#include "luaBTWorld.h"

#include "olua.h"

using namespace olf::bt;

int olf::bt::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{NULL, NULL}
	};
	luaL_openlib(L, "bt", localLib, 0);

	registerLuaWorld(L);

	return 0;
}