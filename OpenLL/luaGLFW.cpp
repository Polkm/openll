//____glfwOpenWindowHint(GLFW_REFRESH_RATE, -1); // Caution! do not un-comment this shit!
#include "luaGLFW.h"

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "olua.h"

#include <map>
#include <iostream>
#include <mutex>
#include <string>

using namespace olf::glfw;

static auto glfw_callback_state = (lua_State*) 0;

// This function retrieves the position, in screen coordinates, of the upper-left
// corner of the client area of the specified window.
static int getWindowPos(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	int x, y;
	glfwGetWindowPos(window, &x, &y);
	return lua_pushn(L, x, y);
}

// This function retrieves the size, in screen coordinates, of the client area of
// the specified window. If you wish to retrieve the size of the framebuffer in pixels,
// see glfwgetFramebufferSize.
static int getWindowSize(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return lua_pushn(L, width, height);
}

// This function retrieves the size, in pixels, of the framebuffer of the specified window. If you
// wish to retrieve the size of the window in screen coordinates, see glfwGetWindowSize.
static int getFramebufferSize(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	return lua_pushn(L, width, height);
}

// Sets the position callback for the specified window.
static int setWindowPosCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWwindowposfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, int xpos, int ypos) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, xpos, ypos);
		};
	}
	glfwSetWindowPosCallback(window, fun);
	return 0;
}

// Sets the size callback for the specified window.
static int setWindowSizeCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWwindowsizefun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, int width, int height) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, width, height);
		};
	}
	glfwSetWindowSizeCallback(window, fun);
	return 0;
}

// Sets the close callback for the specified window.
static int setWindowCloseCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWwindowclosefun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window);
		};
	}
	glfwSetWindowCloseCallback(window, fun);
	return 0;
}

// Sets the refresh callback for the specified window.
static int setWindowRefreshCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWwindowrefreshfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window);
		};
	}
	glfwSetWindowRefreshCallback(window, fun);
	return 0;
}

// Sets the focus callback for the specified window.
static int setWindowFocusCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWwindowfocusfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, int focused) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, focused);
		};
	}
	glfwSetWindowFocusCallback(window, fun);
	return 0;
}

// Sets the iconify callback for the specified window.
static int setWindowIconifyCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWwindowiconifyfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, int iconified) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, iconified);
		};
	}
	glfwSetWindowIconifyCallback(window, fun);
	return 0;
}

// Sets the framebuffer resize callback for the specified window.
static int setFramebufferSizeCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWframebuffersizefun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, int width, int height) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, width, height);
		};
	}
	glfwSetFramebufferSizeCallback(window, fun);
	return 0;
}


// This function makes the context of the specified window current on the calling thread.
// A context can only be made current on a single thread at a time and each thread can have
// only a single current context at a time.
static int makeContextCurrent(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		return 0;
	}

	return 0;
}

// Retrieves the version of the GLFW library.
static int getVersion(lua_State* L) {
	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	lua_push(L, major);
	lua_push(L, minor);
	lua_push(L, rev);
	return 3;
}

// Retrieves the last reported cursor position, relative to the client area of the window.
static int getCursorPos(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	lua_push(L, x);
	lua_push(L, y);
	return 2;
}

// Returns the values of all axes of the specified joystick.
static int getJoystickAxes(lua_State* L) {
	auto joy = lua_tocast<int>(L, 1);
	int count;
	auto axes = glfwGetJoystickAxes(joy, &count);
	if (count > 0) {
		lua_pusharray(L, axes, count, false);
		return 1;
	}
	return 0;
}

// Returns the state of all buttons of the specified joystick.
static int getJoystickButtons(lua_State* L) {
	auto joy = lua_tocast<int>(L, 1);
	int count;
	auto buttons = glfwGetJoystickButtons(joy, &count);
	if (count > 0) {
		lua_pusharray(L, buttons, count, false);
		return 1;
	}
	return 0;
}

// Returns the currently connected monitors.
static int getMonitors(lua_State* L) {
	int count;
	auto monitors = glfwGetMonitors(&count);
	if (count > 0) {
		lua_pusharray(L, monitors, count, false);
		return 1;
	}
	return 0;
}

// Returns the position of the monitor's viewport on the virtual screen.
static int getMonitorPos(lua_State* L) {
	auto monitor = lua_tocast<GLFWmonitor*>(L, 1);
	int xpos, ypos;
	glfwGetMonitorPos(monitor, &xpos, &ypos);
	lua_push(L, xpos);
	lua_push(L, ypos);
	return 2;
}

// Returns the physical size of the monitor.
static int getMonitorPhysicalSize(lua_State* L) {
	auto monitor = lua_tocast<GLFWmonitor*>(L, 1);
	int width, height;
	glfwGetMonitorPhysicalSize(monitor, &width, &height);
	lua_push(L, width);
	lua_push(L, height);
	return 2;
}

// Returns the available video modes for the specified monitor.
//static int getVideoModes(lua_State* L) {
//	auto monitor = lua_touserdatacast<GLFWmonitor>(L, 1);
//	int count;
//	auto modes = glfwGetVideoModes(monitor, &count);
//	if (count > 0) {
//		lua_pusharray(L, modes, count, false);
//		return 1;
//	}
//	return 0;
//}

// Returns the physical size of the monitor.
static int windowShouldClose(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	lua_push(L, glfwWindowShouldClose(window) == 1);
	return 1;
}

// Sets the key callback.
static int setKeyCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWkeyfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, key, scancode, action, mods);
		};
	}
	glfwSetKeyCallback(window, fun);
	return 0;
}

// Sets the Unicode character callback.
static int setCharCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWcharfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, unsigned int codepoint) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, codepoint);
		};
	}
	glfwSetCharCallback(window, fun);
	return 0;
}

// Sets the mouse button callback.
static int setMouseButtonCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWmousebuttonfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, int button, int action, int mods) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, button, action, mods);
		};
	}
	glfwSetMouseButtonCallback(window, fun);
	return 0;
}

// Sets the cursor position callback.
static int setCursorPosCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWcursorposfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, double xpos, double ypos) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, xpos, ypos);
		};
	}
	glfwSetCursorPosCallback(window, fun);
	return 0;
}

// Sets the cursor enter/exit callback.
static int setCursorEnterCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWcursorenterfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, int entered) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, entered);
		};
	}
	glfwSetCursorEnterCallback(window, fun);
	return 0;
}

// Sets the scroll callback.
static int setScrollCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWscrollfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWwindow* window, double xoffset, double yoffset) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, window, xoffset, yoffset);
		};
	}
	glfwSetScrollCallback(window, fun);
	return 0;
}

// Sets the monitor configuration callback.
static int setMonitorCallback(lua_State* L) {
	auto window = lua_tocast<GLFWwindow*>(L, 1);
	static int ref = NULL;
	GLFWmonitorfun fun = NULL;
	if (lua_setfuncref(L, LUA_REGISTRYINDEX, ref, 2)) {
		fun = [](GLFWmonitor* monitor, int event) {
			auto L = glfw_callback_state;
			lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
			lua_pushpcall(L, 0, monitor, event);
		};
	}
	glfwSetMonitorCallback(fun);
	return 0;
}

int olf::glfw::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		// Clipboard support
		{"setClipboardString", LUA_FULL_WRAP(glfwSetClipboardString)},
		{"getClipboardString", LUA_FULL_WRAP(glfwGetClipboardString)},

		// Context handling
		{"makeContextCurrent", makeContextCurrent},
		{"getCurrentContext", LUA_FULL_WRAP(glfwGetCurrentContext)},
		{"swapBuffers", LUA_FULL_WRAP(glfwSwapBuffers)},
		{"swapInterval", LUA_FULL_WRAP(glfwSwapInterval)},
		{"extensionSupported", LUA_FULL_WRAP(glfwExtensionSupported)},

		// Initialization and version information
		{"init", LUA_FULL_WRAP(glfwInit)},
		{"terminate", LUA_FULL_WRAP(glfwTerminate)},
		{"getVersion", getVersion},
		{"getVersionString", LUA_FULL_WRAP(glfwGetVersionString)},

		// Input handling
		{"getInputMode", LUA_FULL_WRAP(glfwGetInputMode)},
		{"setInputMode", LUA_FULL_WRAP(glfwSetInputMode)},
		{"getKey", LUA_FULL_WRAP(glfwGetKey)},
		{"getMouseButton", LUA_FULL_WRAP(glfwGetMouseButton)},
		{"getCursorPos", getCursorPos},
		{"setCursorPos", LUA_FULL_WRAP(glfwSetCursorPos)},
		{"joystickPresent", LUA_FULL_WRAP(glfwJoystickPresent)},
		{"getJoystickAxes", getJoystickAxes},
		{"getJoystickButtons", getJoystickButtons},
		{"getJoystickName", LUA_FULL_WRAP(glfwGetJoystickName)},
		{"setKeyCallback", setKeyCallback},
		{"setCharCallback", setCharCallback},
		{"setMouseButtonCallback", setMouseButtonCallback},
		{"setCursorPosCallback", setCursorPosCallback},
		{"setCursorEnterCallback", setCursorEnterCallback},
		{"setScrollCallback", setScrollCallback},
		

		// Monitor handling
		{"getMonitors", getMonitors},
		{"getPrimaryMonitor", LUA_FULL_WRAP(glfwGetPrimaryMonitor)},
		{"getMonitorPos", getMonitorPos},
		{"getMonitorPhysicalSize", getMonitorPhysicalSize},
		{"getMonitorName", LUA_FULL_WRAP(glfwGetMonitorName)},
		//{"getVideoModes", getVideoModes},
		//{"getVideoMode", LUA_FULL_WRAP(glfwGetVideoMode)},
		{"setGamma", LUA_FULL_WRAP(glfwSetGamma)},
		//{"getGammaRamp", LUA_FULL_WRAP(glfwGetGammaRamp)},
		//{"setGammaRamp", LUA_FULL_WRAP(glfwSetGammaRamp)},

		// Time input
		{"getTime", LUA_FULL_WRAP(glfwGetTime)},
		{"setTime", LUA_FULL_WRAP(glfwSetTime)},

		// Window handling
		{"defaultWindowHints", LUA_FULL_WRAP(glfwDefaultWindowHints)},
		{"windowHint", LUA_FULL_WRAP(glfwWindowHint)},
		{"createWindow", LUA_FULL_WRAP(glfwCreateWindow)},
		{"destroyWindow", LUA_FULL_WRAP(glfwDestroyWindow)},
		{"windowShouldClose", windowShouldClose},
		{"setWindowShouldClose", LUA_FULL_WRAP(glfwSetWindowShouldClose)},
		{"setWindowTitle", LUA_FULL_WRAP(glfwSetWindowTitle)},
		{"getWindowPos", getWindowPos},
		{"setWindowPos", LUA_FULL_WRAP(glfwSetWindowPos)},
		{"getWindowSize", getWindowSize},
		{"setWindowSize", LUA_FULL_WRAP(glfwSetWindowSize)},
		{"getFramebufferSize", getFramebufferSize},
		{"iconifyWindow", LUA_FULL_WRAP(glfwIconifyWindow)},
		{"restoreWindow", LUA_FULL_WRAP(glfwRestoreWindow)},
		{"showWindow", LUA_FULL_WRAP(glfwShowWindow)},
		{"hideWindow", LUA_FULL_WRAP(glfwHideWindow)},
		{"getWindowMonitor", LUA_FULL_WRAP(glfwGetWindowMonitor)},
		{"getWindowAttrib", LUA_FULL_WRAP(glfwGetWindowAttrib)},
		{"setWindowUserPointer", LUA_FULL_WRAP(glfwSetWindowUserPointer)},
		{"setWindowPosCallback", setWindowPosCallback},
		{"setWindowSizeCallback", setWindowSizeCallback},
		{"setWindowCloseCallback", setWindowCloseCallback},
		{"setWindowRefreshCallback", setWindowRefreshCallback},
		{"setWindowFocusCallback", setWindowFocusCallback},
		{"setWindowIconifyCallback", setWindowIconifyCallback},
		{"setFramebufferSizeCallback", setFramebufferSizeCallback},
		{"pollEvents", LUA_FULL_WRAP(glfwPollEvents)},
		{"waitEvents", LUA_FULL_WRAP(glfwWaitEvents)},
		{NULL, NULL}
	};
	luaL_openlib(L, "glfw", localLib, 0);

	// Error Codes
	lua_pushenumuration(L, "GLFW_NOT_INITIALIZED", GLFW_NOT_INITIALIZED);
	lua_pushenumuration(L, "GLFW_NO_CURRENT_CONTEXT", GLFW_NO_CURRENT_CONTEXT);
	lua_pushenumuration(L, "GLFW_INVALID_ENUM", GLFW_INVALID_ENUM);
	lua_pushenumuration(L, "GLFW_INVALID_VALUE", GLFW_INVALID_VALUE);
	lua_pushenumuration(L, "GLFW_OUT_OF_MEMORY", GLFW_OUT_OF_MEMORY);
	lua_pushenumuration(L, "GLFW_API_UNAVAILABLE", GLFW_API_UNAVAILABLE);
	lua_pushenumuration(L, "GLFW_VERSION_UNAVAILABLE", GLFW_VERSION_UNAVAILABLE);
	lua_pushenumuration(L, "GLFW_PLATFORM_ERROR", GLFW_PLATFORM_ERROR);
	lua_pushenumuration(L, "GLFW_FORMAT_UNAVAILABLE", GLFW_FORMAT_UNAVAILABLE);

	// Version Codes
	lua_pushenumuration(L, "GLFW_VERSION_MAJOR", GLFW_VERSION_MAJOR);
	lua_pushenumuration(L, "GLFW_VERSION_MINOR", GLFW_VERSION_MINOR);
	lua_pushenumuration(L, "GLFW_VERSION_REVISION", GLFW_VERSION_REVISION);

	// Mode
	lua_pushenumuration(L, "GLFW_CURSOR", GLFW_CURSOR);
	lua_pushenumuration(L, "GLFW_STICKY_KEYS", GLFW_STICKY_KEYS);
	lua_pushenumuration(L, "GLFW_STICKY_MOUSE_BUTTONS", GLFW_STICKY_MOUSE_BUTTONS);
	lua_pushenumuration(L, "GLFW_CURSOR_NORMAL", GLFW_CURSOR_NORMAL);
	lua_pushenumuration(L, "GLFW_CURSOR_HIDDEN", GLFW_CURSOR_HIDDEN);
	lua_pushenumuration(L, "GLFW_CURSOR_DISABLED", GLFW_CURSOR_DISABLED);
	lua_pushenumuration(L, "GLFW_PRESS", GLFW_PRESS);
	lua_pushenumuration(L, "GLFW_RELEASE", GLFW_RELEASE);
	lua_pushenumuration(L, "GLFW_REPEAT", GLFW_REPEAT);

	lua_pushenumuration(L, "GLFW_CONNECTED", GLFW_CONNECTED);
	lua_pushenumuration(L, "GLFW_DISCONNECTED", GLFW_DISCONNECTED);

	// Window params
	lua_pushenumuration(L, "GLFW_ICONIFIED", GLFW_ICONIFIED);
	lua_pushenumuration(L, "GLFW_RED_BITS", GLFW_RED_BITS);
	lua_pushenumuration(L, "GLFW_GREEN_BITS", GLFW_GREEN_BITS);
	lua_pushenumuration(L, "GLFW_BLUE_BITS", GLFW_BLUE_BITS);
	lua_pushenumuration(L, "GLFW_ALPHA_BITS", GLFW_ALPHA_BITS);
	lua_pushenumuration(L, "GLFW_DEPTH_BITS", GLFW_DEPTH_BITS);
	lua_pushenumuration(L, "GLFW_STENCIL_BITS", GLFW_STENCIL_BITS);
	lua_pushenumuration(L, "GLFW_RESIZABLE", GLFW_RESIZABLE);
	lua_pushenumuration(L, "GLFW_VISIBLE", GLFW_VISIBLE);
	lua_pushenumuration(L, "GLFW_DECORATED", GLFW_DECORATED);
	lua_pushenumuration(L, "GLFW_REFRESH_RATE", GLFW_REFRESH_RATE);
	lua_pushenumuration(L, "GLFW_ACCUM_RED_BITS", GLFW_ACCUM_RED_BITS);
	lua_pushenumuration(L, "GLFW_ACCUM_GREEN_BITS", GLFW_ACCUM_GREEN_BITS);
	lua_pushenumuration(L, "GLFW_ACCUM_BLUE_BITS", GLFW_ACCUM_BLUE_BITS);
	lua_pushenumuration(L, "GLFW_ACCUM_ALPHA_BITS", GLFW_ACCUM_ALPHA_BITS);
	lua_pushenumuration(L, "GLFW_AUX_BUFFERS", GLFW_AUX_BUFFERS);
	lua_pushenumuration(L, "GLFW_STEREO", GLFW_STEREO);
	lua_pushenumuration(L, "GLFW_CLIENT_API", GLFW_CLIENT_API);
	lua_pushenumuration(L, "GLFW_OPENGL_FORWARD_COMPAT", GLFW_OPENGL_FORWARD_COMPAT);
	lua_pushenumuration(L, "GLFW_OPENGL_DEBUG_CONTEXT", GLFW_OPENGL_DEBUG_CONTEXT);
	lua_pushenumuration(L, "GLFW_OPENGL_PROFILE", GLFW_OPENGL_PROFILE);
	lua_pushenumuration(L, "GLFW_SAMPLES", GLFW_SAMPLES);
	lua_pushenumuration(L, "GLFW_SRGB_CAPABLE", GLFW_SRGB_CAPABLE);
	lua_pushenumuration(L, "GLFW_OPENGL_API", GLFW_OPENGL_API);
	lua_pushenumuration(L, "GLFW_OPENGL_ES_API", GLFW_OPENGL_ES_API);
	lua_pushenumuration(L, "GLFW_CONTEXT_VERSION_MAJOR", GLFW_CONTEXT_VERSION_MAJOR);
	lua_pushenumuration(L, "GLFW_CONTEXT_VERSION_MINOR", GLFW_CONTEXT_VERSION_MINOR);
	lua_pushenumuration(L, "GLFW_OPENGL_ANY_PROFILE", GLFW_OPENGL_ANY_PROFILE);
	lua_pushenumuration(L, "GLFW_CONTEXT_ROBUSTNESS", GLFW_CONTEXT_ROBUSTNESS);
	lua_pushenumuration(L, "GLFW_NO_RESET_NOTIFICATION", GLFW_NO_RESET_NOTIFICATION);
	lua_pushenumuration(L, "GLFW_LOSE_CONTEXT_ON_RESET", GLFW_LOSE_CONTEXT_ON_RESET);
	lua_pushenumuration(L, "GLFW_NO_ROBUSTNESS", GLFW_NO_ROBUSTNESS);
	lua_pushenumuration(L, "GLFW_FOCUSED", GLFW_FOCUSED);
	lua_pushenumuration(L, "GLFW_CONTEXT_REVISION", GLFW_CONTEXT_REVISION);
	lua_pushenumuration(L, "GLFW_CONTEXT_REVISION", GLFW_CONTEXT_REVISION);

	// OpenGL profiles
	lua_pushenumuration(L, "GLFW_OPENGL_CORE_PROFILE", GLFW_OPENGL_CORE_PROFILE);
	lua_pushenumuration(L, "GLFW_OPENGL_COMPAT_PROFILE", GLFW_OPENGL_COMPAT_PROFILE);

	// Modifier key flags
	lua_pushenumuration(L, "GLFW_MOD_SHIFT", GLFW_MOD_SHIFT);
	lua_pushenumuration(L, "GLFW_MOD_CONTROL", GLFW_MOD_CONTROL);
	lua_pushenumuration(L, "GLFW_MOD_ALT", GLFW_MOD_ALT);
	lua_pushenumuration(L, "GLFW_MOD_SUPER", GLFW_MOD_SUPER);

	// Joysticks
	lua_pushenumuration(L, "GLFW_JOYSTICK_1", GLFW_JOYSTICK_1);
	lua_pushenumuration(L, "GLFW_JOYSTICK_2", GLFW_JOYSTICK_2);
	lua_pushenumuration(L, "GLFW_JOYSTICK_3", GLFW_JOYSTICK_3);
	lua_pushenumuration(L, "GLFW_JOYSTICK_4", GLFW_JOYSTICK_4);
	lua_pushenumuration(L, "GLFW_JOYSTICK_5", GLFW_JOYSTICK_5);
	lua_pushenumuration(L, "GLFW_JOYSTICK_6", GLFW_JOYSTICK_6);
	lua_pushenumuration(L, "GLFW_JOYSTICK_7", GLFW_JOYSTICK_7);
	lua_pushenumuration(L, "GLFW_JOYSTICK_8", GLFW_JOYSTICK_8);
	lua_pushenumuration(L, "GLFW_JOYSTICK_9", GLFW_JOYSTICK_9);
	lua_pushenumuration(L, "GLFW_JOYSTICK_10", GLFW_JOYSTICK_10);
	lua_pushenumuration(L, "GLFW_JOYSTICK_11", GLFW_JOYSTICK_11);
	lua_pushenumuration(L, "GLFW_JOYSTICK_12", GLFW_JOYSTICK_12);
	lua_pushenumuration(L, "GLFW_JOYSTICK_13", GLFW_JOYSTICK_13);
	lua_pushenumuration(L, "GLFW_JOYSTICK_14", GLFW_JOYSTICK_14);
	lua_pushenumuration(L, "GLFW_JOYSTICK_15", GLFW_JOYSTICK_15);
	lua_pushenumuration(L, "GLFW_JOYSTICK_16", GLFW_JOYSTICK_16);
	lua_pushenumuration(L, "GLFW_JOYSTICK_LAST", GLFW_JOYSTICK_LAST);

	// Mouse buttons
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_1", GLFW_MOUSE_BUTTON_1);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_2", GLFW_MOUSE_BUTTON_2);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_3", GLFW_MOUSE_BUTTON_3);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_4", GLFW_MOUSE_BUTTON_4);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_5", GLFW_MOUSE_BUTTON_5);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_6", GLFW_MOUSE_BUTTON_6);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_7", GLFW_MOUSE_BUTTON_7);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_8", GLFW_MOUSE_BUTTON_8);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_LAST", GLFW_MOUSE_BUTTON_LAST);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_LEFT", GLFW_MOUSE_BUTTON_LEFT);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_RIGHT", GLFW_MOUSE_BUTTON_RIGHT);
	lua_pushenumuration(L, "GLFW_MOUSE_BUTTON_MIDDLE", GLFW_MOUSE_BUTTON_MIDDLE);

	// Keyboard keys
	lua_pushenumuration(L, "GLFW_KEY_UNKNOWN", GLFW_KEY_UNKNOWN);
	lua_pushenumuration(L, "GLFW_KEY_SPACE", GLFW_KEY_SPACE);
	lua_pushenumuration(L, "GLFW_KEY_APOSTROPHE", GLFW_KEY_APOSTROPHE);
	lua_pushenumuration(L, "GLFW_KEY_COMMA", GLFW_KEY_COMMA);
	lua_pushenumuration(L, "GLFW_KEY_MINUS", GLFW_KEY_MINUS);
	lua_pushenumuration(L, "GLFW_KEY_PERIOD", GLFW_KEY_PERIOD);
	lua_pushenumuration(L, "GLFW_KEY_SLASH", GLFW_KEY_SLASH);
	lua_pushenumuration(L, "GLFW_KEY_0", GLFW_KEY_0);
	lua_pushenumuration(L, "GLFW_KEY_1", GLFW_KEY_1);
	lua_pushenumuration(L, "GLFW_KEY_2", GLFW_KEY_2);
	lua_pushenumuration(L, "GLFW_KEY_3", GLFW_KEY_3);
	lua_pushenumuration(L, "GLFW_KEY_4", GLFW_KEY_4);
	lua_pushenumuration(L, "GLFW_KEY_5", GLFW_KEY_5);
	lua_pushenumuration(L, "GLFW_KEY_6", GLFW_KEY_6);
	lua_pushenumuration(L, "GLFW_KEY_7", GLFW_KEY_7);
	lua_pushenumuration(L, "GLFW_KEY_8", GLFW_KEY_8);
	lua_pushenumuration(L, "GLFW_KEY_9", GLFW_KEY_9);
	lua_pushenumuration(L, "GLFW_KEY_SEMICOLON", GLFW_KEY_SEMICOLON);
	lua_pushenumuration(L, "GLFW_KEY_EQUAL", GLFW_KEY_EQUAL);
	lua_pushenumuration(L, "GLFW_KEY_A", GLFW_KEY_A);
	lua_pushenumuration(L, "GLFW_KEY_B", GLFW_KEY_B);
	lua_pushenumuration(L, "GLFW_KEY_C", GLFW_KEY_C);
	lua_pushenumuration(L, "GLFW_KEY_D", GLFW_KEY_D);
	lua_pushenumuration(L, "GLFW_KEY_E", GLFW_KEY_E);
	lua_pushenumuration(L, "GLFW_KEY_F", GLFW_KEY_F);
	lua_pushenumuration(L, "GLFW_KEY_G", GLFW_KEY_G);
	lua_pushenumuration(L, "GLFW_KEY_H", GLFW_KEY_H);
	lua_pushenumuration(L, "GLFW_KEY_I", GLFW_KEY_I);
	lua_pushenumuration(L, "GLFW_KEY_J", GLFW_KEY_J);
	lua_pushenumuration(L, "GLFW_KEY_K", GLFW_KEY_K);
	lua_pushenumuration(L, "GLFW_KEY_L", GLFW_KEY_L);
	lua_pushenumuration(L, "GLFW_KEY_M", GLFW_KEY_M);
	lua_pushenumuration(L, "GLFW_KEY_N", GLFW_KEY_N);
	lua_pushenumuration(L, "GLFW_KEY_O", GLFW_KEY_O);
	lua_pushenumuration(L, "GLFW_KEY_P", GLFW_KEY_P);
	lua_pushenumuration(L, "GLFW_KEY_Q", GLFW_KEY_Q);
	lua_pushenumuration(L, "GLFW_KEY_R", GLFW_KEY_R);
	lua_pushenumuration(L, "GLFW_KEY_S", GLFW_KEY_S);
	lua_pushenumuration(L, "GLFW_KEY_T", GLFW_KEY_T);
	lua_pushenumuration(L, "GLFW_KEY_U", GLFW_KEY_U);
	lua_pushenumuration(L, "GLFW_KEY_V", GLFW_KEY_V);
	lua_pushenumuration(L, "GLFW_KEY_W", GLFW_KEY_W);
	lua_pushenumuration(L, "GLFW_KEY_X", GLFW_KEY_X);
	lua_pushenumuration(L, "GLFW_KEY_Y", GLFW_KEY_Y);
	lua_pushenumuration(L, "GLFW_KEY_Z", GLFW_KEY_Z);
	lua_pushenumuration(L, "GLFW_KEY_LEFT_BRACKET", GLFW_KEY_LEFT_BRACKET);
	lua_pushenumuration(L, "GLFW_KEY_BACKSLASH", GLFW_KEY_BACKSLASH);
	lua_pushenumuration(L, "GLFW_KEY_RIGHT_BRACKET", GLFW_KEY_RIGHT_BRACKET);
	lua_pushenumuration(L, "GLFW_KEY_GRAVE_ACCENT", GLFW_KEY_GRAVE_ACCENT);
	lua_pushenumuration(L, "GLFW_KEY_WORLD_1", GLFW_KEY_WORLD_1);
	lua_pushenumuration(L, "GLFW_KEY_WORLD_2", GLFW_KEY_WORLD_2);
	lua_pushenumuration(L, "GLFW_KEY_ESCAPE", GLFW_KEY_ESCAPE);
	lua_pushenumuration(L, "GLFW_KEY_ENTER", GLFW_KEY_ENTER);
	lua_pushenumuration(L, "GLFW_KEY_TAB", GLFW_KEY_TAB);
	lua_pushenumuration(L, "GLFW_KEY_BACKSPACE", GLFW_KEY_BACKSPACE);
	lua_pushenumuration(L, "GLFW_KEY_INSERT", GLFW_KEY_INSERT);
	lua_pushenumuration(L, "GLFW_KEY_DELETE", GLFW_KEY_DELETE);
	lua_pushenumuration(L, "GLFW_KEY_RIGHT", GLFW_KEY_RIGHT);
	lua_pushenumuration(L, "GLFW_KEY_LEFT", GLFW_KEY_LEFT);
	lua_pushenumuration(L, "GLFW_KEY_DOWN", GLFW_KEY_DOWN);
	lua_pushenumuration(L, "GLFW_KEY_UP", GLFW_KEY_UP);
	lua_pushenumuration(L, "GLFW_KEY_PAGE_UP", GLFW_KEY_PAGE_UP);
	lua_pushenumuration(L, "GLFW_KEY_PAGE_DOWN", GLFW_KEY_PAGE_DOWN);
	lua_pushenumuration(L, "GLFW_KEY_HOME", GLFW_KEY_HOME);
	lua_pushenumuration(L, "GLFW_KEY_END", GLFW_KEY_END);
	lua_pushenumuration(L, "GLFW_KEY_CAPS_LOCK", GLFW_KEY_CAPS_LOCK);
	lua_pushenumuration(L, "GLFW_KEY_SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK);
	lua_pushenumuration(L, "GLFW_KEY_NUM_LOCK", GLFW_KEY_NUM_LOCK);
	lua_pushenumuration(L, "GLFW_KEY_PRINT_SCREEN", GLFW_KEY_PRINT_SCREEN);
	lua_pushenumuration(L, "GLFW_KEY_PAUSE", GLFW_KEY_PAUSE);
	lua_pushenumuration(L, "GLFW_KEY_F1", GLFW_KEY_F1);
	lua_pushenumuration(L, "GLFW_KEY_F2", GLFW_KEY_F2);
	lua_pushenumuration(L, "GLFW_KEY_F3", GLFW_KEY_F3);
	lua_pushenumuration(L, "GLFW_KEY_F4", GLFW_KEY_F4);
	lua_pushenumuration(L, "GLFW_KEY_F5", GLFW_KEY_F5);
	lua_pushenumuration(L, "GLFW_KEY_F6", GLFW_KEY_F6);
	lua_pushenumuration(L, "GLFW_KEY_F7", GLFW_KEY_F7);
	lua_pushenumuration(L, "GLFW_KEY_F8", GLFW_KEY_F8);
	lua_pushenumuration(L, "GLFW_KEY_F9", GLFW_KEY_F9);
	lua_pushenumuration(L, "GLFW_KEY_F10", GLFW_KEY_F10);
	lua_pushenumuration(L, "GLFW_KEY_F11", GLFW_KEY_F11);
	lua_pushenumuration(L, "GLFW_KEY_F12", GLFW_KEY_F12);
	lua_pushenumuration(L, "GLFW_KEY_F13", GLFW_KEY_F13);
	lua_pushenumuration(L, "GLFW_KEY_F14", GLFW_KEY_F14);
	lua_pushenumuration(L, "GLFW_KEY_F15", GLFW_KEY_F15);
	lua_pushenumuration(L, "GLFW_KEY_F16", GLFW_KEY_F16);
	lua_pushenumuration(L, "GLFW_KEY_F17", GLFW_KEY_F17);
	lua_pushenumuration(L, "GLFW_KEY_F18", GLFW_KEY_F18);
	lua_pushenumuration(L, "GLFW_KEY_F19", GLFW_KEY_F19);
	lua_pushenumuration(L, "GLFW_KEY_F20", GLFW_KEY_F20);
	lua_pushenumuration(L, "GLFW_KEY_F21", GLFW_KEY_F21);
	lua_pushenumuration(L, "GLFW_KEY_F22", GLFW_KEY_F22);
	lua_pushenumuration(L, "GLFW_KEY_F23", GLFW_KEY_F23);
	lua_pushenumuration(L, "GLFW_KEY_F24", GLFW_KEY_F24);
	lua_pushenumuration(L, "GLFW_KEY_F25", GLFW_KEY_F25);
	lua_pushenumuration(L, "GLFW_KEY_KP_0", GLFW_KEY_KP_0);
	lua_pushenumuration(L, "GLFW_KEY_KP_1", GLFW_KEY_KP_1);
	lua_pushenumuration(L, "GLFW_KEY_KP_2", GLFW_KEY_KP_2);
	lua_pushenumuration(L, "GLFW_KEY_KP_3", GLFW_KEY_KP_3);
	lua_pushenumuration(L, "GLFW_KEY_KP_4", GLFW_KEY_KP_4);
	lua_pushenumuration(L, "GLFW_KEY_KP_5", GLFW_KEY_KP_5);
	lua_pushenumuration(L, "GLFW_KEY_KP_6", GLFW_KEY_KP_6);
	lua_pushenumuration(L, "GLFW_KEY_KP_7", GLFW_KEY_KP_7);
	lua_pushenumuration(L, "GLFW_KEY_KP_8", GLFW_KEY_KP_8);
	lua_pushenumuration(L, "GLFW_KEY_KP_9", GLFW_KEY_KP_9);
	lua_pushenumuration(L, "GLFW_KEY_KP_DECIMAL", GLFW_KEY_KP_DECIMAL);
	lua_pushenumuration(L, "GLFW_KEY_KP_DIVIDE", GLFW_KEY_KP_DIVIDE);
	lua_pushenumuration(L, "GLFW_KEY_KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY);
	lua_pushenumuration(L, "GLFW_KEY_KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT);
	lua_pushenumuration(L, "GLFW_KEY_KP_ADD", GLFW_KEY_KP_ADD);
	lua_pushenumuration(L, "GLFW_KEY_KP_ENTER", GLFW_KEY_KP_ENTER);
	lua_pushenumuration(L, "GLFW_KEY_KP_EQUAL", GLFW_KEY_KP_EQUAL);
	lua_pushenumuration(L, "GLFW_KEY_LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT);
	lua_pushenumuration(L, "GLFW_KEY_LEFT_CONTROL", GLFW_KEY_LEFT_CONTROL);
	lua_pushenumuration(L, "GLFW_KEY_LEFT_ALT", GLFW_KEY_LEFT_ALT);
	lua_pushenumuration(L, "GLFW_KEY_LEFT_SUPER", GLFW_KEY_LEFT_SUPER);
	lua_pushenumuration(L, "GLFW_KEY_RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT);
	lua_pushenumuration(L, "GLFW_KEY_RIGHT_CONTROL", GLFW_KEY_RIGHT_CONTROL);
	lua_pushenumuration(L, "GLFW_KEY_RIGHT_ALT", GLFW_KEY_RIGHT_ALT);
	lua_pushenumuration(L, "GLFW_KEY_RIGHT_SUPER", GLFW_KEY_RIGHT_SUPER);
	lua_pushenumuration(L, "GLFW_KEY_MENU", GLFW_KEY_MENU);
	lua_pushenumuration(L, "GLFW_KEY_LAST", GLFW_KEY_LAST);

	glfw_callback_state = L;

	return 1;
}
