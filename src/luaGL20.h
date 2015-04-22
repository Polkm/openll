#ifndef __MODULES_LUAGL20_H__
#define __MODULES_LUAGL20_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace gl {
	int registerLua20(lua_State* L);
}
}
#endif