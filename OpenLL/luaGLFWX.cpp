#include "luaGLFWX.h"

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "olua.h"


static int getMouseDeltaPos(lua_State* L) {
	static double lX = 0.0, lY = 0.0;
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	lua_pushn(L, x - lX, y - lY);
	lX = x, lY = y;
	return 2;
}


int olf::glfwx::registerLua(lua_State* L) {
	const luaL_reg localLib[] = {
		{"getMouseDeltaPos", getMouseDeltaPos},
		{NULL, NULL}
	};
	luaL_register(L, "glfwx", localLib);

	return 1;
}