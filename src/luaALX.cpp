#include "luaALX.h"

#include <al.h>
#include <alc.h>
#include "olua.h"

#include "luaALC.h"

#include <iostream>

using namespace olf::alx;

// Creates and sets the default context, with optional device name and attributes.
// Returns what alcMakeContextCurrent returns.
static int defaultContext(lua_State* L) {
	auto devicename = lua_isnil(L, 1) ? NULL : lua_tocast<const ALCchar*>(L, 1);
	auto attrlist = lua_istable(L, 2) ? lua_tabletobasicarray<ALCint>(L, 2) :  NULL;
	lua_push(L, alcMakeContextCurrent(alcCreateContext(alcOpenDevice(devicename), attrlist)));
	return 1;
}

// Destroys the current context.
static int destroyContext(lua_State* L) {
	auto context = alcGetCurrentContext();
	auto device = alcGetContextsDevice(context);
	alcDestroyContext(context);
	alcCloseDevice(device);
	return 0;
}

// Creates a new source from a given buffer.
static int genSource(lua_State* L) {
	auto buffer = lua_tosafecast<ALuint>(L, 1, 0);

	ALuint source;
	alGenSources(1, &source);

	alSourcei(source, AL_BUFFER, buffer);
	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1.0f);
	alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSourcei(source, AL_LOOPING, AL_FALSE);

	lua_push(L, source);
	return 1;
}

// Returns the proper enum for the given bits and channels.
static int getFormat(lua_State* L) {
	auto bitsPerSample = lua_tosafecast<int>(L, 1, 16);
	auto channels = lua_tosafecast<int>(L, 2, 2);
	if (bitsPerSample == 8) {
		if (channels == 1) {
			lua_push(L, AL_FORMAT_MONO8);
		} else if (channels == 2) {
			lua_push(L, AL_FORMAT_STEREO8);
		}
	} else if (bitsPerSample == 16) {
		if (channels == 1) {
			lua_push(L, AL_FORMAT_MONO16);
		} else if (channels == 2) {
			lua_push(L, AL_FORMAT_STEREO16);
		}
	}
	return 1;
}

// Sets listener attributes all at once.
static const ALfloat defaultOrientation[] = {0.0f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f};
static int listener(lua_State* L) {
	alListener3f(AL_POSITION, lua_tosafecast<ALfloat>(L, 1, 0), lua_tosafecast<ALfloat>(L, 2, 0), lua_tosafecast<ALfloat>(L, 3, 0));
	alListener3f(AL_VELOCITY, lua_tosafecast<ALfloat>(L, 4, 0), lua_tosafecast<ALfloat>(L, 5, 0), lua_tosafecast<ALfloat>(L, 6, 0));
	alListenerfv(AL_ORIENTATION, lua_istable(L, 7) ? lua_tabletobasicarray<ALfloat>(L, 7) : defaultOrientation);
	return 0;
}

int olf::alx::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{"defaultContext", defaultContext},
		{"destroyContext", destroyContext},
		{"genSource", genSource},
		{"getFormat", getFormat},
		{"listener", listener},
		{NULL, NULL}
	};
	luaL_openlib(L, "alx", localLib, 0);

	return 1;
}

