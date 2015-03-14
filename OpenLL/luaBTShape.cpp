#include "luaBTShape.h"

#include <btBulletDynamicsCommon.h>
#include "olua.h"

using namespace olf::bt;


static int staticPlaneShape(lua_State* L) {
	auto udata = lua_classconstructor<btStaticPlaneShape>(L, "lua_btshapeplane");
	auto normal = lua_tobtvector3(L, 1);
	auto constant = lua_tocast<btScalar>(L, 2);
	*udata = new btStaticPlaneShape(normal, constant);
	return 1;
}



static int gcWorld(lua_State* L) {
	auto checkClass = lua_classcheck<LuaBTWorld>(L, 1, "lua_btworld");
	delete checkClass;
	return 0;
}

int olf::bt::registerLuaWorld(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{"staticPlaneShape", staticPlaneShape},
		{NULL, NULL}
	};
	luaL_openlib(L, "bt", localLib, 0);

	luaL_Reg sFooRegs[] = {
		{"setGravity", setGravity},
		{"__gc", gcWorld},
		{NULL, NULL}
	};
	lua_classregester(L, sFooRegs, "lua_btworld");

	return 1;
}