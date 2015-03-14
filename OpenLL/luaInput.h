#ifndef __INPUT_INPUT_H__
#define __INPUT_INPUT_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace input {
	void update();

	int registerLua(lua_State* L);
}
}

#endif