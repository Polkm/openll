#ifndef __LUA_ALC_H__
#define __LUA_ALC_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace alc {
	int registerLua(lua_State* L);
}
}

#endif