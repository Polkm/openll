#include "luaGL40.h"

#include <GL/glew.h>
#include "olua.h"


#ifdef GL_VERSION_4_0
struct DrawArraysIndirectCommand {
	GLuint count;
	GLuint primCount;
	GLuint first;
	GLuint baseInstance;
};

struct DrawElementsIndirectCommand {
	GLuint count;
	GLuint primCount;
	GLuint firstIndex;
	GLuint baseVertex;
	GLuint baseInstance;
};

// Delimit the boundaries of a query object on an indexed target.
// Takes (target, index, id)
static int beginQueryIndexed(lua_State* L) {
	return lua_wrapfunction(L, glBeginQueryIndexed);
}

// Bind a transform feedback object.
// Takes (target, id)
static int bindTransformFeedback(lua_State* L) {
	return lua_wrapfunction(L, glBindTransformFeedback);
}

// Specify the equation used for both the RGB blend equation and the Alpha blend equation.
// Takes (buf, mode)
static int blendEquationi(lua_State* L) {
	return lua_wrapfunction(L, glBlendEquationi);
}

// Set the RGB blend equation and the alpha blend equation separately.
// Takes (buf, modeRGB, modeAlpha)
static int blendEquationSeparatei(lua_State* L) {
	return lua_wrapfunction(L, glBlendEquationSeparatei);
}

// Specify pixel arithmetic. Pixels can be drawn using a function that blends the incoming (source)
// RGBA values with the RGBA values that are already in the frame buffer (the destination values).
// Takes (buf, sfactor, dfactor)
static int blendFunci(lua_State* L) {
	return lua_wrapfunction(L, glBlendFunci);
}

// Specify pixel arithmetic for RGB and alpha components separately.
// Takes (buf, srcRGB, dstRGB, srcAlpha, dstAlpha)
static int blendFuncSeparatei(lua_State* L) {
	return lua_wrapfunction(L, glBlendFuncSeparatei);
}

// Specify the clear value for the depth buffer.
// Takes (depth)
static int clearDepthf(lua_State* L) {
	return lua_wrapfunction(L, glClearDepthf);
}

// Delete transform feedback objects.
// Takes (id1, id2, id3, ...)
static int deleteTransformFeedbacks(lua_State* L) {
	for (int i = 1; i <= lua_gettop(L); ++i) {
		auto id = lua_tocast<GLuint>(L, i);
		glDeleteTransformFeedbacks(1, &id);
	}
	return 0;
}

// Specify mapping of depth values from normalized device coordinates to window coordinates.
// Takes (nearVal, farVal)
static int depthRangef(lua_State* L) {
	return lua_wrapfunction(L, glDepthRangef);
}

// glDispatchCompute — launch one or more compute work groups
// glDispatchComputeIndirect — launch one or more compute work groups using parameters stored in a buffer

// Render primitives from array data, taking parameters from memory.
// Takes (mode, indirect)
static int drawArraysIndirect(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	if (lua_istable(L, 2)) {
		DrawArraysIndirectCommand indirect;
		indirect.count = lua_toflieldcastnumber<GLuint>(L, 2, "count");
		indirect.primCount = lua_toflieldcastnumber<GLuint>(L, 2, "primCount");
		indirect.first = lua_toflieldcastnumber<GLuint>(L, 2, "first");
		indirect.baseInstance = lua_toflieldcastnumber<GLuint>(L, 2, "baseInstance");
		glDrawArraysIndirect(mode, &indirect);
	} else {
		auto offest = lua_tocast<lua_Integer>(L, 2);
		glDrawArraysIndirect(mode, (void*)offest);
	}
	return 0;
}

// Render indexed primitives from array data, taking parameters from memory.
// Takes (mode, type, indirect)
static int drawElementsIndirect(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto type = lua_tocast<GLenum>(L, 2);
	if (lua_istable(L, 2)) {
		DrawElementsIndirectCommand indirect;
		indirect.count = lua_toflieldcastnumber<GLuint>(L, 2, "count");
		indirect.primCount = lua_toflieldcastnumber<GLuint>(L, 2, "primCount");
		indirect.firstIndex = lua_toflieldcastnumber<GLuint>(L, 2, "firstIndex");
		indirect.baseVertex = lua_toflieldcastnumber<GLuint>(L, 2, "baseVertex");
		indirect.baseInstance = lua_toflieldcastnumber<GLuint>(L, 2, "baseInstance");
		glDrawElementsIndirect(mode, type, &indirect);
	} else {
		auto offest = lua_tocast<lua_Integer>(L, 3);
		glDrawElementsIndirect(mode, type, (void*)offest);
	}
	return 0;
}

// Render primitives using a count derived from a transform feedback object.
// Takes (mode, id)
static int drawTransformFeedback(lua_State* L) {
	return lua_wrapfunction(L, glDrawTransformFeedback);
}

// Render primitives using a count derived from a specifed stream of a transform feedback object.
// Takes (mode, id, stream)
static int drawTransformFeedbackStream(lua_State* L) {
	return lua_wrapfunction(L, glDrawTransformFeedbackStream);
}

// Delimit the boundaries of a query object on an indexed target.
// Takes (target, index)
static int endQueryIndexed(lua_State* L) {
	return lua_wrapfunction(L, glEndQueryIndexed);
}

// Reserve transform feedback object names.
// Takes (n) Returns (obj1, obj2, obj3, ...)
static int genTransformFeedbacks(lua_State* L) {
	return lua_wrapgenfunction(L, glGenRenderbuffers);
}

// Query the name of an active shader subroutine.
// Takes (program, shadertype, index, bufsize) Returns (name, length)
static int getActiveSubroutineName(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto shadertype = lua_tocast<GLenum>(L, 2);
	auto index = lua_tocast<GLuint>(L, 3);
	auto bufsize = lua_tocast<GLsizei>(L, 4);
	GLsizei length;
	auto name = new char[bufsize];
	glGetActiveSubroutineName(program, shadertype, index, bufsize, &length, name);
	lua_pushstring(L, name);
	lua_pushnumber(L, length);
	delete [] name;
	return 2;
}

// Query a property of an active shader subroutine uniform.
// Takes (program, shadertype, index, pname) Returns (values)
static int getActiveSubroutineUniform(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto shadertype = lua_tocast<GLenum>(L, 2);
	auto index = lua_tocast<GLuint>(L, 3);
	auto pname = lua_tocast<GLenum>(L, 4);
	if (pname == GL_COMPATIBLE_SUBROUTINES) {
		GLint count;
		glGetActiveSubroutineUniformiv(program, shadertype, index, GL_NUM_COMPATIBLE_SUBROUTINES, &count);
		auto values = new GLint[count];
		glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
		lua_pusharray(L, values, count);
		delete [] values;
	} else {
		GLint value;
		glGetActiveSubroutineUniformiv(program, shadertype, index, pname, &value);
		lua_pushnumber(L, value);
	}
	return 1;
}

// Query the name of an active shader subroutine uniform.
// Takes (program, shadertype, index, bufsize) Returns (name, length)
static int getActiveSubroutineUniformName(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto shadertype = lua_tocast<GLenum>(L, 2);
	auto index = lua_tocast<GLuint>(L, 3);
	auto bufsize = lua_tocast<GLsizei>(L, 4);
	GLsizei length;
	auto name = new char[bufsize];
	glGetActiveSubroutineUniformName(program, shadertype, index, bufsize, &length, name);
	lua_pushstring(L, name);
	lua_pushnumber(L, length);
	delete [] name;
	return 2;
}

// Retrieve properties of a program object corresponding to a specified shader stage.
// Takes (program, shadertype, pname, count) Returns (values)
static int getProgramStageiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetProgramStageiv);
}

// Return parameters of an indexed query object target.
// Takes (target, index, pname, count) Returns (params)
static int getQueryIndexediv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetQueryIndexediv);
}

// Retrieve the index of a subroutine uniform of a given shader stage within a program.
// Takes (program, shadertype, name) Returns (index)
static int getSubroutineIndex(lua_State* L) {
	return lua_wrapfunction(L, glGetSubroutineIndex);
}

// Retrieve the location of a subroutine uniform of a given shader stage within a program.
// Takes (program, shadertype, name) Returns (location)
static int getSubroutineUniformLocation(lua_State* L) {
	return lua_wrapfunction(L, glGetSubroutineUniformLocation);
}

// Retrieve the value of a subroutine uniform of a given shader stage of the current program.
// Takes (shadertype, location, count) Returns (values)
static int getUniformSubroutineuiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetUniformSubroutineuiv);
}

// Determine if a name corresponds to a transform feedback object.
// Takes (id) Returns (boolean)
static int isTransformFeedback(lua_State* L) {
	return lua_wrapfunction(L, glIsTransformFeedback);
}

// Specifies minimum rate at which sample shaing takes place.
// Takes (value)
static int minSampleShading(lua_State* L) {
	return lua_wrapfunction(L, glMinSampleShading);
}

// Specifies the parameters for patch primitives.
// Takes (pname, value)
static int patchParameteri(lua_State* L) {
	return lua_wrapfunction(L, glPatchParameteri);
}
// Takes (pname, values)
static int patchParameterfv(lua_State* L) {
	return lua_wraparrayfunction(L, glPatchParameterfv);
}

// Pause transform feedback operations.
static int pauseTransformFeedback(lua_State* L) {
	return lua_wrapfunction(L, glPauseTransformFeedback);
}

// Resume transform feedback operations.
static int resumeTransformFeedback(lua_State* L) {
	return lua_wrapfunction(L, glResumeTransformFeedback);
}

// glUniformSubroutines: load active subroutine uniforms
#endif

#ifdef GL_VERSION_4_1
// Set the active program object for a program pipeline object.
// Takes (pipeline, program)
static int activeShaderProgram(lua_State* L) {
	return lua_wrapfunction(L, glActiveShaderProgram);
}

// Bind a program pipeline to the current context.
// Takes (pipeline)
static int bindProgramPipeline(lua_State* L) {
	return lua_wrapfunction(L, glBindProgramPipeline);
}

// Create a stand-alone program from an array of null-terminated source code strings.
// Takes (type, source)
static int createShaderProgramv(lua_State* L) {
	auto type = lua_tocast<GLuint>(L, 1);
	if (lua_istable(L, 2)) {
		GLsizei count = luaL_getn(L, 2);
		auto strings = lua_tabletobasicarray<const GLchar*>(L, 2);
		glCreateShaderProgramv(type, count, strings);
		delete [] strings;
	} else {
		auto string = lua_tostring(L, 2);
		int length = strlen(string);
		glCreateShaderProgramv(type, 1, &string);
	}
	return 0;
}

// Delete program pipeline objects.
// Takes (pipeline1, pipeline2, pipeline3, ...)
static int deleteProgramPipelines(lua_State* L) {
	for (int i = 1; i <= lua_gettop(L); ++i) {
		auto pipeline = lua_tocast<GLuint>(L, i);
		glDeleteProgramPipelines(1, &pipeline);
	}
	return 0;
}

// Specify mapping of depth values from normalized device coordinates to window coordinates for a specified set of viewports.
// Takes (first, count, v)
static int depthRangeArrayv(lua_State* L) {
	return lua_wraparrayfunction(L, glDepthRangeArrayv);
}

// Specify mapping of depth values from normalized device coordinates to window coordinates for a specified viewport.
// Takes (index, nearVal, farVal)
static int depthRangeIndexed(lua_State* L) {
	return lua_wrapfunction(L, glDepthRangeIndexed);
}

// Reserve program pipeline object names.
// Takes (n) Returns (obj1, obj2, obj3, ...)
static int genProgramPipelines(lua_State* L) {
	return lua_wrapgenfunction(L, glGenProgramPipelines);
}

// Return a binary representation of a program object's compiled and linked executable source.
// Takes (program, bufsize) Returns (binary, binaryFormat, length)
static int getProgramBinary(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto bufsize = lua_tocast<GLsizei>(L, 2);
	GLsizei length;
	GLenum binaryFormat;
	auto binary = new char[bufsize];
	glGetProgramBinary(program, bufsize, &length, &binaryFormat, binary);
	lua_pusharray(L, binary, bufsize, true);
	lua_pushnumber(L, binaryFormat);
	lua_pushnumber(L, length);
	return 3;
}

// Retrieve properties of a program pipeline object.
// Takes (pipeline, pname, count) Returns (params)
static int getProgramPipelineiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetProgramPipelineiv);
}

// Retrieve the info log string from a program pipeline object.
// Takes (pipeline, bufSize) Returns (infoLog, length);
static int getProgramPipelineInfoLog(lua_State* L) {
	auto pipeline = lua_tocast<GLuint>(L, 1);
	auto bufSize = lua_tocast<GLsizei>(L, 2);
	GLsizei length;
	auto infoLog = new char[bufSize];
	glGetProgramPipelineInfoLog(pipeline, bufSize, &length, infoLog);
	lua_pushstring(L, infoLog);
	lua_pushnumber(L, length);
	delete [] infoLog;
	return 2;
}

// Retrieve the range and precision for numeric formats supported by the shader compiler.
// Takes (shaderType, precisionType) Returns (precision, range)
static int getShaderPrecisionFormat(lua_State* L) {
	auto shaderType = lua_tocast<GLenum>(L, 1);
	auto precisionType = lua_tocast<GLenum>(L, 2);
	GLint range[2];
	GLint precision;
	glGetShaderPrecisionFormat(shaderType, precisionType, range, &precision);
	lua_pushnumber(L, precision);
	lua_pusharray(L, range, 2);
	return 2;
}

// Determine if a name corresponds to a program pipeline object.
// Takes (pipeline) Returns (boolean)
static int isProgramPipeline(lua_State* L) {
	return lua_wrapfunction(L, glIsProgramPipeline);
}

// glProgramBinary: load a program object with a program binary

// Specify a parameter for a program object.
// Takes (program, pname, value)
static int programParameteri(lua_State* L) {
	return lua_wrapfunction(L, glProgramParameteri);
}

// glProgramUniform: Specify the value of a uniform variable for a specified program object.

// Release resources consumed by the implementation's shader compiler.
static int releaseShaderCompiler(lua_State* L) {
	return lua_wrapfunction(L, glReleaseShaderCompiler);
}

// Define the scissor box for multiple viewports.
// Takes (first, count, v)
static int scissorArrayv(lua_State* L) {
	return lua_wraparrayfunction(L, glScissorArrayv);
}

// Define the scissor box for a specific viewport.
// Takes (index, left, bottom, width, height)
static int scissorIndexed(lua_State* L) {
	return lua_wrapfunction(L, glScissorIndexed);
}
// Takes (index, v)
static int scissorIndexedv(lua_State* L) {
	return lua_wraparrayfunction(L, glScissorIndexedv);
}

// glShaderBinary: load pre-compiled shader binaries
// glUseProgramStages: bind stages of a program object to a program pipeline
// glValidateProgramPipeline: validate a program pipeline object against current GL state

// glViewportArray: set multiple viewports
// glViewportIndexed: set a specified viewport
#endif

#ifdef GL_VERSION_4_2
// Bind a level of a texture to an image unit.
// Takes (unit, texture, level, layered, layer, access, format)
static int bindImageTexture(lua_State* L) {
	return lua_wrapfunction(L, glBindImageTexture);
}

// Draw multiple instances of a range of elements with offset applied to instanced attributes.
// Takes (mode, first, count, primcount, baseinstance)
static int drawArraysInstancedBaseInstance(lua_State* L) {
	return lua_wrapfunction(L, glDrawArraysInstancedBaseInstance);
}

// Draw multiple instances of a set of elements with offset applied to instanced attributes.
// Takes (mode, count, type, indices, primcount, baseinstance)
static int drawElementsInstancedBaseInstance(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto count = lua_tocast<GLsizei>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	auto primcount = lua_tocast<GLsizei>(L, 5);
	auto baseinstance = lua_tocast<GLuint>(L, 6);
	void* indices = 0;
	if (lua_istable(L, 4)) {
		indices = lua_tabletoglarray(L, 4, type);
		glDrawElementsInstancedBaseInstance(mode, count, type, indices, primcount, baseinstance);
		delete [] indices;
	} else
		glDrawElementsInstancedBaseInstance(mode, count, type, indices, primcount, baseinstance);
	return 0;
}

// Render multiple instances of a set of primitives from array data with a per-element offset.
// Takes (mode, count, type, indices, primcount, basevertex, baseinstance)
static int drawElementsInstancedBaseVertexBaseInstance(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto count = lua_tocast<GLsizei>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	auto primcount = lua_tocast<GLsizei>(L, 5);
	auto basevertex = lua_tocast<GLint>(L, 6);
	auto baseinstance = lua_tocast<GLuint>(L, 7);
	void* indices = 0;
	if (lua_istable(L, 4)) {
		indices = lua_tabletoglarray(L, 4, type);
		glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, primcount, basevertex, baseinstance);
		delete [] indices;
	} else
		glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, primcount, basevertex, baseinstance);
	return 0;
}

// Render multiple instances of primitives using a count derived from a transform feedback object.
// Takes (mode, id, primcount)
static int drawTransformFeedbackInstanced(lua_State* L) {
	return lua_wrapfunction(L, glDrawTransformFeedbackInstanced);
}

// Render multiple instances of primitives using a count derived from a specifed stream of a transform feedback object.
// Takes (mode, id, stream, primcount)
static int drawTransformFeedbackStreamInstanced(lua_State* L) {
	return lua_wrapfunction(L, glDrawTransformFeedbackStreamInstanced);
}

// Retrieve information about the set of active atomic counter buffers for a program.
// Takes (program, bufferIndex, pname) Returns (params)
static int getActiveAtomicCounterBufferiv(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto bufferIndex = lua_tocast<GLuint>(L, 2);
	auto pname = lua_tocast<GLenum>(L, 3);
	if (pname == GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES) {
		GLint count = 1;
		glGetActiveAtomicCounterBufferiv(program, bufferIndex, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS, &count);
		auto params = new GLint[count];
		glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
		lua_pusharray(L, params, count);
		delete [] params;
	} else {
		GLint param;
		glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, &param);
		lua_pushnumber(L, param);
	}
	return 1;
}

// Retrieve information about implementation-dependent support for internal formats.
// Takes (target, internalformat, pname, count) Returns (params)
/*static int getInternalFormativ(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto internalformat = lua_tocast<GLenum>(L, 2);
	auto pname = lua_tocast<GLenum>(L, 3);
	auto count = lua_tocast<GLuint>(L, 4);
	auto parmas = new GLint[count];
	glGetInternalFormativ(target, internalformat, pname, sizeof(GLint) * count, parmas);
	lua_pusharray(L, parmas, count, true);
	return 1;
}
static int getInternalFormati64v(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto internalformat = lua_tocast<GLenum>(L, 2);
	auto pname = lua_tocast<GLenum>(L, 3);
	auto count = lua_tocast<GLuint>(L, 4);
	auto parmas = new GLint64[count];
	glGetInternalFormati64v(target, internalformat, pname, sizeof(GLint64) * count, parmas);
	lua_pusharray(L, parmas, count, true);
	return 1;
}*/

// Return a generic vertex attribute parameter.
// Takes (index, pname, count) Returns (params)
static int getVertexAttribLdv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetVertexAttribLdv);
}

// Defines a barrier ordering memory transactions.
// Takes (barriers)
static int memoryBarrier(lua_State* L) {
	return lua_wrapfunction(L, glMemoryBarrier);
}

// glTexStorage1D: simultaneously specify storage for all levels of a one-dimensional texture
// glTexStorage2D: simultaneously specify storage for all levels of a two-dimensional or one-dimensional array texture
// glTexStorage3D: simultaneously specify storage for all levels of a three-dimensional, two-dimensional array or cube-map array texture

#endif

#ifdef GL_VERSION_4_3
// Bind a buffer to a vertex buffer bind point.
// Takes (bindingindex, buffer, offset, stride)
static int bindVertexBuffer(lua_State* L) {
	return lua_wrapfunction(L, glBindVertexBuffer);
}

// Fill a buffer object's data store with a fixed value.
//static int clearBufferData(lua_State* L) {
//}

// Fill all or part of buffer object's data store with a fixed value.
//static int clearBufferSubData(lua_State* L) {
//}

// Perform a raw data copy between two images.
// Takes (srcName, srcTarget, srcLevel, srcX, srcY, srcZ,
//			dstName, dstTarget, dstLevel, dstX, dstY, dstZ,
//			srcWidth, srcHeight, srcDepth)
static int copyImageSubData(lua_State* L) {
	auto srcName = lua_tocast<GLuint>(L, 1);
	auto srcTarget = lua_tocast<GLenum>(L, 2);
	auto srcLevel = lua_tocast<GLint>(L, 3);
	auto srcX = lua_tocast<GLint>(L, 4);
	auto srcY = lua_tocast<GLint>(L, 5);
	auto srcZ = lua_tocast<GLint>(L, 6);
	auto dstName = lua_tocast<GLuint>(L, 7);
	auto dstTarget = lua_tocast<GLenum>(L, 8);
	auto dstLevel = lua_tocast<GLint>(L, 9);
	auto dstX = lua_tocast<GLint>(L, 10);
	auto dstY = lua_tocast<GLint>(L, 11);
	auto dstZ = lua_tocast<GLint>(L, 12);
	auto srcWidth = lua_tocast<GLsizei>(L, 13);
	auto srcHeight = lua_tocast<GLsizei>(L, 14);
	auto srcDepth = lua_tocast<GLsizei>(L, 15);
	glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ,
			dstName, dstTarget, dstLevel, dstX, dstY, dstZ,
			srcWidth, srcHeight, srcDepth);
	return 0;
}

// Launch one or more compute work groups.
// Takes (num_groups_x, num_groups_y, num_groups_z)
static int dispatchCompute(lua_State* L) {
	return lua_wrapfunction(L, glDispatchCompute);
}

// Launch one or more compute work groups using parameters stored in a buffer.
// Takes (indirect)
static int dispatchComputeIndirect(lua_State* L) {
	return lua_wrapfunction(L, glDispatchComputeIndirect);
}

// glDebugMessageCallback — specify a callback to receive debugging messages from the GL
// glDebugMessageControl — control the reporting of debug messages in a debug context
// glDebugMessageInsert — inject an application-supplied message into the debug message queue

// Set a named parameter of a framebuffer.
// Takes (target, pname, param)
static int framebufferParameteri(lua_State* L) {
	return lua_wrapfunction(L, glFramebufferParameteri);
}

// Retrieve messages from the debug message log.
// Takes (count, bufSize) Returns (sources, types, ids, severities, lengths, messageLog)
static int getDebugMessageLog(lua_State* L) {
	auto count = lua_tocast<GLuint>(L, 1);
	auto bufSize = lua_tocast<GLsizei>(L, 2);
	auto sources = new GLenum[count];
	auto types = new GLenum[count];
	auto ids = new GLuint[count];
	auto severities = new GLenum[count];
	auto lengths = new GLsizei[count];
	auto messageLog = new char[bufSize];
	glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
	lua_pusharray(L, sources, count, true);
	lua_pusharray(L, types, count, true);
	lua_pusharray(L, ids, count, true);
	lua_pusharray(L, severities, count, true);
	lua_pusharray(L, lengths, count, true);
	lua_pushstring(L, messageLog);
	delete [] messageLog;
	return 6;
}

// Retrieve a named parameter from a framebuffer.
// Takes (target, pname) Returns (params)
static int getFramebufferParameteriv(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto pname = lua_tocast<GLenum>(L, 2);
	GLint params;
	glGetFramebufferParameteriv(target, pname, &params);
	lua_pushnumber(L, params);
	return 1;
}

// Retrieve the label of a named object identified within a namespace.
// Takes (identifier, name, bufSize) Return (label, length)
static int getObjectLabel(lua_State* L) {
	auto identifier = lua_tocast<GLenum>(L, 1);
	auto name = lua_tocast<GLuint>(L, 2);
	auto bufSize = lua_tocast<GLsizei>(L, 3);
	GLsizei length;
	auto label = new char[bufSize];
	glGetObjectLabel(identifier, name, bufSize, &length, label);
	lua_pushstring(L, label);
	lua_pushnumber(L, length);
	delete [] label;
	return 2;
}

// glGetObjectPtrLabel: retrieve the label of a sync object identified by a pointer

// Query a property of an interface in a program.
// Takes (program, programInterface, pname) Returns (params)
static int getProgramInterfaceiv(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto programInterface = lua_tocast<GLenum>(L, 2);
	auto pname = lua_tocast<GLenum>(L, 3);
	GLint param;
	glGetProgramInterfaceiv(program, programInterface, pname, &param);
	lua_pushnumber(L, param);
	return 1;
}

// Doable just lazy
// glGetProgramResource: retrieve values for multiple properties of a single active resource within a program object
// glGetProgramResourceLocation: query the location of a named resource within a program
// glGetProgramResourceLocationIndex: query the fragment color index of a named variable within a program
// glGetProgramResourceIndex: query the index of a named resource within a program
// glGetProgramResourceName: query the name of an indexed resource within a program

// glInvalidateBufferData: invalidate the content of a buffer object's data store
// glInvalidateBufferSubData: invalidate a region of a buffer object's data store
// glInvalidateFramebuffer: invalidate the content some or all of a framebuffer object's attachments
// glInvalidateSubFramebuffer: invalidate the content of a region of some or all of a framebuffer object's attachments
// glInvalidateTexImage: invalidate the entirety a texture image
// glInvalidateTexSubImage: invalidate a region of a texture image

// glMultiDrawArraysIndirect: render multiple sets of primitives from array data, taking parameters from memory
// glMultiDrawElementsIndirect: render indexed primitives from array data, taking parameters from memory

// glObjectLabel: label a named object identified within a namespace
// glObjectPtrLabel: label a a sync object identified by a pointer

// glPopDebugGroup: pop the active debug group
// glPushDebugGroup: push a named debug group into the command stream

// glShaderStorageBlockBinding: change an active shader storage block binding

// glTexBufferRange: bind a range of a buffer's data store to a buffer texture

// glTexStorage2DMultisample: specify storage for a two-dimensional multisample texture
// glTexStorage3DMultisample: specify storage for a two-dimensional multisample array texture

// glTextureView: initialize a texture as a data alias of another texture's data store

// glVertexAttribBinding: associate a vertex attribute and a vertex buffer binding
// glVertexAttribFormat: specify the organization of vertex arrays
// glVertexBindingDivisor: modify the rate at which generic vertex attributes advance
#endif

int olf::gl::registerLua40(lua_State* L) {
	const luaL_reg localLib[] = {
#ifdef GL_VERSION_4_0
		{"beginQueryIndexed", beginQueryIndexed},
		{"bindTransformFeedback", bindTransformFeedback},
		{"blendEquationi", blendEquationi},
		{"blendEquationSeparatei", blendEquationSeparatei},
		{"blendFunci", blendFunci},
		{"blendFuncSeparatei", blendFuncSeparatei},
		{"clearDepthf", clearDepthf},
		{"deleteTransformFeedbacks", deleteTransformFeedbacks},
		{"depthRangef", depthRangef},
		{"drawArraysIndirect", drawArraysIndirect},
		{"drawElementsIndirect", drawElementsIndirect},
		{"drawTransformFeedback", drawTransformFeedback},
		{"drawTransformFeedbackStream", drawTransformFeedbackStream},
		{"endQueryIndexed", endQueryIndexed},
		{"genTransformFeedbacks", genTransformFeedbacks},
		{"getActiveSubroutineName", getActiveSubroutineName},
		{"getActiveSubroutineUniform", getActiveSubroutineUniform},
		{"getActiveSubroutineUniformName", getActiveSubroutineUniformName},
		{"getProgramStageiv", getProgramStageiv},
		{"getQueryIndexediv", getQueryIndexediv},
		{"getSubroutineIndex", getSubroutineIndex},
		{"getSubroutineUniformLocation", getSubroutineUniformLocation},
		{"getUniformSubroutineuiv", getUniformSubroutineuiv},
		{"isTransformFeedback", isTransformFeedback},
		{"minSampleShading", minSampleShading},
		{"patchParameteri", patchParameteri},
		{"patchParameterfv", patchParameterfv},
		{"pauseTransformFeedback", pauseTransformFeedback},
		{"resumeTransformFeedback", resumeTransformFeedback},
#endif
#ifdef GL_VERSION_4_1
		{"activeShaderProgram", activeShaderProgram},
		{"bindProgramPipeline", bindProgramPipeline},
		{"createShaderProgramv", createShaderProgramv},
		{"deleteProgramPipelines", deleteProgramPipelines},
		{"depthRangeArrayv", depthRangeArrayv},
		{"depthRangeIndexed", depthRangeIndexed},
		{"genProgramPipelines", genProgramPipelines},
		{"getProgramBinary", getProgramBinary},
		{"getProgramPipelineiv", getProgramPipelineiv},
		{"getProgramPipelineInfoLog", getProgramPipelineInfoLog},
		{"getShaderPrecisionFormat", getShaderPrecisionFormat},
		{"isProgramPipeline", isProgramPipeline},
		{"programParameteri", programParameteri},
		{"releaseShaderCompiler", releaseShaderCompiler},
		{"scissorArrayv", scissorArrayv},
		{"scissorIndexed", scissorIndexed},
		{"scissorIndexedv", scissorIndexedv},
#endif
#ifdef GL_VERSION_4_2
		{"bindImageTexture", bindImageTexture},
		{"drawArraysInstancedBaseInstance", drawArraysInstancedBaseInstance},
		{"drawElementsInstancedBaseInstance", drawElementsInstancedBaseInstance},
		{"drawElementsInstancedBaseVertexBaseInstance", drawElementsInstancedBaseVertexBaseInstance},
		{"drawTransformFeedbackInstanced", drawTransformFeedbackInstanced},
		{"drawTransformFeedbackStreamInstanced", drawTransformFeedbackStreamInstanced},
		{"getActiveAtomicCounterBufferiv", getActiveAtomicCounterBufferiv},
		{"getVertexAttribLdv", getVertexAttribLdv},
		{"memoryBarrier", memoryBarrier},
		//{"getInternalFormativ", getInternalFormativ},
		//{"getInternalFormati64v", getInternalFormati64v},
#endif
#ifdef GL_VERSION_4_3
		{"bindVertexBuffer", bindVertexBuffer},
		//{"clearBufferData", clearBufferData},
		//{"clearBufferSubData", clearBufferSubData},
		{"copyImageSubData", copyImageSubData},
		{"dispatchCompute", dispatchCompute},
		{"dispatchComputeIndirect", dispatchComputeIndirect},
		{"framebufferParameteri", framebufferParameteri},
		{"getDebugMessageLog", getDebugMessageLog},
		{"getFramebufferParameteriv", getFramebufferParameteriv},
		{"getObjectLabel", getObjectLabel},
		{"getProgramInterfaceiv", getProgramInterfaceiv},
#endif 
		{NULL, NULL}
	};
	luaL_register(L, "gl", localLib);

	return 1;
}
