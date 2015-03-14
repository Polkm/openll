#ifndef __MODULES_LUAMATRIX_H__
#define __MODULES_LUAMATRIX_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace matrix {
	int registerLua(lua_State* L);
}
}
#endif