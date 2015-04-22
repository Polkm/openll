#include "luaMatrix.h"

#include "olua.h"
#include "MatrixN.h"
#include "Vector3.h"

#include <map>
#include <vector>

using namespace olf::matrix;

static std::map<unsigned int, MatrixN> matrixMap;
static std::vector<unsigned int> emptySlots;
static unsigned int nextID = 0;

// Generates a new matrix.
// Takes (rows, collumns) Returns (matrixID)
static int gen(lua_State* L) {
	auto rows = lua_tosafecast<unsigned char>(L, 1, 4); 
	auto collumns = lua_tosafecast<unsigned char>(L, 2, 4); 

	// Find an empty slot to inject the new matrix
	unsigned int emptySlot = 0;
	if (!emptySlots.empty()) {
		emptySlot = emptySlots[emptySlots.size() - 1];
		emptySlots.pop_back();
	} else
		emptySlot = nextID++;

	// Create new matrix and add to the map
	matrixMap[emptySlot] = MatrixN(rows, collumns);

	// Return matrix ID to lua
	lua_pushnumber(L, emptySlot);
	return 1;
}

// Frees a matrix fom the database
// Takes (matrixID)
static int free(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);

	// Erase the matrix
	matrixMap.erase(matrixID);

	// Lower next ID or add to empty slots
	if (matrixID == nextID - 1)
		--nextID;
	else
		emptySlots.push_back(matrixID);

	return 0;
}

// Sets the matrix to a new value
// Takes (matrixID, newValues/otherMatrix)
static int set(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);

	if (lua_isnumber(L, 2)) {
		// Set to another matrix
		auto matrix2 = lua_tocast<unsigned char>(L, 2);
		matrixMap[matrixID].Set(matrixMap[matrix2]);
	} else if (lua_istable(L, 2)) {
		// Set to a table of values
		auto newValues = lua_tabletobasicarray<float>(L, 2);
		matrixMap[matrixID].Set(newValues);
	}
	return 0;
}

// Gets the values of the matrix
// Takes (matrixID) Returns (tableOfValues)
static int get(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);
	auto matrix = matrixMap[matrixID];

	lua_pusharray(L, matrix.Get(), matrix.GetSize());

	return 1;
}

// Sets the matrix to its identity
// Takes (matrixID)
static int identity(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);

	matrixMap[matrixID].Identity();

	return 0;
}

// Translates the matrix
// Takes (matrixID, trans)
static int translate(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);
	auto trans = lua_tovector3(L, 2);

	matrixMap[matrixID].Translate(trans);

	return 0;
}

// Rotates the matrix
// Takes (matrixID, angle, axis)
static int rotate(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);
	auto angle = lua_tocast<float>(L, 2);
	auto axis = lua_tovector3(L, 3);

	matrixMap[matrixID].Rotate(angle, axis);

	return 0;
}

// Scales the matrix by a vector
// Takes (matrixID, scaleVec)
static int scale(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);
	auto scaleVec = lua_tovector3(L, 2);

	matrixMap[matrixID].Scale(scaleVec);

	return 0;
}

// Sets the matrix to a perspective projection
// Takes (matrixID, fov, aspect, near, far)
static int perspective(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);
	auto fov = lua_tocast<float>(L, 2);
	auto aspect = lua_tocast<float>(L, 3);
	auto near = lua_tocast<float>(L, 4);
	auto far = lua_tocast<float>(L, 5);

	matrixMap[matrixID].Perspective(fov, aspect, near, far);

	return 0;
}

// Sets the matrix to look at a point
// Takes (matrixID, 
static int lookAt(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);
	auto eye = lua_tovector3(L, 2);
	auto focus = lua_tovector3(L, 3);
	auto up = lua_tovector3(L, 4);

	matrixMap[matrixID].LookAt(eye, focus, up);

	return 0;
}

static int getRow(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);
	auto rowIndex = lua_tocast<size_t>(L, 2);

	auto row = matrixMap[matrixID].GetRow(rowIndex);

	lua_pusharray(L, row.GetArray(), 3);
	return 3;
}

static int setRow(lua_State* L) {
	auto matrixID = lua_tocast<unsigned char>(L, 1);
	auto rowIndex = lua_tocast<size_t>(L, 2);
	auto row = lua_tovector3(L, 3);

	matrixMap[matrixID].SetRow(rowIndex, row);
	return 0;
}

int olf::matrix::registerLua(lua_State* L) {
	const luaL_reg localLib[] = {
		{"gen", gen},
		{"free", free},
		{"set", set},
		{"get", get},
		{"identity", identity},
		{"translate", translate},
		{"rotate", rotate},
		{"scale", scale},
		{"perspective", perspective},
		{"lookAt", lookAt},
		{"getRow", getRow},
		{"setRow", setRow},
		{NULL, NULL}
	};
	luaL_register(L, "matrix", localLib);

	return 1;
}