#include <iostream>
#include <string>

#include "luaGLFW.h"
#include "luaGLFWX.h"
#include "luaMath.h"
#include "luaGL.h"
#include "luaGLX.h"
#include "luaGLM.h"
#include "luaAL.h"
#include "luaALC.h"
#include "luaALX.h"
#include "luaImport.h"
#include "luaMatrix.h"
#include "luaBT.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "olua.h"

#include <btBulletDynamicsCommon.h>

void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

int main() {
	// Set error call back.
	glfwSetErrorCallback(error_callback);

	auto L = luaL_newstate();

	// load the libs
	luaL_openlibs(L);
	olf::math::registerLua(L);
	olf::glfw::registerLua(L);
	olf::glfwx::registerLua(L);
	olf::gl::registerLua(L);
	olf::glx::registerLua(L);
	olf::glmw::registerLua(L);
	olf::al::registerLua(L);
	olf::alc::registerLua(L);
	olf::alx::registerLua(L);
	olf::import::registerLua(L);
	olf::matrix::registerLua(L);
	olf::bt::registerLua(L);

	// Start running lua code
	if (luaL_dofile(L, "Content/lua/main.lua")) {
		// We have errors!
        printf("%s\n", lua_tostring(L, -1));
    }

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	lua_close(L);
	return 0;
}