#include "luaInput.h"

#include <GLFW/glfw3.h>
#include "olua.h"

#include <string>

using namespace olf::input;
//
//static int lastMouseX = -1;
//static int lastMouseY = -1;
//static int mouseDeltaX = 0;
//static int mouseDeltaY = 0;
//
//// Internal use only!
//static int luaGLFWSetFeature(const int enabled, int feature) {
//	if (enabled == 1)
//		glfwEnable(feature);
//	else
//		glfwDisable(feature);
//	return 0;
//}
//
//// Returns true if the key is pressed
//// Takes (key) Returns (pressed)
//static int getKey(lua_State* L) {
//	auto keyIndex = lua_tocast<int>(L, 1);
//	if (lua_isstring(L, 1))
//		keyIndex = static_cast<int>(lua_tostring(L, 1)[0]);
//
//	lua_push(L, glfwGetKey(keyIndex) == GLFW_PRESS);
//	return 1;
//}
//
//// Returns true if the mouse button is pressed
//// Takes (mouseButton) Returns (pressed)
//static int getMouseButton(lua_State* L) {
//	auto buttonIndex = lua_tocast<int>(L, 1);
//
//	lua_push(L, glfwGetMouseButton(buttonIndex) == GLFW_PRESS);
//	return 1;
//}
//
//// Sets and gets the pos of the mouse
//// Takes (x, y)
//static int setMousePos(lua_State* L) {
//	auto x = lua_tocast<int>(L, 1);
//	auto y = lua_tocast<int>(L, 2);
//	glfwSetMousePos(x, y);
//	lastMouseX = x;
//	lastMouseY = y;
//	return 0;
//}
//// Returns (x, y)
//static int getMousePos(lua_State* L) {
//	int posX, posY;
//	glfwGetMousePos(&posX, &posY);
//	lua_pushnumber(L, posX);
//	lua_pushnumber(L, posY);
//	return 2;
//}
//
//// Gets the delta mouse pos
//// Returns (x, y)
//static int getMouseDeltaPos(lua_State* L) {
//	lua_pushnumber(L, mouseDeltaX);
//	lua_pushnumber(L, mouseDeltaY);
//	return 2;
//}
//
//// Sets and gets the mouse wheel pos (z axis)
//// Takes (pos)
//static int setMouseWheel(lua_State* L) {
//	return lua_wrapfunction(L, glfwSetMouseWheel);
//}
//// Returns (pos)
//static int getMouseWheel(lua_State* L) {
//	return lua_wrapfunction(L, glfwGetMouseWheel);
//}
//
//// Sets whether sticky keys is enabled (The key will stay in state until it is checked by getKey)
//// Takes (enabled)
//static int setStickyKeys(lua_State* L) {
//	return luaGLFWSetFeature(lua_toboolean(L, 1), GLFW_STICKY_KEYS);
//}
//
//// Sets whether sticky mouse buttons is enabled (The key will stay in state until it is checked by getKey)
//// Takes (enabled)
//static int setStickyMouseButtons(lua_State* L) {
//	return luaGLFWSetFeature(lua_toboolean(L, 1), GLFW_STICKY_MOUSE_BUTTONS);
//}
//
//// Sets whether a key can continue to send events while being held down.
//// Takes (enabled)
//static int setKeyRepeat(lua_State* L) {
//	return luaGLFWSetFeature(lua_toboolean(L, 1), GLFW_KEY_REPEAT);
//}
//
//// Sets whether system keys are enabled (ex. ALT+TAB)
//// Takes (enabled)
//static int setSystemKeys(lua_State* L) {
//	return luaGLFWSetFeature(lua_toboolean(L, 1), GLFW_SYSTEM_KEYS);
//}
//
//// Sets whether the mouse cursor is visible or not.
//// Takes (enabled)
//static int setMouseVisible(lua_State* L) {
//	return luaGLFWSetFeature(lua_toboolean(L, 1), GLFW_MOUSE_CURSOR);
//}
//
//// Returns true if a joystick is present
//// Takes (joyID) Returns (exists)
//static int getJoystickExists(lua_State* L) {
//	lua_pushboolean(L, glfwGetJoystickParam(lua_tocast<int>(L, 1), GLFW_PRESENT));
//	return 1;
//}
//
//// Returns the number of axes supported by the joystick
//// Takes (joyID) Returns (axes)
//static int getJoystickAxes(lua_State* L) {
//	lua_pushnumber(L, glfwGetJoystickParam(lua_tocast<int>(L, 1), GLFW_AXES));
//	return 1;
//}
//
//// Returns the number of buttons supported by the joy stick
//// Takes (joyID) Returns (buttons)
//static int getJoystickButtons(lua_State* L) {
//	lua_pushnumber(L, glfwGetJoystickParam(lua_tocast<int>(L, 1), GLFW_BUTTONS));
//	return 1;
//}
//
//// Returns a table of the axis poses
//// Takes (joyID, requestAxes) Returns (posTable)
//static int getJoystickPos(lua_State* L) {
//	auto joyID = lua_tocast<int>(L, 1);
//	auto requestAxes = lua_tocast<int>(L, 2);
//	auto pos = new float[requestAxes];
//
//	int actualAxes = glfwGetJoystickPos(joyID, pos, requestAxes);
//	if (actualAxes > 0) {
//		lua_pusharray(L, pos, actualAxes, true);
//		return 1;
//	}
//
//	delete [] pos;
//	return 0;
//}
//
//// Returns if a joystick button is pressed
//// Takes (joyID, buttonID) Returns (pressed)
//static int getJoystickButton(lua_State* L) {
//	auto joyID = lua_tocast<int>(L, 1);
//	auto buttonID = lua_tocast<int>(L, 2);
//	auto buttonStates = new unsigned char[buttonID + 1];
//	auto returnedButtons = glfwGetJoystickButtons(joyID, buttonStates, buttonID + 1);
//
//	if (returnedButtons > 0) {
//		lua_pushboolean(L, buttonStates[buttonID] == GLFW_PRESS);
//		delete [] buttonStates;
//		return 1;
//	}
//	delete [] buttonStates;
//	return 0;
//}
//
//void GLFWCALL MousePosCallback(int x, int y) {
//	// TODO: Call lua call back function
//}
//void GLFWCALL MouseWheelCallback(int pos) {
//	// TODO: Call lua call back function
//}
//
//void olf::input::update() {
//	int curX, curY;
//	glfwGetMousePos(&curX, &curY);
//
//	if (lastMouseX >= 0 && lastMouseY >= 0) {
//		mouseDeltaX = curX - lastMouseX;
//		mouseDeltaY = curY - lastMouseY;
//	}
//
//	lastMouseX = curX;
//	lastMouseY = curY;
//}

int olf::input::registerLua(lua_State* L) {
	//const struct luaL_reg localLib[] = {
	//	{"getKey", getKey},
	//	{"getMouseButton", getMouseButton},
	//	{"setMousePos", setMousePos},
	//	{"getMousePos", getMousePos},
	//	{"getMouseDeltaPos", getMouseDeltaPos},
	//	{"setMouseWheel", setMouseWheel},
	//	{"getMouseWheel", getMouseWheel},
	//	{"setStickyKeys", setStickyKeys},
	//	{"setStickyMouseButtons", setStickyMouseButtons},
	//	{"setKeyRepeat", setKeyRepeat},
	//	{"setSystemKeys", setSystemKeys},
	//	{"setMouseVisible", setMouseVisible},
	//	{"getJoystickExists", getJoystickExists},
	//	{"getJoystickAxes", getJoystickAxes},
	//	{"getJoystickButtons", getJoystickButtons},
	//	{"getJoystickPos", getJoystickPos},
	//	{"getJoystickButton", getJoystickButton},
	//	{NULL, NULL}
	//};
	//luaL_openlib(L, "input", localLib, 0);

	//lua_pushenumuration(L, "INPUT_KEY_SPACE", GLFW_KEY_SPACE);
	//lua_pushenumuration(L, "INPUT_KEY_ESC", GLFW_KEY_ESC);
	//lua_pushenumuration(L, "INPUT_KEY_F1", GLFW_KEY_F1);
	//lua_pushenumuration(L, "INPUT_KEY_F2", GLFW_KEY_F2);
	//lua_pushenumuration(L, "INPUT_KEY_F3", GLFW_KEY_F3);
	//lua_pushenumuration(L, "INPUT_KEY_F4", GLFW_KEY_F4);
	//lua_pushenumuration(L, "INPUT_KEY_F5", GLFW_KEY_F5);
	//lua_pushenumuration(L, "INPUT_KEY_F6", GLFW_KEY_F6);
	//lua_pushenumuration(L, "INPUT_KEY_F7", GLFW_KEY_F7);
	//lua_pushenumuration(L, "INPUT_KEY_F8", GLFW_KEY_F8);
	//lua_pushenumuration(L, "INPUT_KEY_F9", GLFW_KEY_F9);
	//lua_pushenumuration(L, "INPUT_KEY_F10", GLFW_KEY_F10);
	//lua_pushenumuration(L, "INPUT_KEY_F11", GLFW_KEY_F11);
	//lua_pushenumuration(L, "INPUT_KEY_F12", GLFW_KEY_F12);
	//lua_pushenumuration(L, "INPUT_KEY_UP", GLFW_KEY_UP);
	//lua_pushenumuration(L, "INPUT_KEY_DOWN", GLFW_KEY_DOWN);
	//lua_pushenumuration(L, "INPUT_KEY_LEFT", GLFW_KEY_LEFT);
	//lua_pushenumuration(L, "INPUT_KEY_RIGHT", GLFW_KEY_RIGHT);
	//lua_pushenumuration(L, "INPUT_KEY_LSHIFT", GLFW_KEY_LSHIFT);
	//lua_pushenumuration(L, "INPUT_KEY_RSHIFT", GLFW_KEY_RSHIFT);
	//lua_pushenumuration(L, "INPUT_KEY_LCTRL", GLFW_KEY_LCTRL);
	//lua_pushenumuration(L, "INPUT_KEY_RCTRL", GLFW_KEY_RCTRL);
	//lua_pushenumuration(L, "INPUT_KEY_LALT", GLFW_KEY_LALT);
	//lua_pushenumuration(L, "INPUT_KEY_RALT", GLFW_KEY_RALT);
	//lua_pushenumuration(L, "INPUT_KEY_LSUPER", GLFW_KEY_LSUPER);
	//lua_pushenumuration(L, "INPUT_KEY_RSUPER", GLFW_KEY_RSUPER);
	//lua_pushenumuration(L, "INPUT_KEY_TAB", GLFW_KEY_TAB);
	//lua_pushenumuration(L, "INPUT_KEY_ENTER", GLFW_KEY_ENTER);
	//lua_pushenumuration(L, "INPUT_KEY_BACKSPACE", GLFW_KEY_BACKSPACE);
	//lua_pushenumuration(L, "INPUT_KEY_INSERT", GLFW_KEY_INSERT);
	//lua_pushenumuration(L, "INPUT_KEY_DEL", GLFW_KEY_DEL);
	//lua_pushenumuration(L, "INPUT_KEY_PAGEUP", GLFW_KEY_PAGEUP);
	//lua_pushenumuration(L, "INPUT_KEY_PAGEDOWN", GLFW_KEY_PAGEDOWN);
	//lua_pushenumuration(L, "INPUT_KEY_HOME", GLFW_KEY_HOME);
	//lua_pushenumuration(L, "INPUT_KEY_END", GLFW_KEY_END);
	//lua_pushenumuration(L, "INPUT_KEY_KP_0", GLFW_KEY_KP_0);
	//lua_pushenumuration(L, "INPUT_KEY_KP_1", GLFW_KEY_KP_1);
	//lua_pushenumuration(L, "INPUT_KEY_KP_2", GLFW_KEY_KP_2);
	//lua_pushenumuration(L, "INPUT_KEY_KP_3", GLFW_KEY_KP_3);
	//lua_pushenumuration(L, "INPUT_KEY_KP_4", GLFW_KEY_KP_4);
	//lua_pushenumuration(L, "INPUT_KEY_KP_5", GLFW_KEY_KP_5);
	//lua_pushenumuration(L, "INPUT_KEY_KP_6", GLFW_KEY_KP_6);
	//lua_pushenumuration(L, "INPUT_KEY_KP_7", GLFW_KEY_KP_7);
	//lua_pushenumuration(L, "INPUT_KEY_KP_8", GLFW_KEY_KP_9);
	//lua_pushenumuration(L, "INPUT_KEY_KP_9", GLFW_KEY_KP_9);
	//lua_pushenumuration(L, "INPUT_KEY_KP_DIVIDE", GLFW_KEY_KP_DIVIDE);
	//lua_pushenumuration(L, "INPUT_KEY_KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY);
	//lua_pushenumuration(L, "INPUT_KEY_KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT);
	//lua_pushenumuration(L, "INPUT_KEY_KP_ADD", GLFW_KEY_KP_ADD);
	//lua_pushenumuration(L, "INPUT_KEY_KP_DECIMAL", GLFW_KEY_KP_DECIMAL);
	//lua_pushenumuration(L, "INPUT_KEY_KP_EQUAL", GLFW_KEY_KP_EQUAL);
	//lua_pushenumuration(L, "INPUT_KEY_KP_ENTER", GLFW_KEY_KP_ENTER);
	//lua_pushenumuration(L, "INPUT_KEY_KP_NUM_LOCK", GLFW_KEY_KP_NUM_LOCK);
	//lua_pushenumuration(L, "INPUT_KEY_CAPS_LOCK", GLFW_KEY_CAPS_LOCK);
	//lua_pushenumuration(L, "INPUT_KEY_SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK);
	//lua_pushenumuration(L, "INPUT_KEY_PAUSE", GLFW_KEY_PAUSE);
	//lua_pushenumuration(L, "INPUT_KEY_MENU", GLFW_KEY_MENU);

	//lua_pushenumuration(L, "INPUT_MOUSE_LEFT", GLFW_MOUSE_BUTTON_LEFT);
	//lua_pushenumuration(L, "INPUT_MOUSE_RIGHT", GLFW_MOUSE_BUTTON_RIGHT);
	//lua_pushenumuration(L, "INPUT_MOUSE_MIDDLE", GLFW_MOUSE_BUTTON_MIDDLE);
	//lua_pushenumuration(L, "INPUT_MOUSE_1", GLFW_MOUSE_BUTTON_1);
	//lua_pushenumuration(L, "INPUT_MOUSE_2", GLFW_MOUSE_BUTTON_2);
	//lua_pushenumuration(L, "INPUT_MOUSE_3", GLFW_MOUSE_BUTTON_3);
	//lua_pushenumuration(L, "INPUT_MOUSE_4", GLFW_MOUSE_BUTTON_4);
	//lua_pushenumuration(L, "INPUT_MOUSE_5", GLFW_MOUSE_BUTTON_5);
	//lua_pushenumuration(L, "INPUT_MOUSE_6", GLFW_MOUSE_BUTTON_6);
	//lua_pushenumuration(L, "INPUT_MOUSE_7", GLFW_MOUSE_BUTTON_7);
	//lua_pushenumuration(L, "INPUT_MOUSE_8", GLFW_MOUSE_BUTTON_8);

	//// Set up call backs
	//glfwSetMousePosCallback(MousePosCallback);
	//glfwSetMouseWheelCallback(MouseWheelCallback);

	return 1;
}
