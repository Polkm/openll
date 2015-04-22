//____glfwOpenWindowHint(GLFW_REFRESH_RATE, -1); // Caution! do not un-comment this shit!
#include "luaWindow.h"

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "olua.h"

#include <map>
#include <iostream>

using namespace olf::window;

// This function resets all window hints to their default values.
static int create(lua_State* L) {
	auto width = lua_tosafecast<unsigned int>(L, 1, 800);
	auto height = lua_tosafecast<unsigned int>(L, 2, 700);
	auto title = lua_tocast<const char*>(L, 3);
	auto monitor = lua_touserdatacast<GLFWmonitor>(L, 4);
	auto share = lua_touserdatacast<GLFWwindow>(L, 4);
	auto window = glfwCreateWindow(width, height, title, monitor, share);

	lua_pushlightuserdata(L, window);
	return 1;
}

// This function destroys the specified window and its context. On calling this
// function, no further callbacks will be called for that window.
static int destroyWindow(lua_State* L) {
	glfwDestroyWindow(lua_touserdatacast<GLFWwindow>(L, 1));
	return 0;
}

// This function returns the value of the close flag of the specified window.
static int getShouldClose(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	lua_push(L, glfwWindowShouldClose(window));
	return 1;
}

// This function sets the value of the close flag of the specified window. This
// can be used to override the user's attempt to close the window, or to signal
// that it should be closed.
static int setShouldClose(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	auto value = lua_tosafecast<int>(L, 2, 0);
	glfwSetWindowShouldClose(window, value);
	return 0;
}

// This function sets the window title, encoded as UTF-8, of the specified window.
static int setTitle(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	auto title = lua_tosafecast<const char*>(L, 2, 0);
	glfwSetWindowTitle(window, title);
	return 0;
}

// This function retrieves the position, in screen coordinates, of the upper-left
// corner of the client area of the specified window.
static int getPos(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	int x, y;
	glfwGetWindowPos(window, &x, &y);
	lua_push(L, x);
	lua_push(L, y);
	return 2;
}

// This function sets the window title, encoded as UTF-8, of the specified window.
static int setPos(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	auto x = lua_tosafecast<int>(L, 2, 0);
	auto y = lua_tosafecast<int>(L, 3, 0);
	glfwSetWindowPos(window, x, y);
	return 0;
}


// This function retrieves the size, in screen coordinates, of the client area of
// the specified window. If you wish to retrieve the size of the framebuffer in pixels,
// see glfwGetFramebufferSize.
static int getSize(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	lua_push(L, width);
	lua_push(L, height);
	return 2;
}

// This function sets the size, in screen coordinates, of the client area of the specified window.
static int setSize(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	auto width = lua_tosafecast<int>(L, 2, 1024);
	auto height = lua_tosafecast<int>(L, 3, 768);
	glfwSetWindowSize(window, width, height);
	return 0;
}

// This function retrieves the size, in pixels, of the framebuffer of the specified window. If you
// wish to retrieve the size of the window in screen coordinates, see glfwGetWindowSize.
static int getFramebufferSize(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	lua_push(L, width);
	lua_push(L, height);
	return 2;
}

// This function iconifies/minimizes the specified window, if it was previously restored. If it is
// a full screen window, the original monitor resolution is restored until the window is restored.
// If the window is already iconified, this function does nothing.
static int minimizes(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	glfwIconifyWindow(window);
	return 0;
}

// This function restores the specified window, if it was previously iconified/minimized. If it is
// a full screen window, the resolution chosen for the window is restored on the selected monitor.
// If the window is already restored, this function does nothing.
static int restore(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	glfwRestoreWindow(window);
	return 0;
}

// This function makes the specified window visible, if it was previously hidden. If the window is
// already visible or is in full screen mode, this function does nothing.
static int show(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	glfwShowWindow(window);
	return 0;
}

// This function hides the specified window, if it was previously visible. If the window is already
// hidden or is in full screen mode, this function does nothing.
static int hide(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	glfwHideWindow(window);
	return 0;
}

// This function returns the handle of the monitor that the specified window is in full screen on.
static int getMonitor(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	auto monitor = glfwGetWindowMonitor(window);
	lua_pushlightuserdata(L, monitor);
	return 1;
}

// This function returns an attribute of the specified window. There are many attributes, some
// related to the window and others to its context.
static int getAttribute(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	auto attribute = lua_tosafecast<int>(L, 2, 1024);
	auto value = glfwGetWindowAttrib(window, attribute);
	lua_push(L, value);
	return 1;
}

// This function sets the user-defined pointer of the specified window. The current value is
// retained until the window is destroyed. The initial value is NULL.
static int setUserPointer(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	auto pointer = lua_tocast<void*>(L, 2);
	glfwSetWindowUserPointer(window, pointer);
	return 0;
}

// This function returns the handle of the monitor that the specified window is in full screen on.
static int getUserPointer(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	auto pointer = glfwGetWindowUserPointer(window);
	lua_pushlightuserdata(L, pointer);
	return 1;
}

// This function sets the user-defined pointer of the specified window. The current value is
// retained until the window is destroyed. The initial value is NULL.
static int setPosCallback(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	//auto cbfun = lua_tofunction<GLFWwindowposfun>(L, 2);
	glfwSetWindowPosCallback(window, [](GLFWwindow*, int, int) { /* do something here*/ });
	return 0;
}

// This function processes only those events that have already been received and then returns
// immediately. Processing events will cause the window and input callbacks associated with
// those events to be called.
static int pollEvents(lua_State* L) {
	glfwPollEvents();
	return 0;
}

// This function puts the calling thread to sleep until at least one event has been received.
// Once one or more events have been received, it behaves as if glfwPollEvents was called, i.e.
// the events are processed and the function then returns immediately. Processing events will
// cause the window and input callbacks associated with those events to be called.
static int waitEvents(lua_State* L) {
	glfwWaitEvents();
	return 0;
}


// This function makes the context of the specified window current on the calling thread.
// A context can only be made current on a single thread at a time and each thread can have
// only a single current context at a time.
static int setCurrentContext(lua_State* L) {
	auto window = lua_touserdatacast<GLFWwindow>(L, 1);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		//return 0;
	}

	return 0;
}

// This function returns the window whose context is current on the calling thread.
static int getCurrentContext(lua_State* L) {
	lua_pushlightuserdata(L, glfwGetCurrentContext());
	return 1;
}

int olf::window::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{"defaultHints", LUA_FULL_WRAP(glfwDefaultWindowHints)},
		{"hint", LUA_FULL_WRAP(glfwWindowHint)},
		{"create", create},
		{"destroyWindow", destroyWindow},
		{"getShouldClose", getShouldClose},
		{"setShouldClose", setShouldClose},
		{"setTitle", setTitle},
		{"getPos", getPos},
		{"setPos", setPos},
		{"getSize", getSize},
		{"setSize", setSize},
		{"getFramebufferSize", getFramebufferSize},
		{"minimizes", minimizes},
		{"restore", restore},
		{"show", show},
		{"hide", hide},
		{"getMonitor", getMonitor},
		{"getAttribute", getAttribute},
		{"setUserPointer", setUserPointer},
		{"setPosCallback", setPosCallback},
		{"pollEvents", pollEvents},
		{"waitEvents", waitEvents},

		{"setCurrentContext", setCurrentContext},
		{"getCurrentContext", getCurrentContext},
		{"waitEvents", waitEvents},
		{"waitEvents", waitEvents},
		{"waitEvents", waitEvents},
		{NULL, NULL}
	};
	luaL_openlib(L, "window", localLib, 0);

	// Window params
	lua_pushenumuration(L, "WINDOW_ICONIFIED", GLFW_ICONIFIED);
	lua_pushenumuration(L, "WINDOW_RED_BITS", GLFW_RED_BITS);
	lua_pushenumuration(L, "WINDOW_GREEN_BITS", GLFW_GREEN_BITS);
	lua_pushenumuration(L, "WINDOW_BLUE_BITS", GLFW_BLUE_BITS);
	lua_pushenumuration(L, "WINDOW_ALPHA_BITS", GLFW_ALPHA_BITS);
	lua_pushenumuration(L, "WINDOW_DEPTH_BITS", GLFW_DEPTH_BITS);
	lua_pushenumuration(L, "WINDOW_STENCIL_BITS", GLFW_STENCIL_BITS);
	// Setable
	lua_pushenumuration(L, "WINDOW_REFRESH_RATE", GLFW_REFRESH_RATE);
	lua_pushenumuration(L, "WINDOW_ACCUM_RED_BITS", GLFW_ACCUM_RED_BITS);
	lua_pushenumuration(L, "WINDOW_ACCUM_GREEN_BITS", GLFW_ACCUM_GREEN_BITS);
	lua_pushenumuration(L, "WINDOW_ACCUM_BLUE_BITS", GLFW_ACCUM_BLUE_BITS);
	lua_pushenumuration(L, "WINDOW_ACCUM_ALPHA_BITS", GLFW_ACCUM_ALPHA_BITS);
	lua_pushenumuration(L, "WINDOW_AUX_BUFFERS", GLFW_AUX_BUFFERS);
	lua_pushenumuration(L, "WINDOW_STEREO", GLFW_STEREO);
	lua_pushenumuration(L, "WINDOW_OPENGL_FORWARD_COMPAT", GLFW_OPENGL_FORWARD_COMPAT);
	lua_pushenumuration(L, "WINDOW_OPENGL_DEBUG_CONTEXT", GLFW_OPENGL_DEBUG_CONTEXT);
	lua_pushenumuration(L, "WINDOW_OPENGL_PROFILE", GLFW_OPENGL_PROFILE);
	// OpenGL profiles
	lua_pushenumuration(L, "WINDOW_OPENGL_CORE", GLFW_OPENGL_CORE_PROFILE);
	lua_pushenumuration(L, "WINDOW_OPENGL_COMPAT", GLFW_OPENGL_COMPAT_PROFILE);

	return 1;
}
