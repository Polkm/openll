#ifndef __LUA_BTWORLD_H__
#define __LUA_BTWORLD_H__

// Forward declarations
struct lua_State;

class btCollisionWorld;
class btBroadphaseInterface;
class btCollisionConfiguration;
class btDispatcher;
class btConstraintSolver;

class LuaBTWorld {
public:
	LuaBTWorld();

	~LuaBTWorld();

	void Initialize();

	btCollisionWorld* getWorld() const;

protected:
	btCollisionWorld* world;

	btBroadphaseInterface* broadphase;
	btCollisionConfiguration* collisionConfiguration;
	btDispatcher* dispatcher;
	btConstraintSolver* solver;
};

namespace olf {
namespace bt {
	int registerLuaWorld(lua_State* L);
}
}

#endif