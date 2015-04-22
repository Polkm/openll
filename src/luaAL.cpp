#include "luaAL.h"

#include <al.h>
#include <alc.h>
#include <iostream>
#include "olua.h"

using namespace olf::al;

static int genBuffers(lua_State* L) {
	return lua_wrapgenfunction(L, alGenBuffers);
}

static int deleteBuffers(lua_State* L) {
	return lua_wraploopfunction(L, alDeleteBuffers);
}

static int isBuffer(lua_State* L) {
	return lua_wrapfunction(L, alIsBuffer);
}

static int bufferData(lua_State* L) {
	auto buffer = lua_tocast<ALuint>(L, 1);
	auto format = lua_tocast<ALenum>(L, 2);
	auto data = lua_tabletobasicarray<unsigned char>(L, 3);
	auto size = lua_tocast<ALsizei>(L, 4);
	auto freq = lua_tocast<ALsizei>(L, 5);
	alBufferData(buffer, format, data, size, freq);
	delete [] data;
	return 0;
}

static int bufferf(lua_State* L) {
	return lua_wrapfunction(L, alBufferf);
}
static int buffer3f(lua_State* L) {
	return lua_wrapfunction(L, alBuffer3f);
}
static int bufferfv(lua_State* L) {
	return lua_wraparrayfunction(L, alBufferfv);
}
static int bufferi(lua_State* L) {
	return lua_wrapfunction(L, alBufferi);
}
static int buffer3i(lua_State* L) {
	return lua_wrapfunction(L, alBuffer3i);
}
static int bufferiv(lua_State* L) {
	return lua_wraparrayfunction(L, alBufferiv);
}

static int getBufferf(lua_State* L) {
	return lua_wrapreffunction(L, alGetBufferf);
}
static int getBuffer3f(lua_State* L) {
	auto buffer = lua_tocast<ALuint>(L, 1);
	auto param = lua_tocast<ALenum>(L, 2);
	ALfloat v1, v2, v3;
	alGetBuffer3f(buffer, param, &v1, &v2, &v3);
	lua_push(L, v1);
	lua_push(L, v2);
	lua_push(L, v3);
	return 3;
}
static int getBufferfv(lua_State* L) {
	auto buffer = lua_tocast<ALuint>(L, 1);
	auto param = lua_tocast<ALenum>(L, 2);
	ALfloat values[3];
	alGetBufferfv(buffer, param, values);
	lua_pusharray(L, values, 3);
	return 1;
}
static int getBufferi(lua_State* L) {
	return lua_wrapreffunction(L, alGetBufferi);
}
static int getBuffer3i(lua_State* L) {
	auto buffer = lua_tocast<ALuint>(L, 1);
	auto param = lua_tocast<ALenum>(L, 2);
	ALint v1, v2, v3;
	alGetBuffer3i(buffer, param, &v1, &v2, &v3);
	lua_push(L, v1);
	lua_push(L, v2);
	lua_push(L, v3);
	return 3;
}
static int getBufferiv(lua_State* L) {
	auto buffer = lua_tocast<ALuint>(L, 1);
	auto param = lua_tocast<ALenum>(L, 2);
	ALint values[3];
	alGetBufferiv(buffer, param, values);
	lua_pusharray(L, values, 3);
	return 1;
}


static int genSources(lua_State* L) {
	return lua_wrapgenfunction(L, alGenSources);
}

static int deleteSources(lua_State* L) {
	return lua_wraploopfunction(L, alDeleteSources);
}

static int isSource(lua_State* L) {
	return lua_wrapfunction(L, alIsSource);
}

static int sourcef(lua_State* L) {
	return lua_wrapfunction(L, alSourcef);
}
static int source3f(lua_State* L) {
	return lua_wrapfunction(L, alSource3f);
}
static int sourcefv(lua_State* L) {
	return lua_wraparrayfunction(L, alSourcefv);
}
static int sourcei(lua_State* L) {
	return lua_wrapfunction(L, alSourcei);
}
static int source3i(lua_State* L) {
	return lua_wrapfunction(L, alSource3i);
}
static int sourceiv(lua_State* L) {
	return lua_wraparrayfunction(L, alSourceiv);
}

static int getSourcef(lua_State* L) {
	return lua_wrapreffunction(L, alGetSourcef);
}
static int getSource3f(lua_State* L) {
	auto source = lua_tocast<ALuint>(L, 1);
	auto param = lua_tocast<ALenum>(L, 2);
	ALfloat v1, v2, v3;
	alGetSource3f(source, param, &v1, &v2, &v3);
	lua_push(L, v1);
	lua_push(L, v2);
	lua_push(L, v3);
	return 3;
}
static int getSourcefv(lua_State* L) {
	auto source = lua_tocast<ALuint>(L, 1);
	auto param = lua_tocast<ALenum>(L, 2);
	ALfloat values[3];
	alGetSourcefv(source, param, values);
	lua_pusharray(L, values, 3);
	return 1;
}
static int getSourcei(lua_State* L) {
	return lua_wrapreffunction(L, alGetSourcei);
}
static int getSource3i(lua_State* L) {
	auto source = lua_tocast<ALuint>(L, 1);
	auto param = lua_tocast<ALenum>(L, 2);
	ALint v1, v2, v3;
	alGetSource3i(source, param, &v1, &v2, &v3);
	lua_push(L, v1);
	lua_push(L, v2);
	lua_push(L, v3);
	return 3;
}
static int getSourceiv(lua_State* L) {
	auto source = lua_tocast<ALuint>(L, 1);
	auto param = lua_tocast<ALenum>(L, 2);
	ALint values[3];
	alGetSourceiv(source, param, values);
	lua_pusharray(L, values, 3);
	return 1;
}

static int sourcePlay(lua_State* L) {
	return lua_wrapfunction(L, alSourcePlay);
}
static int sourcePlayv(lua_State* L) {
	auto n = lua_tocast<ALsizei>(L, 1);
	auto sources = lua_tabletobasicarray<ALuint>(L, 2);
	alSourcePlayv(n, sources);
	return 0;
}

static int sourcePause(lua_State* L) {
	return lua_wrapfunction(L, alSourcePause);
}
static int sourcePausev(lua_State* L) {
	auto n = lua_tocast<ALsizei>(L, 1);
	auto sources = lua_tabletobasicarray<ALuint>(L, 2);
	alSourcePausev(n, sources);
	return 0;
}

static int sourceStop(lua_State* L) {
	return lua_wrapfunction(L, alSourceStop);
}
static int sourceStopv(lua_State* L) {
	auto n = lua_tocast<ALsizei>(L, 1);
	auto sources = lua_tabletobasicarray<ALuint>(L, 2);
	alSourceStopv(n, sources);
	return 0;
}

static int sourceRewind(lua_State* L) {
	return lua_wrapfunction(L, alSourceRewind);
}
static int sourceRewindv(lua_State* L) {
	auto n = lua_tocast<ALsizei>(L, 1);
	auto sources = lua_tabletobasicarray<ALuint>(L, 2);
	alSourceRewindv(n, sources);
	return 0;
}

static int sourceQueueBuffers(lua_State* L) {
	auto source = lua_tocast<ALuint>(L, 1);
	auto n = lua_tocast<ALsizei>(L, 1);
	auto buffers = lua_tabletobasicarray<ALuint>(L, 2);
	alSourceQueueBuffers(source, n, buffers);
	return 0;
}

static int sourceUnqueueBuffers(lua_State* L) {
	auto source = lua_tocast<ALuint>(L, 1);
	auto n = lua_tocast<ALsizei>(L, 1);
	auto buffers = lua_tabletobasicarray<ALuint>(L, 2);
	alSourceUnqueueBuffers(source, n, buffers);
	return 0;
}


static int listenerf(lua_State* L) {
	return lua_wrapfunction(L, alListenerf);
}
static int listener3f(lua_State* L) {
	return lua_wrapfunction(L, alListener3f);
}
static int listenerfv(lua_State* L) {
	return lua_wraparrayfunction(L, alListenerfv);
}
static int listeneri(lua_State* L) {
	return lua_wrapfunction(L, alListeneri);
}
static int listener3i(lua_State* L) {
	return lua_wrapfunction(L, alListener3i);
}
static int listeneriv(lua_State* L) {
	return lua_wraparrayfunction(L, alListeneriv);
}

static int getListenerf(lua_State* L) {
	return lua_wrapreffunction(L, alGetListenerf);
}
static int getListener3f(lua_State* L) {
	auto param = lua_tocast<ALenum>(L, 1);
	ALfloat v1, v2, v3;
	alGetListener3f(param, &v1, &v2, &v3);
	lua_push(L, v1);
	lua_push(L, v2);
	lua_push(L, v3);
	return 3;
}
static int getListenerfv(lua_State* L) {
	auto param = lua_tocast<ALenum>(L, 1);
	ALfloat values[3];
	alGetListenerfv(param, values);
	lua_pusharray(L, values, 3);
	return 1;
}
static int getListeneri(lua_State* L) {
	return lua_wrapreffunction(L, alGetListeneri);
}
static int getListener3i(lua_State* L) {
	auto param = lua_tocast<ALenum>(L, 1);
	ALint v1, v2, v3;
	alGetListener3i(param, &v1, &v2, &v3);
	lua_push(L, v1);
	lua_push(L, v2);
	lua_push(L, v3);
	return 3;
}
static int getListeneriv(lua_State* L) {
	auto param = lua_tocast<ALenum>(L, 1);
	ALint values[3];
	alGetListeneriv(param, values);
	lua_pusharray(L, values, 3);
	return 1;
}


static int enable(lua_State* L) {
	return lua_wrapfunction(L, alEnable);
}

static int disable(lua_State* L) {
	return lua_wrapfunction(L, alDisable);
}

static int isEnabled(lua_State* L) {
	return lua_wrapfunction(L, alIsEnabled);
}

static int getBoolean(lua_State* L) {
	return lua_wrapfunction(L, alGetBoolean);
}
static int getDouble(lua_State* L) {
	return lua_wrapfunction(L, alGetDouble);
}
static int getFloat(lua_State* L) {
	return lua_wrapfunction(L, alGetFloat);
}
static int getInteger(lua_State* L) {
	return lua_wrapfunction(L, alGetInteger);
}

static int getBooleanv(lua_State* L) {
	return lua_wrapreffunction(L, alGetBooleanv);
}
static int getDoublev(lua_State* L) {
	return lua_wrapreffunction(L, alGetDoublev);
}
static int getFloatv(lua_State* L) {
	return lua_wrapreffunction(L, alGetFloatv);
}
static int getIntegerv(lua_State* L) {
	return lua_wrapreffunction(L, alGetIntegerv);
}

static int getString(lua_State* L) {
	return lua_wrapfunction(L, alGetString);
}

static int distanceModel(lua_State* L) {
	return lua_wrapfunction(L, alDistanceModel);
}

static int dopplerFactor(lua_State* L) {
	return lua_wrapfunction(L, alDopplerFactor);
}

static int speedOfSound(lua_State* L) {
	return lua_wrapfunction(L, alSpeedOfSound);
}


static int getError(lua_State* L) {
	return lua_wrapfunction(L, alGetError);
}


static int isExtensionPresent(lua_State* L) {
	return lua_wrapfunction(L, alIsExtensionPresent);
}

static int getEnumValue(lua_State* L) {
	return lua_wrapfunction(L, alGetEnumValue);
}

int olf::al::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{"deleteBuffers", deleteBuffers},
		{"isBuffer", isBuffer},
		{"bufferData", bufferData},
		{"bufferf", bufferf},
		{"buffer3f", buffer3f},
		{"bufferfv", bufferfv},
		{"bufferi", bufferi},
		{"buffer3i", buffer3i},
		{"bufferiv", bufferiv},
		{"getBufferf", getBufferf},
		{"getBuffer3f", getBuffer3f},
		{"getBufferfv", getBufferfv},
		{"getBufferi", getBufferi},
		{"getBuffer3i", getBuffer3i},
		{"getBufferiv", getBufferiv},

		{"genSources", genSources},
		{"deleteSources", deleteSources},
		{"isSource", isSource},
		{"sourcef", sourcef},
		{"source3f", source3f},
		{"sourcefv", sourcefv},
		{"sourcei", sourcei},
		{"source3i", source3i},
		{"sourceiv", sourceiv},
		{"getSourcef", getSourcef},
		{"getSource3f", getSource3f},
		{"getSourcefv", getSourcefv},
		{"getSourcei", getSourcei},
		{"getSource3i", getSource3i},
		{"getSourceiv", getSourceiv},
		{"sourcePlay", sourcePlay},
		{"sourcePlayv", sourcePlayv},
		{"sourcePause", sourcePause},
		{"sourcePausev", sourcePausev},
		{"sourceStop", sourceStop},
		{"sourceStopv", sourceStopv},
		{"sourceRewind", sourceRewind},
		{"sourceRewindv", sourceRewindv},
		{"sourceQueueBuffers", sourceQueueBuffers},

		{"listenerf", listenerf},
		{"listener3f", listener3f},
		{"listenerfv", listenerfv},
		{"listeneri", listeneri},
		{"listener3i", listener3i},
		{"listeneriv", listeneriv},
		{"getListenerf", getListenerf},
		{"getListener3f", getListener3f},
		{"getListenerfv", getListenerfv},
		{"getListeneri", getListeneri},
		{"getListener3i", getListener3i},
		{"getListeneriv", getListeneriv},

		{"enable", enable},
		{"disable", disable},
		{"isEnabled", isEnabled},
		{"getBoolean", getBoolean},
		{"getDouble", getDouble},
		{"getFloat", getFloat},
		{"getInteger", getInteger},
		{"getBooleanv", getBooleanv},
		{"getDoublev", getDoublev},
		{"getFloatv", getFloatv},
		{"getIntegerv", getIntegerv},
		{"getString", getString},
		{"distanceModel", distanceModel},
		{"dopplerFactor", dopplerFactor},
		{"speedOfSound", speedOfSound},

		{"getError", getError},

		{"isExtensionPresent", isExtensionPresent},
		{"getEnumValue", getEnumValue},
		{NULL, NULL}
	};

	luaL_openlib(L, "al", localLib, 0);

	lua_pushenumuration(L, "AL_NONE", AL_NONE);

	lua_pushenumuration(L, "AL_FALSE", AL_FALSE);
	lua_pushenumuration(L, "AL_TRUE", AL_TRUE);

	lua_pushenumuration(L, "AL_SOURCE_RELATIVE", AL_SOURCE_RELATIVE);
	lua_pushenumuration(L, "AL_CONE_INNER_ANGLE", AL_CONE_INNER_ANGLE);
	lua_pushenumuration(L, "AL_CONE_OUTER_ANGLE", AL_CONE_OUTER_ANGLE);
	lua_pushenumuration(L, "AL_PITCH", AL_PITCH);
	lua_pushenumuration(L, "AL_POSITION", AL_POSITION);
	lua_pushenumuration(L, "AL_DIRECTION", AL_DIRECTION);
	lua_pushenumuration(L, "AL_VELOCITY", AL_VELOCITY);
	lua_pushenumuration(L, "AL_LOOPING", AL_LOOPING);
	lua_pushenumuration(L, "AL_BUFFER", AL_BUFFER);
	lua_pushenumuration(L, "AL_GAIN", AL_GAIN);
	lua_pushenumuration(L, "AL_MIN_GAIN", AL_MIN_GAIN);
	lua_pushenumuration(L, "AL_MAX_GAIN", AL_MAX_GAIN);
	lua_pushenumuration(L, "AL_ORIENTATION", AL_ORIENTATION);
	lua_pushenumuration(L, "AL_SOURCE_STATE", AL_SOURCE_STATE);
	lua_pushenumuration(L, "AL_INITIAL", AL_INITIAL);
	lua_pushenumuration(L, "AL_PLAYING", AL_PLAYING);
	lua_pushenumuration(L, "AL_PAUSED", AL_PAUSED);
	lua_pushenumuration(L, "AL_STOPPED", AL_STOPPED);
	lua_pushenumuration(L, "AL_BUFFERS_QUEUED", AL_BUFFERS_QUEUED);
	lua_pushenumuration(L, "AL_BUFFERS_PROCESSED", AL_BUFFERS_PROCESSED);
	lua_pushenumuration(L, "AL_SEC_OFFSET", AL_SEC_OFFSET);
	lua_pushenumuration(L, "AL_SAMPLE_OFFSET", AL_SAMPLE_OFFSET);
	lua_pushenumuration(L, "AL_BYTE_OFFSET", AL_BYTE_OFFSET);
	lua_pushenumuration(L, "AL_SOURCE_TYPE", AL_SOURCE_TYPE);
	lua_pushenumuration(L, "AL_STATIC", AL_STATIC);
	lua_pushenumuration(L, "AL_STREAMING", AL_STREAMING);
	lua_pushenumuration(L, "AL_UNDETERMINED", AL_UNDETERMINED);
	lua_pushenumuration(L, "AL_FORMAT_MONO8", AL_FORMAT_MONO8);
	lua_pushenumuration(L, "AL_FORMAT_MONO16", AL_FORMAT_MONO16);
	lua_pushenumuration(L, "AL_FORMAT_STEREO8", AL_FORMAT_STEREO8);
	lua_pushenumuration(L, "AL_FORMAT_STEREO16", AL_FORMAT_STEREO16);
	lua_pushenumuration(L, "AL_REFERENCE_DISTANCE", AL_REFERENCE_DISTANCE);
	lua_pushenumuration(L, "AL_ROLLOFF_FACTOR", AL_ROLLOFF_FACTOR);
	lua_pushenumuration(L, "AL_CONE_OUTER_GAIN", AL_CONE_OUTER_GAIN);
	lua_pushenumuration(L, "AL_MAX_DISTANCE", AL_MAX_DISTANCE);
	lua_pushenumuration(L, "AL_FREQUENCY", AL_FREQUENCY);
	lua_pushenumuration(L, "AL_BITS", AL_BITS);
	lua_pushenumuration(L, "AL_CHANNELS", AL_CHANNELS);
	lua_pushenumuration(L, "AL_SIZE", AL_SIZE);
	lua_pushenumuration(L, "AL_UNUSED", AL_UNUSED);
	lua_pushenumuration(L, "AL_PENDING", AL_PENDING);
	lua_pushenumuration(L, "AL_PROCESSED", AL_PROCESSED);
	lua_pushenumuration(L, "AL_NO_ERROR", AL_NO_ERROR);
	lua_pushenumuration(L, "AL_INVALID_NAME", AL_INVALID_NAME);
	lua_pushenumuration(L, "AL_INVALID_ENUM", AL_INVALID_ENUM);
	lua_pushenumuration(L, "AL_INVALID_VALUE", AL_INVALID_VALUE);
	lua_pushenumuration(L, "AL_INVALID_OPERATION", AL_INVALID_OPERATION);
	lua_pushenumuration(L, "AL_OUT_OF_MEMORY", AL_OUT_OF_MEMORY);
	lua_pushenumuration(L, "AL_VENDOR", AL_VENDOR);
	lua_pushenumuration(L, "AL_VERSION", AL_VERSION);
	lua_pushenumuration(L, "AL_RENDERER", AL_RENDERER);
	lua_pushenumuration(L, "AL_EXTENSIONS", AL_EXTENSIONS);
	lua_pushenumuration(L, "AL_DOPPLER_FACTOR", AL_DOPPLER_FACTOR);
	lua_pushenumuration(L, "AL_DOPPLER_VELOCITY", AL_DOPPLER_VELOCITY);
	lua_pushenumuration(L, "AL_SPEED_OF_SOUND", AL_SPEED_OF_SOUND);
	lua_pushenumuration(L, "AL_DISTANCE_MODEL", AL_DISTANCE_MODEL);
	lua_pushenumuration(L, "AL_INVERSE_DISTANCE", AL_INVERSE_DISTANCE);
	lua_pushenumuration(L, "AL_INVERSE_DISTANCE_CLAMPED", AL_INVERSE_DISTANCE_CLAMPED);
	lua_pushenumuration(L, "AL_LINEAR_DISTANCE", AL_LINEAR_DISTANCE);
	lua_pushenumuration(L, "AL_LINEAR_DISTANCE_CLAMPED", AL_LINEAR_DISTANCE_CLAMPED);
	lua_pushenumuration(L, "AL_EXPONENT_DISTANCE", AL_EXPONENT_DISTANCE);
	lua_pushenumuration(L, "AL_EXPONENT_DISTANCE_CLAMPED", AL_EXPONENT_DISTANCE_CLAMPED);

	return 1;
}
