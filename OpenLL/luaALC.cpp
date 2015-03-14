#include "luaALC.h"

#include <al.h>
#include <alc.h>
#include "olua.h"

using namespace olf::alc;

static int createContext(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	auto attrlist = lua_istable(L, 2) ? lua_tabletobasicarray<ALCint>(L, 2) :  NULL;
	lua_pushlightuserdata(L, alcCreateContext(device, attrlist));

	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
	alListenerfv(AL_ORIENTATION, ListenerOri);

	return 1;
}

static int makeContextCurrent(lua_State* L) {
	auto context = lua_touserdatacast<ALCcontext>(L, 1);
	lua_push(L, alcMakeContextCurrent(context));
	return 1;
}

static int processContext(lua_State* L) {
	auto context = lua_touserdatacast<ALCcontext>(L, 1);
	alcProcessContext(context);
	return 0;
}

static int suspendContext(lua_State* L) {
	auto context = lua_touserdatacast<ALCcontext>(L, 1);
	alcSuspendContext(context);
	return 0;
}

static int destroyContext(lua_State* L) {
	auto context = lua_touserdatacast<ALCcontext>(L, 1);
	alcDestroyContext(context);
	return 0;
}

static int getCurrentContext(lua_State* L) {
	lua_pushlightuserdata(L, alcGetCurrentContext());
	return 1;
}

static int getContextsDevice(lua_State* L) {
	auto context = lua_touserdatacast<ALCcontext>(L, 1);
	lua_pushlightuserdata(L, alcGetContextsDevice(context));
	return 1;
}

static int getError(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	lua_push(L, alcGetError(device));
	return 1;
}


static int openDevice(lua_State* L) {
	auto devicename = lua_isnil(L, 1) ? NULL : lua_tocast<const ALCchar*>(L, 1);
	lua_pushlightuserdata(L, alcOpenDevice(devicename));
	return 1;
}

static int closeDevice(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	lua_push(L, alcCloseDevice(device));
	return 1;
}


static int isExtensionPresent(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	auto extName = lua_tocast<const ALCchar*>(L, 2);
	lua_push(L, alcIsExtensionPresent(device, extName));
	return 1;
}

static int getEnumValue(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	auto enumName = lua_tocast<const ALCchar*>(L, 2);
	lua_push(L, alcGetEnumValue(device, enumName));
	return 1;
}


static int getString(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	auto param = lua_tocast<ALCenum>(L, 2);
	lua_push(L, alcGetString(device, param));
	return 1;
}

static int getIntegerv(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	auto param = lua_tocast<ALCenum>(L, 2);
	auto size = lua_tocast<ALCsizei>(L, 3);
	auto data = new ALCint[size];
	alcGetIntegerv(device, param, size, data);
	lua_pusharray(L, data, size, true);
	return 1;
}


static int captureOpenDevice(lua_State* L) {
	auto devicename = lua_tocast<const ALCchar*>(L, 1);
	auto frequency = lua_tocast<ALCuint>(L, 2);
	auto format = lua_tocast<ALCenum>(L, 3);
	auto buffersize = lua_tocast<ALCsizei>(L, 4);
	lua_pushlightuserdata(L, alcCaptureOpenDevice(devicename, frequency, format, buffersize));
	return 0;
}

static int captureCloseDevice(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	lua_push(L, alcCaptureCloseDevice(device));
	return 1;
}

static int captureStart(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	alcCaptureStart(device);
	return 0;
}

static int captureStop(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	alcCaptureStop(device);
	return 0;
}

static int captureSamples(lua_State* L) {
	auto device = lua_touserdatacast<ALCdevice>(L, 1);
	auto samples = lua_tocast<ALCsizei>(L, 2);
	auto buffer = new ALCuint[samples];
	alcCaptureSamples(device, buffer, samples);
	lua_pusharray(L, buffer, samples, true);
	return 1;
}

int olf::alc::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{"createContext", createContext},
		{"makeContextCurrent", makeContextCurrent},
		{"processContext", processContext},
		{"suspendContext", suspendContext},
		{"destroyContext", destroyContext},
		{"getCurrentContext", getCurrentContext},
		{"getContextsDevice", getContextsDevice},

		{"getError", getError},

		{"openDevice", openDevice},
		{"closeDevice", closeDevice},

		{"isExtensionPresent", isExtensionPresent},
		{"getEnumValue", getEnumValue},

		{"getString", getString},
		{"getIntegerv", getIntegerv},

		{"captureOpenDevice", captureOpenDevice},
		{"captureCloseDevice", captureCloseDevice},
		{"captureStart", captureStart},
		{"captureStop", captureStop},
		{"captureSamples", captureSamples},
		{NULL, NULL}
	};
	luaL_openlib(L, "alc", localLib, 0);

	return 1;
}