#ifndef __TIME_TIME_H__
#define __TIME_TIME_H__

// Forward declarations
struct lua_State;

namespace olf {
namespace time {
	int registerLua(lua_State* L);

	// Updates the time module, given time a chance to set delta variables.
	void update();
}
}

#endif