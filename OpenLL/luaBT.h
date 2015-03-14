#ifndef __MODULES_LUABT_H__
#define __MODULES_LUABT_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace bt {
	int registerLua(lua_State* L);
}
}

#endif