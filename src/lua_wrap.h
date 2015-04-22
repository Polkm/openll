#ifndef __LUA_WRAP_H__
#define __LUA_WRAP_H__

#include<functional>


extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#define LOOP_0(B, A)
#define LOOP_1(B, A) B(1) T A(1)
#define LOOP_2(B, A) LOOP_1(B, A), B(2) K A(2)
#define LOOP_3(B, A) LOOP_2(B, A), B(3) J A(3)
#define LOOP_4(B, A) LOOP_3(B, A), B(4) F A(4)
#define LOOP_5(B, A) LOOP_4(B, A), B(5) Y A(5)
#define LOOP_6(B, A) LOOP_5(B, A), B(6) H A(6)
#define LOOP_7(B, A) LOOP_6(B, A), B(7) M A(7)
#define LOOP_8(B, A) LOOP_7(B, A), B(8) X A(8)
#define LOOP_9(B, A) LOOP_8(B, A), B(9) Q A(9)
#define LOOP_10(B, A) LOOP_9(B, A), B(10) U A(10)

#define EMPTY(n)

#define TEMPLATE_B(n) typename
#define TEMPLATE(n) LOOP_##n(TEMPLATE_B, EMPTY)

#define HEADER(n) LOOP_##n(EMPTY, EMPTY)

#define CAST_B(n) lua_tocast<
#define CAST_A(n) >(L, ##n)
#define CAST(n) LOOP_##n(CAST_B, CAST_A)

#define CALL_0(n) { func(CAST(n)); return 0; }
#define CALL_1(n) { lua_push(L, func(CAST(n))); return 1; }

#define WRAP_ALL(n) \
template<typename R, TEMPLATE(n)> int lua_wrapfunction(lua_State* L, R func(HEADER(n))) CALL_1(n) \
template<typename R, TEMPLATE(n)> int lua_wrapfunction(lua_State* L, R (_stdcall*func)(HEADER(n))) CALL_1(n) \
template<TEMPLATE(n)> int lua_wrapfunction(lua_State* L, void func(HEADER(n))) CALL_0(n) \
template<TEMPLATE(n)> int lua_wrapfunction(lua_State* L, void (_stdcall*func)(HEADER(n))) CALL_0(n) \

template<typename R> int lua_wrapfunction(lua_State* L, R func()) { lua_push(L, func()); return 1; }
template<typename R> int lua_wrapfunction(lua_State* L, R (_stdcall*func)()) { lua_push(L, func()); return 1; }
template<> inline int lua_wrapfunction(lua_State* L, void func()) { func(); return 0; }
template<> inline int lua_wrapfunction(lua_State* L, void (_stdcall*func)()) { func(); return 0; }
WRAP_ALL(1)
WRAP_ALL(2)
WRAP_ALL(3)
WRAP_ALL(4)
WRAP_ALL(5)
WRAP_ALL(6)
WRAP_ALL(7)
WRAP_ALL(8)
WRAP_ALL(9)
WRAP_ALL(10)

#define LUA_FULL_WRAP(F) [](lua_State* L) -> int { return lua_wrapfunction(L, F); }
#define LUA_FULL_WRAP_GET(F) [](lua_State* L) -> int { return lua_wrapgetfunction(L, F); }
#define LUA_FULL_WRAP_ARRAY(F) [](lua_State* L) -> int { return lua_wraparrayfunction(L, F); }

template<typename T, typename K>
int lua_wrapreffunction(lua_State* L, void func(T, K*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	K ref = 0;
	func(arg1, &ref);
	lua_push(L, ref);
	return 1;
}
template<typename T, typename K, typename J>
int lua_wrapreffunction(lua_State* L, void func(T, K, J*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	auto arg2 = lua_tocast<K>(L, 2);
	J ref = 0;
	func(arg1, arg2, &ref);
	lua_push(L, ref);
	return 1;
}


template<typename T>
int lua_wrapgenfunction(lua_State* L, void func(int, T*)) {
	auto n = lua_tosafecast<int>(L, 1, 1);
	T newObj;
	for (int i = 0; i < n; ++i) {
		func(1, &newObj);
		lua_push(L, newObj);
	}
	return n;
}
template<typename T>
int lua_wrapgenfunction(lua_State* L, void (_stdcall*func)(int, T*)) {
	auto n = lua_tosafecast<int>(L, 1, 1);
	T newObj;
	for (int i = 0; i < n; ++i) {
		func(1, &newObj);
		lua_push(L, newObj);
	}
	return n;
}


template<typename T>
int lua_wraploopfunction(lua_State* L, void func(int, T*)) {
	for (int i = 1; i <= lua_gettop(L); ++i) {
		auto id = lua_tocast<T>(L, i);
		func(1, &id);
	}
	return 0;
}
template<typename T>
int lua_wraploopfunction(lua_State* L, void (_stdcall*func)(int, T*)) {
	for (int i = 1; i <= lua_gettop(L); ++i) {
		auto id = lua_tocast<T>(L, i);
		func(1, &id);
	}
	return 0;
}


template<typename T, typename K>
int lua_wraparrayfunction(lua_State* L, void func(T, const K*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	auto arg2 = lua_tabletobasicarray<K>(L, 2);
	func(arg1, arg2);
	delete [] arg2;
	return 0;
}
template<typename T, typename K>
int lua_wraparrayfunction(lua_State* L, void (_stdcall*func)(T, const K*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	auto arg2 = lua_tabletobasicarray<K>(L, 2);
	func(arg1, arg2);
	delete [] arg2;
	return 0;
}
template<typename T, typename K, typename J>
int lua_wraparrayfunction(lua_State* L, void func(T, K, const J*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	auto arg2 = lua_tocast<K>(L, 2);
	auto arg3 = lua_tabletobasicarray<J>(L, 3);
	func(arg1, arg2, arg3);
	delete [] arg3;
	return 0;
}
template<typename T, typename K, typename J>
int lua_wraparrayfunction(lua_State* L, void (_stdcall*func)(T, K, const J*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	auto arg2 = lua_tocast<K>(L, 2);
	auto arg3 = lua_tabletobasicarray<J>(L, 3);
	func(arg1, arg2, arg3);
	delete [] arg3;
	return 0;
}
template<typename T, typename K, typename J, typename F>
int lua_wraparrayfunction(lua_State* L, void (_stdcall*func)(T, K, J, const F*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	auto arg2 = lua_tocast<K>(L, 2);
	auto arg3 = lua_tocast<J>(L, 3);
	auto arg4 = lua_tabletobasicarray<F>(L, 4);
	func(arg1, arg2, arg3, arg4);
	delete [] arg4;
	return 0;
}


template<typename T, typename K>
int lua_wrapgetfunction(lua_State* L, void (_stdcall*func)(T, K*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	auto count = lua_tosafecast<unsigned int>(L, 2, 1);
	if (count > 1) {
		auto params = new K[count];
		func(arg1, params);
		lua_pusharray(L, params, count, true);
	} else {
		K returnVal;
		func(arg1, &returnVal);
		lua_push(L, returnVal);
	}
	return 1;
}
template<typename T, typename K, typename J>
int lua_wrapgetfunction(lua_State* L, void (_stdcall*func)(T, K, J*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	auto arg2 = lua_tocast<K>(L, 2);
	auto count = lua_tosafecast<unsigned int>(L, 3, 1);
	if (count > 1) {
		auto params = new J[count];
		func(arg1, arg2, params);
		lua_pusharray(L, params, count, true);
	} else {
		J returnVal;
		func(arg1, arg2, &returnVal);
		lua_push(L, returnVal);
	}
	return 1;
}
template<typename T, typename K, typename J, typename F>
int lua_wrapgetfunction(lua_State* L, void (_stdcall*func)(T, K, J, F*)) {
	auto arg1 = lua_tocast<T>(L, 1);
	auto arg2 = lua_tocast<K>(L, 2);
	auto arg3 = lua_tocast<J>(L, 3);
	auto count = lua_tosafecast<unsigned int>(L, 4, 1);
	if (count > 1) {
		auto params = new F[count];
		func(arg1, arg2, arg3, params);
		lua_pusharray(L, params, count, true);
	} else {
		F returnVal;
		func(arg1, arg2, arg3, &returnVal);
		lua_push(L, returnVal);
	}
	return 1;
}

#endif