#ifndef __EXTENSIONS_LUAMATH_H__
#define __EXTENSIONS_LUAMATH_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace math {
	int registerLua(lua_State* L);
}
}

#endif