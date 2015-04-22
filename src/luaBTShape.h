#ifndef __LUA_BTSHAPE_H__
#define __LUA_BTSHAPE_H__

// Forward declarations
struct lua_State;


namespace olf {
namespace bt {
	int registerLuaShape(lua_State* L);
}
}

#endif