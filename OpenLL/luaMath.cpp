#include "luaMath.h"

#include "olua.h"

#include <math.h>
#include <vector>

using namespace olf::math;

static int randSeed = 547238892;
static double pi = 3.1415926535897932384626433832795028841971693993751058;

// Finds the factorial of a number
// WARNING: This shit can cause stack overflow like a bitch so keep value as a fairly low integer.
static int localFactorial(const int x) {
	if (x == 1)
		return x;
	return x * localFactorial(x - 1);
}
static int factorial(lua_State* L) {
	auto x = lua_tocast<int>(L, 1);
	lua_pushnumber(L, localFactorial(x));
	return 1;
}

// Gives you the log, with the specified base, of x
static int logx(lua_State* L) {
	auto base = lua_tocast<lua_Number>(L, 1);
	auto value = lua_tocast<lua_Number>(L, 2);
	lua_pushnumber(L, log(value) / log(base));
	return 1;
}

// Returns the nth root of x.
static int rootx(lua_State* L) {
	auto x = lua_tocast<lua_Number>(L, 1);
	auto root = lua_tocast<lua_Number>(L, 2);
	lua_pushnumber(L, pow(x, (1.0 / root)));
	return 1;
}

// Returns -1 if value is negative and 1 if positive, 0 if it is zero.
static int sign(lua_State* L) {
	auto value = lua_tocast<lua_Number>(L, 1);
	if (value > 0.0)
		lua_pushnumber(L, 1);
	else if (value < 0.0)
		lua_pushnumber(L, -1);
	else
		lua_pushnumber(L, 0);
	return 1;
}

// Returns true if the value is even.
static int even(lua_State* L) {
	auto value = lua_tocast<lua_Number>(L, 1);
	lua_pushboolean(L, fmod(value, 2.0) == 0.0);
	return 1;
}

// Rounds the value to the nearest whole number.
static int round(lua_State* L) {
	auto value = lua_tocast<lua_Number>(L, 1);
	lua_pushnumber(L, floor(value + 0.5));
	return 1;
}

// Rounds the value to the nearest base.
static int roundTo(lua_State* L) {
	auto value = lua_tocast<lua_Number>(L, 1);
	auto base = lua_tocast<lua_Number>(L, 2);
	lua_pushnumber(L, floor((value / base) + 0.5) * base);
	return 1;
}

// Clamps value between low and high.
static int clamp(lua_State* L) {
	auto value = lua_tocast<lua_Number>(L, 1);
	auto low = lua_tocast<lua_Number>(L, 2);
	auto high = lua_tocast<lua_Number>(L, 3);
	lua_pushnumber(L, value < low ? low : (value > high ? high : value));
	return 1;
}

// Wraps the value around the low and high parameters.
static int wrap(lua_State* L) {
	auto value = lua_tocast<lua_Number>(L, 1);
	auto low = lua_tocast<lua_Number>(L, 2);
	auto high = lua_tocast<lua_Number>(L, 3);
	auto dif = high - low;
	auto offSet = (value - low) / dif;
	lua_pushnumber(L, low + (dif * (offSet - floor(offSet))));
	return 1;
}

// Checks if vlaue is in the low and high range.
static int inRange(lua_State* L) {
	auto value = lua_tocast<lua_Number>(L, 1);
	auto low = lua_tocast<lua_Number>(L, 2);
	auto high = lua_tocast<lua_Number>(L, 3);
	lua_pushboolean(L, value <= high && value >= low);
	return 1;
}

// Linearly interpotates a to b by delta.
static int lerp(lua_State* L) {
	auto a = lua_tocast<lua_Number>(L, 1);
	auto b = lua_tocast<lua_Number>(L, 2);
	auto delta = lua_tocast<lua_Number>(L, 3);
	lua_pushnumber(L, a + (b - a) * delta);
	return 1;
}

// Cosineuraly interpotates a to b by delta.
static int coserp(lua_State* L) {
	auto a = lua_tonumber(L, 1);
	auto b = lua_tonumber(L, 2);
	auto delta = lua_tonumber(L, 3);
	auto f = (1.0 - cos(delta * pi)) * 0.5;
	lua_pushnumber(L, (a * (1.0 - f)) + (b * f));
	return 1;
}

// Cubicly interpolates between two points a and b
static int cuberp(lua_State* L) {
	auto a = lua_tonumber(L, 1);
	auto a1 = lua_tonumber(L, 2);
	auto b1 = lua_tonumber(L, 3);
	auto b = lua_tonumber(L, 4);
	auto delta = lua_tonumber(L, 5);

	double c0, c1, c2, c3, delta2;

	delta2 = delta * delta;
	c0 = b - b1 - a + a1;
	c1 = a - a1 - c0;
	c2 = b1 - a;
	c3 = a1;

	lua_pushnumber(L, c0 * delta * delta2 + c1 * delta2 + c2 * delta + c3);
	return 1;
}

// Hermitely interpolates from a to b.
static int hermiterp(lua_State* L) {
	auto a = lua_tonumber(L, 1);
	auto a1 = lua_tonumber(L, 2);
	auto b1 = lua_tonumber(L, 3);
	auto b = lua_tonumber(L, 4);
	auto delta = lua_tonumber(L, 5);
	auto tension = (1.0 - lua_tonumber(L, 6)) * 0.5;
	auto bias = lua_tonumber(L, 7);
	auto biasP = 1.0 + bias;
	auto biasN = 1.0 - bias;

	double m0, m1, delta2, delta3;
	double c0, c1, c2, c3;

	delta2 = delta * delta;
	delta3 = delta2 * delta;
	m0 = ((a1 - a) * biasP + (b1 - a1) * biasN) * tension;
	m1 = ((b1 - a1) * biasP + (b - b1) * biasN) * tension;
	c0 = 2.0 * delta3 - 3.0 * delta2 + 1.0;
	c1 = delta3 - 2.0 * delta2 + delta;
	c2 = delta3 - delta2;
	c3 = -2.0 * delta3 + 3.0 * delta2;

	lua_pushnumber(L, c0 * a1 + c1 * m0 + c2 * m1 + c3 * b1);
	return 1;
}

// Grows fast and then slowly decays.
static int impulse(lua_State* L) {
	auto x = lua_tonumber(L, 1);
	auto k = lua_tonumber(L, 2);

	const auto h = k * x;
	lua_pushnumber(L, h * exp(1.0 - h));
	return 1;
}

// Returns the value of an expressed polynomial using Horner's rule
// Coefficients are ordered from lowest to highest power
// ex. (6x^3 - 4x^2 + 7x - 19, x = 2) => math.poly(2, 6, -4, 7, -19)
static int poly(lua_State* L) {
	auto x = lua_tonumber(L, 1);
	auto top = lua_gettop(L);

    lua_Number val = 0.0;

    for (int i = top; i >= 2; --i) {
		auto coef = lua_tonumber(L, i);
        val = val * x + coef;
	}

	lua_pushnumber(L, val);
	return 1;
}

// Sets the random seed
static int randomseed(lua_State* L) {
	randSeed = lua_tocast<int>(L, 1);
	return 0;
}

static float nextRandom() {
    union {
        float dres;
        unsigned int ires;
    };

	randSeed *= 16807;

    ires = ((((unsigned int)randSeed) >> 9) | 0x3f800000);
    return dres - 1.0f;
}
// Standard random function.
static int random(lua_State* L) {
	if (lua_isnumber(L, 1) == 1) {
		auto first = lua_tocast<int>(L, 1);
		if (lua_isnumber(L, 2) == 1) {
			auto second = lua_tocast<int>(L, 2);
			lua_pushnumber(L, first + static_cast<int>(nextRandom() * static_cast<float>(second - first + 1)));
		} else {
			lua_pushnumber(L, 1 + static_cast<int>(nextRandom() * static_cast<float>(first)));
		}
	} else {
		lua_pushnumber(L, nextRandom());
	}
	return 1;
}

// Generates a random floating point number between a range.
static int randomf(lua_State* L) {
	if (lua_isnumber(L, 1) == 1) {
		auto first = lua_tocast<lua_Number>(L, 1);
		if (lua_isnumber(L, 2) == 1) {
			auto second = lua_tocast<lua_Number>(L, 2);
			lua_pushnumber(L, first + static_cast<lua_Number>(nextRandom()) * (second - first));
		} else {
			lua_pushnumber(L, 1 + static_cast<int>(nextRandom() * static_cast<float>(first - 1)));
		}
	} else {
		lua_pushnumber(L, nextRandom());
	}
	return 1;
}

static int prime(lua_State* L) {
	auto value = lua_tocast<int>(L, 1);

	if (value <= 1 || (value != 2 && value % 2 == 0)) {
		lua_pushboolean(L, false);
		return 1;
	}

	for (int i = 3; i < sqrt(static_cast<double>(value)); i += 2) {
		if (value % i == 0) {
			lua_pushboolean(L, false);
			return 1;
		}
	}

	lua_pushboolean(L, true);
	return 1;
}

int olf::math::registerLua(lua_State* L) {
	const luaL_reg localLib[] = {
		{"factorial", factorial},
		{"logx", logx},
		{"rootx", rootx},
		{"sign", sign},
		{"even", even},
		{"round", round},
		{"roundTo", roundTo},
		{"clamp", clamp},
		{"wrap", wrap},
		{"inRange", inRange},
		{"lerp", lerp},
		{"coserp", coserp},
		{"cuberp", cuberp},
		{"hermiterp", hermiterp},
		{"impulse", impulse},
		
		{"poly", poly},
		{"randomseed", randomseed},
		{"random", random},
		{"randomf", randomf},
		{NULL, NULL}
	};
	luaL_register(L, "math", localLib);

	lua_pushnumbertoglobal(L, "math", "e", 2.71828182845904523536028747135266249775724709369995);
	lua_pushnumbertoglobal(L, "math", "tau", pi * 2.0);
	lua_pushnumbertoglobal(L, "math", "halfPI", pi * 0.5);
	lua_pushnumbertoglobal(L, "math", "goldenRatio", 1.618033988749894848204586834365638117720309179);

	return 1;
}