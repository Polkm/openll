#include "olua.h"

#include "Vector3.h"

#include <stdarg.h>
#include <assert.h>
#include <GL/glew.h>
#include <iostream>

#include <btBulletDynamicsCommon.h>

int lua_callFunc(lua_State* L, const int index, const char* funcName, double arg, double arg2, double arg3) {
	int result;
	// Push functions and arguments
	lua_getfield(L, index, funcName);
	lua_pushnumber(L, arg);
	lua_pushnumber(L, arg2);
	lua_pushnumber(L, arg3);
	
	if (lua_pcall(L, 3, 1, 0) != 0) {
        //std::cout << lua_tostring(L, -1);
	}

	result = static_cast<int>(lua_tonumber(L, -1));
	lua_pop(L, 1); // pop returned value
	return result;
}

int lua_callFunc(lua_State* L, const char* modName, const char* funcName, double arg, double arg2, double arg3) {
	int result;
	lua_getfield(L, LUA_GLOBALSINDEX, modName);
	result = lua_callFunc(L, -1, funcName, arg, arg2, arg3);
	lua_remove(L, -1);
	return result;
}

void lua_pushnumbertoglobal(lua_State* L, const char* globalName, const char* key, double value) {
	lua_getfield(L, LUA_GLOBALSINDEX, globalName);
	lua_pushnumber(L, value);
	lua_setfield(L, -2, key);
	lua_pop(L, 1);
}

void lua_pushenumuration(lua_State* L, const char* enumName, int value) {
	lua_pushnumber(L, value);
	lua_setglobal(L, enumName);
}

void* lua_tabletoglarray(lua_State* L, int index, GLenum type) {
	switch (type) {
	case GL_FLOAT:
		return lua_tabletobasicarray<GLfloat>(L, index);
	case GL_DOUBLE:
		return lua_tabletobasicarray<GLdouble>(L, index);
	case GL_INT:
		return lua_tabletobasicarray<GLint>(L, index);
	case GL_UNSIGNED_INT:
		return lua_tabletobasicarray<GLuint>(L, index);
	case GL_BYTE:
		return lua_tabletobasicarray<GLbyte>(L, index);
	case GL_UNSIGNED_BYTE:
		return lua_tabletobasicarray<GLubyte>(L, index);
	case GL_SHORT:
		return lua_tabletobasicarray<GLshort>(L, index);
	case GL_UNSIGNED_SHORT:
		return lua_tabletobasicarray<GLushort>(L, index);
	default:
		return nullptr;
	}
}
void* lua_tabletoglarray(lua_State* L, int index, GLenum type, GLsizeiptr& size) {
	size = luaL_getn(L, index);
	switch (type) {
	case GL_FLOAT:
		size *= sizeof(GLfloat);
		return lua_tabletobasicarray<GLfloat>(L, index);
	case GL_DOUBLE:
		size *= sizeof(GLdouble);
		return lua_tabletobasicarray<GLdouble>(L, index);
	case GL_INT:
		size *= sizeof(GLint);
		return lua_tabletobasicarray<GLint>(L, index);
	case GL_UNSIGNED_INT:
		size *= sizeof(GLuint);
		return lua_tabletobasicarray<GLuint>(L, index);
	case GL_BYTE:
		size *= sizeof(GLbyte);
		return lua_tabletobasicarray<GLbyte>(L, index);
	case GL_UNSIGNED_BYTE:
		size *= sizeof(GLubyte);
		return lua_tabletobasicarray<GLubyte>(L, index);
	case GL_SHORT:
		size *= sizeof(GLshort);
		return lua_tabletobasicarray<GLshort>(L, index);
	case GL_UNSIGNED_SHORT:
		size *= sizeof(GLushort);
		return lua_tabletobasicarray<GLushort>(L, index);
	default:
		return nullptr;
	}
}

GLuint luaGLGetParamCount(GLenum pname) {
	if (pname == GL_ALIASED_LINE_WIDTH_RANGE || pname == GL_DEPTH_RANGE ||
		pname == GL_LINE_WIDTH_RANGE || pname == GL_MAX_VIEWPORT_DIMS ||
		pname == GL_POINT_SIZE_RANGE || pname == GL_SMOOTH_LINE_WIDTH_RANGE)
		return 2;
#ifdef GL_VERSION_4_1
	if (pname == GL_VIEWPORT_BOUNDS_RANGE)
		return 2;
#endif
	if (pname == GL_BLEND_COLOR || pname == GL_COLOR_CLEAR_VALUE ||
		pname == GL_COLOR_WRITEMASK || pname == GL_SCISSOR_BOX ||
		pname == GL_VIEWPORT)
		return 4;
	if (pname == GL_COMPRESSED_TEXTURE_FORMATS)
		return GL_NUM_COMPRESSED_TEXTURE_FORMATS;
	if (pname == GL_PROGRAM_BINARY_FORMATS)
		return GL_NUM_PROGRAM_BINARY_FORMATS;
	return 1;
}

Vector3 lua_tovector3(lua_State* L, int index) {
	float data[3];
	lua_toarray<float, 3>(L, index, data);
	return Vector3(data);
}

btVector3 lua_tobtvector3(lua_State* L, int index) {
	float data[3];
	lua_toarray<float, 3>(L, index, data);
	return btVector3(data[0], data[1], data[2]);
}

const char** lua_tabletolstringarray(lua_State* L, int index, int* lengths) {
	const char** data = new const char*[luaL_getn(L, index)];

	int i = 0;
	lua_pushnil(L);
	if (index < 0) index -= 1;
	while (lua_next(L, index) != 0) {
		data[i] = lua_tostring(L, -1);
		if (lengths != nullptr)
			lengths[i] = strlen(data[i]);
		lua_pop(L, 1);
		++i;
	}

	return data;
}