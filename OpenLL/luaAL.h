#ifndef __LUA_AL_H__
#define __LUA_AL_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace al {
	int registerLua(lua_State* L);
}
}

#endif