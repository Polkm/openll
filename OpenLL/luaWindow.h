#ifndef __WINDOW_WINDOW_H__
#define __WINDOW_WINDOW_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace window {
	int registerLua(lua_State* L);
}
}

#endif