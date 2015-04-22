#ifndef __MODULES_LUAIMPORT_H__
#define __MODULES_LUAIMPORT_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace import {
	int registerLua(lua_State* L);
}
}
#endif