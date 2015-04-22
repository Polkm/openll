#include "luaBTWorld.h"

#include <btBulletDynamicsCommon.h>
#include "olua.h"

using namespace olf::bt;

LuaBTWorld::LuaBTWorld() {
	world = nullptr;
	broadphase = nullptr;
	collisionConfiguration = nullptr;
	dispatcher = nullptr;
	solver = nullptr;
}

LuaBTWorld::~LuaBTWorld() {
	if (broadphase != nullptr) delete broadphase;
	if (collisionConfiguration != nullptr) delete collisionConfiguration;
	if (dispatcher != nullptr) delete dispatcher;
	if (solver != nullptr) delete solver;
	if (world != nullptr) delete world;
}

void LuaBTWorld::Initialize() {
	broadphase = new btDbvtBroadphase();

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
}

btCollisionWorld* LuaBTWorld::getWorld() const {
	return world;
}




static int world(lua_State* L) {
	auto udata = lua_classconstructor<LuaBTWorld>(L, "lua_btworld");
	*udata = new LuaBTWorld();
	(*udata)->Initialize();
	return 1;
}

static int setGravity(lua_State* L) {
	auto world = static_cast<btDiscreteDynamicsWorld*>(lua_classcheck<LuaBTWorld>(L, 1, "lua_btworld")->getWorld());
	world->setGravity(lua_tobtvector3(L, 2));
	return 0;
}

static int gcWorld(lua_State* L) {
	auto checkClass = lua_classcheck<LuaBTWorld>(L, 1, "lua_btworld");
	delete checkClass;
	return 0;
}

int olf::bt::registerLuaWorld(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{"world", world},
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