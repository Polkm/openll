#include "luaGLM.h"

#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "olua.h"

#define GLM_WRAP1(F) [](lua_State* L) -> int { return lua_pushn(L, F(lua_tocast<lua_Number>(L, 1))); }
#define GLM_WRAP2(F) [](lua_State* L) -> int { return lua_pushn(L, F(lua_tocast<lua_Number>(L, 1), lua_tocast<lua_Number>(L, 2))); }
#define GLM_WRAP3(F) [](lua_State* L) -> int { return lua_pushn(L, F(lua_tocast<lua_Number>(L, 1), lua_tocast<lua_Number>(L, 2), lua_tocast<lua_Number>(L, 3))); }

using namespace olf::glmw;

static glm::mat4 getMatrix(lua_State* L, int index) {
	float flts[16];
	lua_toarray<float, 16>(L, index, flts);
	return glm::make_mat4(flts);
}

static glm::vec2 getVector2(lua_State* L, int index) {
	float flts[2];
	lua_toarray<float, 2>(L, index, flts);
	return glm::make_vec2(flts);
}

static glm::vec3 getVector3(lua_State* L, int index) {
	float flts[3];
	lua_toarray<float, 3>(L, index, flts);
	return glm::make_vec3(flts);
}

static glm::vec4 getVector4(lua_State* L, int index) {
	float flts[4];
	lua_toarray<float, 4>(L, index, flts);
	return glm::make_vec4(flts);
}

static float pullF(lua_State* L, int index) {
	return lua_tosafecast<float>(L, index, 0.0f);
}

static int pushMatrix(lua_State* L, glm::mat4 m) {
	lua_pusharray(L, glm::value_ptr(m), 16);
	return 1;
}

static int pushVector3(lua_State* L, glm::vec3 v) {
	lua_pusharray(L, glm::value_ptr(v), 3);
	return 1;
}

static int vec2(lua_State* L) {
	auto x = lua_tosafecast<float>(L, 1, 0);
	auto y = lua_tosafecast<float>(L, 2, 0);
	glm::vec2 vec(x, y);
	lua_pusharray(L, glm::value_ptr(vec), 2);
	return 1;
}

static int mat4(lua_State* L) {
	auto identity = lua_tosafecast<float>(L, 1, 1.0f);
	glm::mat4 m(identity);
	lua_pusharray(L, glm::value_ptr(m), 16);
	return 1;
}

static int frustum(lua_State* L) {
	return pushMatrix(L, glm::frustum(pullF(L, 1), pullF(L, 2), pullF(L, 3), pullF(L, 4), pullF(L, 5), pullF(L, 6)));
}

static int infinitePerspective(lua_State* L) {
	return pushMatrix(L, glm::infinitePerspective(pullF(L, 1), pullF(L, 2), pullF(L, 3)));
}

static int lookAt(lua_State* L) {
	return pushMatrix(L, glm::lookAt(getVector3(L, 1), getVector3(L, 2), getVector3(L, 3)));
}

static int ortho(lua_State* L) {
	if (lua_isnil(L, 5) || lua_isnil(L, 6)) {
		return pushMatrix(L, glm::ortho(pullF(L, 1), pullF(L, 2), pullF(L, 3), pullF(L, 4)));
	} else {
		return pushMatrix(L, glm::ortho(pullF(L, 1), pullF(L, 2), pullF(L, 3), pullF(L, 4), pullF(L, 5), pullF(L, 6)));
	}
}

static int perspective(lua_State* L) {
	return pushMatrix(L, glm::perspective(pullF(L, 1), pullF(L, 2), pullF(L, 3), pullF(L, 4)));
}

static int perspectiveFov(lua_State* L) {
	return pushMatrix(L, glm::perspectiveFov(pullF(L, 1), pullF(L, 2), pullF(L, 3), pullF(L, 4), pullF(L, 5)));
}

static int pickMatrix(lua_State* L) {
	return pushMatrix(L, glm::pickMatrix(getVector2(L, 1), getVector2(L, 2), getVector4(L, 3)));
}

static int project(lua_State* L) {
	return pushVector3(L, glm::project(getVector3(L, 1), getMatrix(L, 2), getMatrix(L, 3), getVector4(L, 4)));
}

static int rotate(lua_State* L) {
	return pushMatrix(L, glm::rotate(getMatrix(L, 1), lua_tosafecast<float>(L, 2, 0.0f), getVector3(L, 3)));
}

static int scale(lua_State* L) {
	return pushMatrix(L, glm::scale(getMatrix(L, 1), getVector3(L, 2)));
}

static int translate(lua_State* L) {
	return pushMatrix(L, glm::translate(getMatrix(L, 1), getVector3(L, 2)));
}

static int tweakedInfinitePerspective(lua_State* L) {
	return pushMatrix(L, glm::tweakedInfinitePerspective(pullF(L, 1), pullF(L, 2), pullF(L, 3)));
}

static int unProject(lua_State* L) {
	return pushVector3(L, glm::unProject(getVector3(L, 1), getMatrix(L, 2), getMatrix(L, 3), getVector4(L, 4)));
}

int olf::glmw::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{"vec2", vec2},
		{"mat4", mat4},

		{"frustum", frustum},
		{"infinitePerspective", infinitePerspective},
		{"lookAt", lookAt},
		{"ortho", ortho},
		{"perspective", perspective},
		{"perspectiveFov", perspectiveFov},
		{"pickMatrix", pickMatrix},
		{"project", project},
		{"rotate", rotate},
		{"scale", scale},
		{"translate", translate},
		{"tweakedInfinitePerspective", tweakedInfinitePerspective},
		{"unProject", unProject},

		{"abs", GLM_WRAP1(glm::abs)},
		{"ceil", GLM_WRAP1(glm::ceil)},
		{"clamp", GLM_WRAP3(glm::clamp)},
		{"floor", GLM_WRAP1(glm::floor)},
		{NULL, NULL}
	};
	luaL_openlib(L, "glm", localLib, 0);

	return 1;
}
