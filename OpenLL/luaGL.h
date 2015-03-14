#ifndef __MODULES_LUAGL_H__
#define __MODULES_LUAGL_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace gl {
	int registerLua(lua_State* L);
}
}

#endif