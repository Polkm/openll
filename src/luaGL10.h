#ifndef __MODULES_LUAGL10_H__
#define __MODULES_LUAGL10_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace gl {
	int registerLua10(lua_State* L);
}
}
#endif