#ifndef __MODULES_LUAGL30_H__
#define __MODULES_LUAGL30_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace gl {
	int registerLua30(lua_State* L);
}
}
#endif