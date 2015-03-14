#include "luaTime.h"

#include <GLFW/glfw3.h>
#include "olua.h"

using namespace olf::time;

static double deltaTime = 0.0; // The time in between frames
static double lastFrameTime = 0.0; // The time of last frame
static double fps = 0.0; // Frames per second

// Sets the time returned by getTime by seconds.
// Takes (newTime)
static int set(lua_State* L) {
	glfwSetTime(lua_tonumber(L, 1));
	return 0;
}

// Returns the time since the time was last set in seconds. (first set at initialization)
// Returns (time)
static int get(lua_State* L) {
	lua_pushnumber(L, glfwGetTime());
	return 1;
}

// Returns the time since last frame in seconds.
// Returns (deltaTime)
static int getDelta(lua_State* L) {
	lua_pushnumber(L, deltaTime);
	return 1;
}

// Returns the frames per second the aplication is running at
// Returns (fps)
static int getFPS(lua_State* L) {
	lua_pushnumber(L, fps);
	return 1;
}

// Sleeps the calling thread for the specified number of seconds
// Takes (sleepTime)
static int sleep(lua_State* L) {
	//glfwSleep(lua_tonumber(L, 1));
	return 0;
}

int olf::time::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{"set", set},
		{"get", get},
		{"getDelta", getDelta},
		{"getFPS", getFPS},
		{"sleep", sleep},
		{NULL, NULL}
	};
	luaL_openlib(L, "time", localLib, 0);

	return 1;
}

void olf::time::update() {
	auto curentTime = glfwGetTime();
	deltaTime = curentTime - lastFrameTime;
	lastFrameTime = curentTime;
	fps = 1.0 / deltaTime;
}
