#ifndef __OLF_OLUA_H__
#define __OLF_OLUA_H__

#include <cstring>
#include <vector>
#include <list>
#include <iostream>
#include <type_traits>

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include "lua_wrap.h"
#include "lua_class.h"

class Vector3;
class btVector3;

// Takes a generic type and gets the value from Lua
// and casts it to the right type.
template<typename T>
inline T lua_tocast(lua_State* L, int index) {
	return reinterpret_cast<T>(lua_touserdata(L, index));
}
template<>
inline void* lua_tocast<void*>(lua_State* L, int index) {
	return lua_touserdata(L, index);
}
template<>
inline bool lua_tocast<bool>(lua_State* L, int index) {
	return static_cast<int>(lua_tonumber(L, index)) == 1;
}
template<>
inline char lua_tocast<char>(lua_State* L, int index) {
	return static_cast<char>(lua_tonumber(L, index));
}
template<>
inline char16_t lua_tocast<char16_t>(lua_State* L, int index) {
	return static_cast<char16_t>(lua_tonumber(L, index));
}
//template<>
//inline char32_t lua_tocast<char32_t>(lua_State* L, int index) {
//	return static_cast<char32_t>(lua_tonumber(L, index));
//}
template<>
inline wchar_t lua_tocast<wchar_t>(lua_State* L, int index) {
	return static_cast<wchar_t>(lua_tonumber(L, index));
}
template<>
inline signed char lua_tocast<signed char>(lua_State* L, int index) {
	return static_cast<signed char>(lua_tonumber(L, index));
}
template<>
inline short int lua_tocast<short int>(lua_State* L, int index) {
	return static_cast<short int>(lua_tonumber(L, index));
}
template<>
inline int lua_tocast<int>(lua_State* L, int index) {
	return static_cast<int>(lua_tonumber(L, index));
}
template<>
inline long int lua_tocast<long int>(lua_State* L, int index) {
	return static_cast<long int>(lua_tointeger(L, index));
}
template<>
inline long long int lua_tocast<long long int>(lua_State* L, int index) {
	return lua_tointeger(L, index);
}
template<>
inline unsigned char lua_tocast<unsigned char>(lua_State* L, int index) {
	return static_cast<unsigned char>(lua_tonumber(L, index));
}
//template<>
//inline unsigned short int lua_tocast<unsigned short int>(lua_State* l, int index) {
//	return static_cast<unsigned short int>(lua_tonumber(l, index));
//}
template<>
inline unsigned int lua_tocast<unsigned int>(lua_State* L, int index) {
	return static_cast<unsigned int>(lua_tonumber(L, index));
}
template<>
inline unsigned long int lua_tocast<unsigned long int>(lua_State* L, int index) {
	return static_cast<unsigned long int>(lua_tointeger(L, index));
}
template<>
inline unsigned long long int lua_tocast<unsigned long long int>(lua_State* L, int index) {
	return lua_tointeger(L, index);
}
template<>
inline float lua_tocast<float>(lua_State* L, int index) {
	return static_cast<float>(lua_tonumber(L, index));
}
template<>
inline double lua_tocast<double>(lua_State* L, int index) {
	return static_cast<double>(lua_tonumber(L, index));
}
template<>
inline long double lua_tocast<long double>(lua_State* L, int index) {
	return static_cast<long double>(lua_tonumber(L, index));
}
template<>
inline const char* lua_tocast<const char*>(lua_State* L, int index) {
	return lua_tostring(L, index);
}
template<>
inline std::string lua_tocast<std::string>(lua_State* L, int index) {
	return std::string(lua_tostring(L, index));
}


// Pushes a generic value to the Lua stack.
template<typename T>
inline void lua_push(lua_State* L, T value) {
	lua_pushlightuserdata(L, value);
}
template<>
inline void lua_push<void*>(lua_State* L, void* value) {
	lua_pushlightuserdata(L, value);
}
template<>
inline void lua_push<bool>(lua_State* L, bool value) {
	lua_pushboolean(L, value);
}
template<>
inline void lua_push<char>(lua_State* L, char value) {
	lua_pushnumber(L, value);
}
template<>
inline void lua_push<char16_t>(lua_State* L, char16_t value) {
	lua_pushnumber(L, value);
}
//template<>
//inline void lua_tocast<char32_t>(lua_State* L, char32_t value) {
//	lua_pushnumber(L, value);
//}
template<>
inline void lua_push<wchar_t>(lua_State* L, wchar_t value) {
	lua_pushnumber(L, value);
}
template<>
inline void lua_push<signed char>(lua_State* L, signed char value) {
	lua_pushnumber(L, value);
}
template<>
inline void lua_push<short int>(lua_State* L, short int value) {
	lua_pushnumber(L, value);
}
template<>
inline void lua_push<int>(lua_State* L, int value) {
	lua_pushnumber(L, value);
}
template<>
inline void lua_push<long int>(lua_State* L, long int value) {
	lua_pushinteger(L, value);
}
template<>
inline void lua_push<long long int>(lua_State* L, long long int value) {
	lua_pushinteger(L, static_cast<lua_Integer>(value));
}
template<>
inline void lua_push<unsigned char>(lua_State* L, unsigned char value) {
	lua_pushnumber(L, value);
}
//template<>
//inline void lua_push<unsigned short int>(lua_State* l, unsigned short int value) {
//	lua_pushnumber(L, value);
//}
template<>
inline void lua_push<unsigned int>(lua_State* L, unsigned int value) {
	lua_pushnumber(L, value);
}
template<>
inline void lua_push<unsigned long int>(lua_State* L, unsigned long int value) {
	lua_pushinteger(L, value);
}
template<>
inline void lua_push<unsigned long long int>(lua_State* L, unsigned long long int value) {
	lua_pushinteger(L, static_cast<lua_Integer>(value));
}
template<>
inline void lua_push<float>(lua_State* L, float value) {
	lua_pushnumber(L, value);
}
template<>
inline void lua_push<double>(lua_State* L, double value) {
	lua_pushnumber(L, value);
}
template<>
inline void lua_push<long double>(lua_State* L, long double value) {
	lua_pushnumber(L, value);
}
template<>
inline void lua_push<char*>(lua_State* L, char* value) {
	lua_pushstring(L, value);
}
template<>
inline void lua_push<const char*>(lua_State* L, const char* value) {
	lua_pushstring(L, value);
}
template<>
inline void lua_push<const unsigned char*>(lua_State* L, const unsigned char* value) {
	lua_pushstring(L, reinterpret_cast<char*>(const_cast<unsigned char*>(value)));
}
template<>
inline void lua_push<std::string>(lua_State* L, std::string value) {
	lua_pushstring(L, value.c_str());
}

template<typename T>
inline int lua_pushn(lua_State* L, T v1) {
	lua_push(L, v1);
	return 1;
}
template<typename T, typename K>
inline int lua_pushn(lua_State* L, T v1, K v2) {
	lua_push(L, v1);
	lua_push(L, v2);
	return 2;
}
template<typename T, typename K, typename J>
inline int lua_pushn(lua_State* L, T v1, K v2, J v3) {
	lua_push(L, v1);
	lua_push(L, v2);
	lua_push(L, v3);
	return 3;
}
template<typename T, typename K, typename J, typename F>
inline int lua_pushn(lua_State* L, T v1, K v2, J v3, F v4) {
	lua_push(L, v1);
	lua_push(L, v2);
	lua_push(L, v3);
	lua_push(L, v4);
	return 4;
}
template<typename T, typename K, typename J, typename F, typename Y>
inline int lua_pushn(lua_State* L, T v1, K v2, J v3, F v4, Y v5) {
	lua_push(L, v1);
	lua_push(L, v2);
	lua_push(L, v3);
	lua_push(L, v4);
	lua_push(L, v5);
	return 5;
}

inline bool lua_setfuncref(lua_State* L, int t, int& ref, int index) {
	if (lua_isfunction(L, index)) {
		luaL_unref(L, LUA_REGISTRYINDEX, ref);
		ref = luaL_ref(L, LUA_REGISTRYINDEX);
		return true;
	}
	return false;
}

inline int lua_pushpcall(lua_State* L, int nresults) {
	return lua_pcall(L, 0, nresults, 0);
}
template<typename T>
inline int lua_pushpcall(lua_State* L, int nresults, T v1) {
	return lua_pcall(L, lua_pushn(L, v1), nresults, 0);
}
template<typename T, typename K>
inline int lua_pushpcall(lua_State* L, int nresults, T v1, K v2) {
	return lua_pcall(L, lua_pushn(L, v1, v2), nresults, 0);
}
template<typename T, typename K, typename J>
inline int lua_pushpcall(lua_State* L, int nresults, T v1, K v2, J v3) {
	return lua_pcall(L, lua_pushn(L, v1, v2, v3), nresults, 0);
}
template<typename T, typename K, typename J, typename F>
inline int lua_pushpcall(lua_State* L, int nresults, T v1, K v2, J v3, F v4) {
	return lua_pcall(L, lua_pushn(L, v1, v2, v3, v4), nresults, 0);
}
template<typename T, typename K, typename J, typename F, typename Y>
inline int lua_pushpcall(lua_State* L, int nresults, T v1, K v2, J v3, F v4, Y v5) {
	return lua_pcall(L, lua_pushn(L, v1, v2, v3, v4, v5), nresults, 0);
}



// Takes a generic type and gets the value from Lua
// and casts it to the right type. Accepts a default
// value for the returned value.
template<typename T>
inline T lua_tosafecast(lua_State* L, int index, T def) {
	return lua_isnil(L, index) == 0 && lua_isnumber(L, index) ? lua_tocast<T>(L, index) : def;
}
template<>
inline const char* lua_tosafecast<const char*>(lua_State* L, int index, const char* def) {
	return lua_isnil(L, index) == 0 && lua_isstring(L, index) ? lua_tocast<const char*>(L, index) : def;
}
template<>
inline std::string lua_tosafecast<std::string>(lua_State* L, int index, std::string def) {
	return lua_isnil(L, index) == 0 && lua_isstring(L, index) ? lua_tocast<std::string>(L, index) : def;
}
template<>
inline bool lua_tosafecast<bool>(lua_State* L, int index, bool def) {
	return lua_isnil(L, index) == 0 && lua_isboolean(L, index) ? lua_tocast<bool>(L, index) : def;
}

// Takes a generic type and get userdata from Lua and casts to that type.
template<typename T>
inline T* lua_touserdatacast(lua_State* L, int index) {
	return static_cast<T*>(lua_touserdata(L, index));
}

template<typename T>
inline T lua_toflieldcastnumber(lua_State* L, int index, const char* key) {
	lua_getfield(L, index, key);
	auto returnVal = static_cast<T>(lua_tonumber(L, lua_gettop(L)));
	lua_pop(L, 1);
	return returnVal;
}

//template<typename T>
//inline T lua_tofunction(lua_State* L, int index) {
//	return 
//}


// Alocate a new array of the given type and fill it
// with the data in a lua table at the given index.
template<typename T>
T* lua_tabletobasicarray(lua_State* L, int index) {
	auto n = luaL_getn(L, index);
	if (n > 0) {
		auto ret = new T[n];
		unsigned int i = 0;

		if (index < 0)
			index -= 1;

		lua_pushnil(L);
		while (lua_next(L, index) != 0) {
			ret[i] = lua_tocast<T>(L, -1);

			lua_pop(L, 1);
			++i;
		}
		return ret;
	}
	return NULL;
}

template<typename T, unsigned int size>
void lua_toarray(lua_State* L, int index, T* ref) {
	unsigned int i = 0;

	if (index < 0)
		index -= 1;

	lua_pushnil(L);
	while (lua_next(L, index) != 0) {
		ref[i] = lua_tosafecast<T>(L, -1, 0);

		lua_pop(L, 1);
		if (++i >= size) break;
	}
}

// Pushes a key, value pair onto the stack.
template<typename T, typename K>
void lua_pushtablekeyvalue(lua_State* L, T key, K value) {
	lua_push(L, key);
	lua_push(L, value);
	lua_settable(L, -3);
}

// Creates a new Lua table on the stack and fills it
// with the contents of pointer. Deletes it too if
// thats what you want.
template<typename T>
void lua_pusharray(lua_State* L, const T* pointer, unsigned int count, bool deleteArray = false) {
	lua_newtable(L);
	for (unsigned int i = 0; i < count; ++i)
		lua_pushtablekeyvalue(L, i + 1, pointer[i]);
	if (deleteArray) {
		delete [] pointer;
		pointer = NULL;
	}
}


// Creates a new Lua table on the stack and fills it
// with the contents of a stl container.
template<typename T>
void lua_pushlist(lua_State* L, const std::vector<T> container) {
	lua_newtable(L);
	for (unsigned int i = 0; i < container.size(); ++i)
		lua_pushtablekeyvalue(L, i + 1, container[i]);
}

template<typename T>
void lua_pushlist(lua_State* L, const std::list<T> container) {
	lua_newtable(L);
	
	int i = 1;
	for (auto iteratorA = container.begin(); iteratorA != container.end(); ++iteratorA) {
		lua_pushtablekeyvalue(L, i, *iteratorA);
		++i;
	}
}

int lua_callFunc(lua_State* L, const int index, const char* funcName, double arg = 0.0, double arg2 = 0.0, double arg3 = 0.0);
int lua_callFunc(lua_State* L, const char* modName, const char* funcName, double arg = 0.0, double arg2 = 0.0, double arg3 = 0.0);

void lua_pushnumbertoglobal(lua_State* L, const char* globalName, const char* key, double value);

void lua_pushenumuration(lua_State* L, const char* enumName, int value);

void* lua_tabletoglarray(lua_State* L, int index, unsigned int type);
void* lua_tabletoglarray(lua_State* L, int index, unsigned int type, ptrdiff_t& size);

unsigned int luaGLGetParamCount(unsigned int pname);

Vector3 lua_tovector3(lua_State* L, int index);
btVector3 lua_tobtvector3(lua_State* L, int index);

const char** lua_tabletolstringarray(lua_State* L, int index, int* lengths = nullptr);

#endif