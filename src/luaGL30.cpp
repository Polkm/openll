#include "luaGL30.h"

#include <GL/glew.h>
#include "olua.h"

#include <cstdlib>

using namespace olf::gl;

#ifdef GL_VERSION_3_0
// Start conditional rendering.
// Takes (id, mode)
static int beginConditionalRender(lua_State* L) {
	return lua_wrapfunction(L, glBeginConditionalRender);
}

// Start transform feedback operation.
// Takes (primitiveMode)
static int beginTransformFeedback(lua_State* L) {
	return lua_wrapfunction(L, glBeginTransformFeedback);
}

// Bind a buffer object to an indexed buffer target.
// Takes (target, index, buffer)
static int bindBufferBase(lua_State* L) {
	return lua_wrapfunction(L, glBindBufferBase);
}

// Bind a range within a buffer object to an indexed buffer target.
// Takes (target, index, buffer, offset, size)
static int bindBufferRange(lua_State* L) {
	return lua_wrapfunction(L, glBindBufferRange);
}

// Bind a user-defined varying out variable to a fragment shader color number.
// Takes (program, colorNumber, name)
static int bindFragDataLocation(lua_State* L) {
	return lua_wrapfunction(L, glBindFragDataLocation);
}

// Bind a framebuffer to a framebuffer target.
// Takes (target, framebuffer)
static int bindFramebuffer(lua_State* L) {
	return lua_wrapfunction(L, glBindFramebuffer);
}

// Bind a renderbuffer to a renderbuffer target.
// Takes (target, renderbuffer)
static int bindRenderbuffer(lua_State* L) {
	return lua_wrapfunction(L, glBindRenderbuffer);
}

// Bind a vertex array object.
// Takes (array)
static int bindVertexArray(lua_State* L) {
	return lua_wrapfunction(L, glBindVertexArray);
}

// Copy a block of pixels from the read framebuffer to the draw framebuffer.
// Takes (srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter)
static int blitFramebuffer(lua_State* L) {
	return lua_wrapfunction(L, glBlitFramebuffer);
}

// Check the completeness status of a framebuffer.
// Takes (target)
static int checkFramebufferStatus(lua_State* L) {
	return lua_wrapfunction(L, glCheckFramebufferStatus);
}

// Specify whether data read via glReadPixels should be clamped.
// Takes (target, clamp)
static int clampColor(lua_State* L) {
	return lua_wrapfunction(L, glClampColor);
}

// Clear individual buffers of the currently bound draw framebuffer.
// Takes (buffer, drawBuffer, value)
static int clearBufferiv(lua_State* L) {
	return lua_wraparrayfunction(L, glClearBufferiv);
}
static int clearBufferuiv(lua_State* L) {
	return lua_wraparrayfunction(L, glClearBufferuiv);
}
static int clearBufferfv(lua_State* L) {
	return lua_wraparrayfunction(L, glClearBufferfv);
}
// Takes (buffer, drawBuffer, depth, stencil)
static int clearBufferfi(lua_State* L) {
	return lua_wrapfunction(L, glClearBufferfi);
}

// Takes (buf, red, green, blue, alpha)
static int colorMaski(lua_State* L) {
	return lua_wrapfunction(L, glColorMaski);
}

// Delete framebuffer objects.
// Takes (framebuffer1, framebuffer2, framebuffer3, ...)
static int deleteFramebuffers(lua_State* L) {
	return lua_wraploopfunction(L, glDeleteFramebuffers);
}

// Delete renderbuffer objects.
// Takes (renderbuffer1, renderbuffer2, renderbuffer3, ...)
static int deleteRenderbuffers(lua_State* L) {
	return lua_wraploopfunction(L, glDeleteRenderbuffers);
}

// Delete vertex array objects.
// Takes (array1, array2, array3, ...)
static int deleteVertexArrays(lua_State* L) {
	return lua_wraploopfunction(L, glDeleteVertexArrays);
}

// Takes (cap, index)
static int disablei(lua_State* L) {
	return lua_wrapfunction(L, glDisablei);
}

// Takes (cap, index)
static int enablei(lua_State* L) {
	return lua_wrapfunction(L, glEnablei);
}

// End conditional rendering.
static int endConditionalRender(lua_State* L) {
	return lua_wrapfunction(L, glEndConditionalRender);
}

// End transform feedback operation.
static int endTransformFeedback(lua_State* L) {
	return lua_wrapfunction(L, glEndTransformFeedback);
}

// Indicate modifications to a range of a mapped buffer.
// Takes (target, offset, length)
static int flushMappedBufferRange(lua_State* L) {
	return lua_wrapfunction(L, glFlushMappedBufferRange);
}

// Attach a renderbuffer as a logical buffer to the currently bound framebuffer object.
// Takes (target, attachment, renderbuffertarget, renderbuffer)
static int framebufferRenderbuffer(lua_State* L) {
	return lua_wrapfunction(L, glFramebufferRenderbuffer);
}

// Generate mipmaps for a specified texture target.
// Takes (target)
static int generateMipmap(lua_State* L) {
	return lua_wrapfunction(L, glGenerateMipmap);
}

// Generate framebuffer object names.
// Takes (n) Returns (obj1, obj2, obj3, ...)
static int genFramebuffers(lua_State* L) {
	return lua_wrapgenfunction(L, glGenFramebuffers);
}

// Generate renderbuffer object names.
// Takes (n) Returns (obj1, obj2, obj3, ...)
static int genRenderbuffers(lua_State* L) {
	return lua_wrapgenfunction(L, glGenRenderbuffers);
}

// Generate vertex array object names.
// Takes (n) Returns (obj1, obj2, obj3, ...)
static int genVertexArrays(lua_State* L) {
	return lua_wrapgenfunction(L, glGenVertexArrays);
}

// Query the bindings of color numbers to user-defined varying out variables.
// Takes (program, name) Returns (location)
static int getFragDataLocation(lua_State* L) {
	return lua_wrapfunction(L, glGetFragDataLocation);
}

// Retrieve information about attachments of a bound framebuffer object.
// Doesn't find the openGL function :S IDK why.
/*static int getFramebufferAttachmentParameter(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto attachment = lua_tocast<GLenum>(L, 2);
	auto pname = lua_tocast<GLenum>(L, 3);
	GLint params = 0;
	glGetFramebufferAttachmentParameter(target, attachment, pname, &params);
	lua_pushnumber(L, params);
	return 1;
}*/

// Retrieve information about a bound renderbuffer object.
// Takes (target, pname, count) Returns (params)
static int getRenderbufferParameteriv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetRenderbufferParameteriv);
}

// Retrieve information about varying variables selected for transform feedback.
// Takes (program, index, bufSize) Returns (name, type, size, length)
static int getTransformFeedbackVarying(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto index = lua_tocast<GLuint>(L, 2);
	auto bufSize = lua_tocast<GLsizei>(L, 3);
	GLsizei length, size;
	GLenum type;
	auto name = new GLchar[bufSize];
	glGetTransformFeedbackVarying(program, index, bufSize, &length, &size, &type, name);
	lua_push(L, name);
	lua_push(L, type);
	lua_push(L, size);
	lua_push(L, length);
	delete [] name;
	return 4;
}

// Determine if a name corresponds to a framebuffer object.
// Takes (framebuffer) Returns (boolean)
static int isFramebuffer(lua_State* L) {
	return lua_wrapfunction(L, glIsFramebuffer);
}

// Determine if a name corresponds to a renderbuffer object.
// Takes (renderbuffer) Returns (boolean)
static int isRenderbuffer(lua_State* L) {
	return lua_wrapfunction(L, glIsRenderbuffer);
}

// Determine if a name corresponds to a vertex array object.
// Takes (array) Returns (boolean)
static int isVertexArray(lua_State* L) {
	return lua_wrapfunction(L, glIsVertexArray);
}

// Map a section of a buffer object's data store.
// IDK how to make this work :S
//static int mapBufferRange(lua_State* L);

// Establish data storage, format and dimensions of a renderbuffer object's image.
// Takes (target, internalformat, width, height)
static int renderbufferStorage(lua_State* L) {
	return lua_wrapfunction(L, glRenderbufferStorage);
}

// Establish data storage, format, dimensions and sample count of a renderbuffer object's image.
// Takes (target, samples, internalformat, width, height)
static int renderbufferStorageMultisample(lua_State* L) {
	return lua_wrapfunction(L, glRenderbufferStorageMultisample);
}

// Specify multisample coverage parameters.
// Takes (value, invert)
static int sampleCoverage(lua_State* L) {
	return lua_wrapfunction(L, glSampleCoverage);
}

// Attach the storage for a buffer object to the active buffer texture.
// Takes (target, internalFormat, buffer)
static int texBuffer(lua_State* L) {
	return lua_wrapfunction(L, glTexBuffer);
}

// Specify values to record in transform feedback buffers.
// Takes (program, count, varyings, bufferMode)
static int transformFeedbackVaryings(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto count = lua_tocast<GLsizei>(L, 2);
	auto varyings = lua_tabletobasicarray<const GLchar*>(L, 3);
	auto bufferMode = lua_tocast<GLenum>(L, 4);
	glTransformFeedbackVaryings(program, count, varyings, bufferMode);
	delete [] varyings;
	return 0;
}

// Define an array of generic vertex attribute data.
// Takes (index, size, type, stride, offset/data)
static int vertexAttribIPointer(lua_State* L) {
	auto index = lua_tocast<GLuint>(L, 1);
	auto size = lua_tocast<GLint>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	auto stride = lua_tocast<GLsizei>(L, 4);
	const GLvoid* pointer = 0;
	if (lua_istable(L, 5)) {
		GLsizeiptr size;
		pointer = lua_tabletoglarray(L, 5, type, size);
	} else {
		pointer = (void*)lua_tocast<lua_Integer>(L, 5);
	}
	glVertexAttribIPointer(index, size, type, stride, pointer);
	return 0;
}
#endif

#ifdef GL_VERSION_3_1
// Copy part of the data store of a buffer object to the data store of another buffer object.
// Takes (readtarget, writetarget, readoffset, writeoffset, size)
static int copyBufferSubData(lua_State* L) {
	return lua_wrapfunction(L, glCopyBufferSubData);
}

// Draw multiple instances of a range of elements.
// Takes (mode, first, count, primcount)
static int drawArraysInstanced(lua_State* L) {
	return lua_wrapfunction(L, glDrawArraysInstanced);
}

// Draw multiple instances of a set of elements.
// Takes (mode, count, type, indices, primcount)
static int drawElementsInstanced(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto count = lua_tocast<GLsizei>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	auto primcount = lua_tocast<GLsizei>(L, 5);
	auto indices = lua_tabletoglarray(L, 4, type);
	glDrawElementsInstanced(mode, count, type, indices, primcount);
	delete [] indices;
	return 0;
}

// Query information about an active uniform block.
// Takes (program, uniformBlockIndex, pname, count) Returns (params)
static int getActiveUniformBlockiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetActiveUniformBlockiv);
}

// Retrieve the name of an active uniform block
// Takes (program, uniformBlockIndex, bufSize) Returns (uniformBlockName, length)
static int getActiveUniformBlockName(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto uniformBlockIndex = lua_tocast<GLuint>(L, 2);
	auto bufSize = lua_tocast<GLsizei>(L, 3);
	GLsizei length;
	auto uniformBlockName = new char[bufSize];
	glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, &length, uniformBlockName);
	lua_push(L, uniformBlockName);
	lua_push(L, length);
	delete [] uniformBlockName;
	return 2;
}

// Retrieve the index of a named uniform block.
// Takes (program, uniformBlockName) Returns (index)
static int getUniformBlockIndex(lua_State* L) {
	return lua_wrapfunction(L, glGetUniformBlockIndex);
}

// Retrieve the index of a named uniform block.
// Takes (program, uniformCount) Returns (uniformTable)
// {uniformIndex1 = uniformName1, uniformIndex2 = uniformName2, ...}
static int getUniformIndices(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto uniformCount = lua_tocast<GLsizei>(L, 2);
	auto uniformNames = new const GLchar*[uniformCount];
	auto uniformIndices = new GLuint[uniformCount];
	glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
	lua_newtable(L);
	for (int i = 0; i < uniformCount; ++i)
		lua_pushtablekeyvalue(L, uniformIndices[i], uniformNames[i]);
	delete [] uniformNames;
	delete [] uniformIndices;
	return 1;
}

// Specify the primitive restart index.
// Takes (index)
static int primitiveRestartIndex(lua_State* L) {
	return lua_wrapfunction(L, glPrimitiveRestartIndex);
}

// Assign a binding point to an active uniform block.
// Takes (program, uniformBlockIndex, uniformBlockBinding)
static int uniformBlockBinding(lua_State* L) {
	return lua_wrapfunction(L, glUniformBlockBinding);
}
#endif

#ifdef GL_VERSION_3_2
// Block and wait for a sync object to become signaled.
//static int clientWaitSync(lua_State* L);

// Deletes a sync object.
//static int deleteSync(lua_State* L);

// Render primitives from array data with a per-element offset.
// Takes (mode, count, type, indices, basevertex)
static int drawElementsBaseVertex(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto count = lua_tocast<GLsizei>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	auto basevertex = lua_tocast<GLint>(L, 5);
	void* indices = 0;
	if (lua_istable(L, 4)) {
		indices = lua_tabletoglarray(L, 4, type);
		glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
		delete [] indices;
	} else
		glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
	return 0;
}

// Render multiple instances of a set of primitives from array data with a per-element offset.
// Takes (mode, count, type, indices, primcount, basevertex)
static int drawElementsInstancedBaseVertex(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto count = lua_tocast<GLsizei>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	auto primcount = lua_tocast<GLsizei>(L, 5);
	auto basevertex = lua_tocast<GLint>(L, 6);
	void* indices = 0;
	if (lua_istable(L, 4)) {
		indices = lua_tabletoglarray(L, 4, type);
		glDrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex);
		delete [] indices;
	} else
		glDrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex);
	return 0;
}

// Render primitives from array data with a per-element offset.
// Takes (mode, start, end, count, type, indices, basevertex)
static int drawRangeElementsBaseVertex(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto start = lua_tocast<GLuint>(L, 2);
	auto end = lua_tocast<GLuint>(L, 3);
	auto count = lua_tocast<GLsizei>(L, 4);
	auto type = lua_tocast<GLenum>(L, 5);
	auto basevertex = lua_tocast<GLint>(L, 7);
	void* indices = 0;
	if (lua_istable(L, 6)) {
		indices = lua_tabletoglarray(L, 6, type);
		glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
		delete [] indices;
	} else
		glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	return 0;
}

// Create a new sync object and insert it into the GL command stream.
//static int fenceSync(lua_State* L);

// Attach a level of a texture object as a logical buffer to the currently bound framebuffer object.
// Takes (target, attachment, texture, level)
static int framebufferTexture(lua_State* L) {
	return lua_wrapfunction(L, glFramebufferTexture);
}
// Takes (target, attachment, textarget, texture, level)
static int framebufferTexture1D(lua_State* L) {
	return lua_wrapfunction(L, glFramebufferTexture1D);
}
static int framebufferTexture2D(lua_State* L) {
	return lua_wrapfunction(L, glFramebufferTexture2D);
}
// Takes (target, attachment, textarget, texture, level, layer)
static int framebufferTexture3D(lua_State* L) {
	return lua_wrapfunction(L, glFramebufferTexture3D);
}

// Attach a single layer of a texture to a framebuffer.
// Takes (target, attachment, texture, level, layer)
static int framebufferTextureLayer(lua_State* L) {
	return lua_wrapfunction(L, glFramebufferTextureLayer);
}

// Return the value or values of a selected parameter
// Takes (pname) Returns (params)
static int getInteger64v(lua_State* L) {
	auto pname = lua_tocast<GLenum>(L, 1);
	auto count = luaGLGetParamCount(pname);
	if (count > 1) {
		auto params = new GLint64[count];
		glGetInteger64v(pname, params);
		lua_pusharray(L, params, count);
		delete [] params;
	} else {
		GLint64 param;
		glGetInteger64v(pname, &param);
		lua_push(L, param);
	}
	return 1;
}
// Takes (pname, index) Returns (params)
static int getInteger64i_v(lua_State* L) {
	auto pname = lua_tocast<GLenum>(L, 1);
	auto index = lua_tocast<GLuint>(L, 2);
	auto count = luaGLGetParamCount(pname);
	if (count > 1) {
		auto params = new GLint64[count];
		glGetInteger64i_v(pname, index, params);
		lua_pusharray(L, params, count);
		delete [] params;
	} else {
		GLint64 param;
		glGetInteger64i_v(pname, index, &param);
		lua_push(L, param);
	}
	return 1;
}

// Retrieve the location of a sample.
// Takes (pname, index) Return (val)
static int getMultisamplefv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetMultisamplefv);
}

// Query the properties of a sync object.
//static int getSynciv(lua_State* L);

// Determine if a name corresponds to a sync object.
// Takes (sync) Returns (boolean)
//static int isSync(lua_State* L);

// Render multiple sets of primitives by specifying indices of array data elements and an index to apply to each index.
// Nested tables :'(
//static int multiDrawElementsBaseVertex(lua_State* L);

// Specifiy the vertex to be used as the source of data for flat shaded varyings.
// Takes (provokeMode)
static int provokingVertex(lua_State* L) {
	return lua_wrapfunction(L, glProvokingVertex);
}

// Set the value of a sub-word of the sample mask.
// Takes (maskNumber, mask)
static int sampleMaski(lua_State* L) {
	return lua_wrapfunction(L, glSampleMaski);
}

// Establish the data storage, format, dimensions, and number of samples of a multisample texture's image.
// Takes (target, samples, internalformat, width, height, fixedsamplelocations)
static int texImage2DMultisample(lua_State* L) {
	return lua_wrapfunction(L, glTexImage2DMultisample);
}

// Establish the data storage, format, dimensions, and number of samples of a multisample texture's image.
// Takes (target, samples, internalformat, width, height, depth, fixedsamplelocations)
static int texImage3DMultisample(lua_State* L) {
	return lua_wrapfunction(L, glTexImage3DMultisample);
}

// Instruct the GL server to block until the specified sync object becomes signaled.
// Takes (sync, flags, timeout)
// How to handle syncs?
//static int waitSync(lua_State* L);
#endif

#ifdef GL_VERSION_3_3
// Bind a user-defined varying out variable to a fragment shader color number and index.
// Takes (program, colorNumber, index, name)
static int bindFragDataLocationIndexed(lua_State* L) {
	return lua_wrapfunction(L, glBindFragDataLocationIndexed);
}

// Bind a named sampler to a texturing target.
// Takes (unit, sampler)
static int bindSampler(lua_State* L) {
	return lua_wrapfunction(L, glBindSampler);
}

// Delete named sampler objects.
// Takes (sampler1, sampler2, sampler3, ...)
static int deleteSamplers(lua_State* L) {
	return lua_wraploopfunction(L, glDeleteSamplers);
}

// Generate sampler object names.
// Takes (n) Returns (obj1, obj2, obj3, ...)
static int genSamplers(lua_State* L) {
	return lua_wrapgenfunction(L, glGenSamplers);
}

// Query the bindings of color indices to user-defined varying out variables.
// Takes (program, name) Returns (index)
static int getFragDataIndex(lua_State* L) {
	return lua_wrapfunction(L, glGetFragDataIndex);
}

// Return parameters of a query object.
// Takes (id, pname,count) Returns (params)
static int getQueryObjectiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetQueryObjectiv);
}
static int getQueryObjectuiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetQueryObjectuiv);
}
static int getQueryObjecti64v(lua_State* L) {
	return lua_wrapgetfunction(L, glGetQueryObjecti64v);
}
static int getQueryObjectui64v(lua_State* L) {
	return lua_wrapgetfunction(L, glGetQueryObjectui64v);
}

// Return sampler parameter values.
// Takes (sampler, pname, count) Returns (params)
static int getSamplerParameterfv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetSamplerParameterfv);
}
static int getSamplerParameteriv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetSamplerParameteriv);
}

// Return a generic vertex attribute parameter.
// Takes (index, pname, count) Returns (params)
static int getVertexAttribIiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetVertexAttribIiv);
}
static int getVertexAttribIuiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetVertexAttribIuiv);
}

// Test whether a capability is enabled.
// Takes (cap, index) Returns (boolean)
static int isEnabledi(lua_State* L) {
	return lua_wrapfunction(L, glIsEnabledi);
}

// Determine if a name corresponds to a sampler object.
// Takes (id) Returns (boolean)
static int isSampler(lua_State* L) {
	return lua_wrapfunction(L, glIsSampler);
}

// Record the GL time into a query object after all previous commands have reached the GL server but have not yet necessarily executed.
// Takes (id, target)
static int queryCounter(lua_State* L) {
	return lua_wrapfunction(L, glQueryCounter);
}

// Set sampler parameters.
// Takes (sampler, pname, param)
static int samplerParameterf(lua_State* L) {
	return lua_wrapfunction(L, glSamplerParameterf);
}
static int samplerParameteri(lua_State* L) {
	return lua_wrapfunction(L, glSamplerParameteri);
}
// Takes (sampler, pname, params)
static int samplerParameterfv(lua_State* L) {
	return lua_wraparrayfunction(L, glSamplerParameterfv);
}
static int samplerParameteriv(lua_State* L) {
	return lua_wraparrayfunction(L, glSamplerParameteriv);
}

// Set texture parameters.
// Takes (target, pname, param)
static int texParameterIiv(lua_State* L) {
	return lua_wraparrayfunction(L, glTexParameterIiv);
}
static int texParameterIuiv(lua_State* L) {
	return lua_wraparrayfunction(L, glTexParameterIuiv);
}

// Specify the value of a uniform variable for the current program object.
// Takes (location, v0, v1, v2, ...)
static int uniform1ui(lua_State* L) {
	return lua_wrapfunction(L, glUniform1ui);
}
static int uniform2ui(lua_State* L) {
	return lua_wrapfunction(L, glUniform2ui);
}
static int uniform3ui(lua_State* L) {
	return lua_wrapfunction(L, glUniform3ui);
}
static int uniform4ui(lua_State* L) {
	return lua_wrapfunction(L, glUniform4ui);
}
// Takes (location, count, value)
static int uniform1uiv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform1uiv);
}
static int uniform2uiv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform2uiv);
}
static int uniform3uiv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform3uiv);
}
static int uniform4uiv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform4uiv);
}

// Specifies the value of a generic vertex attribute.
// Takes (index, v0, v1, v2, ...)
static int vertexAttribI1i(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribI1i);
}
static int vertexAttribI1ui(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribI1ui);
}
static int vertexAttribI2i(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribI2i);
}
static int vertexAttribI2ui(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribI2ui);
}
static int vertexAttribI3i(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribI3i);
}
static int vertexAttribI3ui(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribI3ui);
}
static int vertexAttribI4i(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribI4i);
}
static int vertexAttribI4ui(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribI4ui);
}
// Takes (index, v)
static int vertexAttribI1iv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI1iv);
}
static int vertexAttribI1uiv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI1uiv);
}
static int vertexAttribI2iv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI2iv);
}
static int vertexAttribI2uiv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI2uiv);
}
static int vertexAttribI3iv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI3iv);
}
static int vertexAttribI3uiv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI3uiv);
}
static int vertexAttribI4bv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI4bv);
}
static int vertexAttribI4ubv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI4ubv);
}
static int vertexAttribI4sv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI4sv);
}
static int vertexAttribI4usv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI4usv);
}
static int vertexAttribI4iv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI4iv);
}
static int vertexAttribI4uiv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI4uiv);
}
// Takes (index, type, normalized, value)
static int vertexAttribP1ui(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribP1ui);
}
static int vertexAttribP2ui(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribP2ui);
}
static int vertexAttribP3ui(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribP3ui);
}
static int vertexAttribP4ui(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribP4ui);
}

// Modify the rate at which generic vertex attributes advance during instanced rendering.
// Takes (index, divisor)
static int vertexAttribDivisor(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttribDivisor);
}
#endif

int olf::gl::registerLua30(lua_State* L) {
	const luaL_reg localLib[] = {
#ifdef GL_VERSION_3_0
		{"beginConditionalRender", beginConditionalRender},
		{"beginTransformFeedback", beginTransformFeedback},
		{"bindBufferBase", bindBufferBase},
		{"bindBufferRange", bindBufferRange},
		{"bindFragDataLocation", bindFragDataLocation},
		{"bindFramebuffer", bindFramebuffer},
		{"bindRenderbuffer", bindRenderbuffer},
		{"bindVertexArray", bindVertexArray},
		{"checkFramebufferStatus", checkFramebufferStatus},
		{"clampColor", clampColor},
		{"clearBufferiv", clearBufferiv},
		{"clearBufferuiv", clearBufferuiv},
		{"clearBufferfv", clearBufferfv},
		{"clearBufferfi", clearBufferfi},
		{"deleteFramebuffers", deleteFramebuffers},
		{"deleteRenderbuffers", deleteRenderbuffers},
		{"deleteVertexArrays", deleteVertexArrays},
		{"disablei", disablei},
		{"enablei", enablei},
		{"endConditionalRender", endConditionalRender},
		{"endTransformFeedback", endTransformFeedback},
		{"flushMappedBufferRange", flushMappedBufferRange},
		{"framebufferRenderbuffer", framebufferRenderbuffer},
		{"generateMipmap", generateMipmap},
		{"genFramebuffers", genFramebuffers},
		{"genRenderbuffers", genRenderbuffers},
		{"genVertexArrays", genVertexArrays},
		{"getFragDataIndex", getFragDataIndex},
		{"getFragDataLocation", getFragDataLocation},
		//{"getFramebufferAttachmentParameter", getFramebufferAttachmentParameter},
		{"getRenderbufferParameteriv", getRenderbufferParameteriv},
		{"getTransformFeedbackVarying", getTransformFeedbackVarying},
		{"isFramebuffer", isFramebuffer},
		{"isRenderbuffer", isRenderbuffer},
		{"isVertexArray", isVertexArray},
		{"renderbufferStorage", renderbufferStorage},
		{"renderbufferStorageMultisample", renderbufferStorageMultisample},
		{"sampleCoverage", sampleCoverage},
		{"transformFeedbackVaryings", transformFeedbackVaryings},
		{"vertexAttribIPointer", vertexAttribIPointer},
#endif
#ifdef GL_VERSION_3_1
		{"copyBufferSubData", copyBufferSubData},
		{"drawArraysInstanced", drawArraysInstanced},
		{"drawElementsInstanced", drawElementsInstanced},
		{"getActiveUniformBlockiv", getActiveUniformBlockiv},
		{"getActiveUniformBlockName", getActiveUniformBlockName},
		{"getUniformBlockIndex", getUniformBlockIndex},
		{"getUniformIndices", getUniformIndices},
		{"primitiveRestartIndex", primitiveRestartIndex},
		{"texBuffer", texBuffer},
		{"uniformBlockBinding", uniformBlockBinding},
#endif
#ifdef GL_VERSION_3_2
		{"drawElementsBaseVertex", drawElementsBaseVertex},
		{"drawElementsInstancedBaseVertex", drawElementsInstancedBaseVertex},
		{"drawRangeElementsBaseVertex", drawRangeElementsBaseVertex},
		{"framebufferTexture", framebufferTexture},
		{"framebufferTexture1D", framebufferTexture1D},
		{"framebufferTexture2D", framebufferTexture2D},
		{"framebufferTexture3D", framebufferTexture3D},
		{"framebufferTextureLayer", framebufferTextureLayer},
		{"getInteger64v", getInteger64v},
		{"getInteger64i_v", getInteger64i_v},
		{"getMultisamplefv", getMultisamplefv},
		{"provokingVertex", provokingVertex},
		{"queryCounter", queryCounter},
		{"sampleMaski", sampleMaski},
		{"texImage2DMultisample", texImage2DMultisample},
		{"texImage3DMultisample", texImage3DMultisample},
#endif
#ifdef GL_VERSION_3_3
		{"bindFragDataLocationIndexed", bindFragDataLocationIndexed},
		{"bindSampler", bindSampler},
		{"deleteSamplers", deleteSamplers},
		{"genSamplers", genSamplers},
		{"getFragDataIndex", getFragDataIndex},
		{"getQueryObjectiv", getQueryObjectiv},
		{"getQueryObjectuiv", getQueryObjectuiv},
		{"getQueryObjecti64v", getQueryObjecti64v},
		{"getQueryObjectui64v", getQueryObjectui64v},
		{"getSamplerParameterfv", getSamplerParameterfv},
		{"getSamplerParameteriv", getSamplerParameteriv},
		{"getVertexAttribIiv", getVertexAttribIiv},
		{"getVertexAttribIuiv", getVertexAttribIuiv},
		{"isEnabledi", isEnabledi},
		{"isSampler", isSampler},
		{"queryCounter", queryCounter},
		{"samplerParameterf", samplerParameterf},
		{"samplerParameteri", samplerParameteri},
		{"samplerParameterfv", samplerParameterfv},
		{"samplerParameteriv", samplerParameteriv},
		{"texParameterIiv", texParameterIiv},
		{"texParameterIuiv", texParameterIuiv},
		{"uniform1ui", uniform1ui},
		{"uniform2ui", uniform2ui},
		{"uniform3ui", uniform3ui},
		{"uniform4ui", uniform4ui},
		{"uniform1uiv", uniform1uiv},
		{"uniform2uiv", uniform2uiv},
		{"uniform3uiv", uniform3uiv},
		{"uniform4uiv", uniform4uiv},
		{"vertexAttribI1i", vertexAttribI1i},
		{"vertexAttribI1ui", vertexAttribI1ui},
		{"vertexAttribI2i", vertexAttribI2i},
		{"vertexAttribI2ui", vertexAttribI2ui},
		{"vertexAttribI3i", vertexAttribI3i},
		{"vertexAttribI3ui", vertexAttribI3ui},
		{"vertexAttribI4i", vertexAttribI4i},
		{"vertexAttribI4ui", vertexAttribI4ui},
		{"vertexAttribI1iv", vertexAttribI1iv},
		{"vertexAttribI1uiv", vertexAttribI1uiv},
		{"vertexAttribI2iv", vertexAttribI2iv},
		{"vertexAttribI2uiv", vertexAttribI2uiv},
		{"vertexAttribI3iv", vertexAttribI3iv},
		{"vertexAttribI3uiv", vertexAttribI3uiv},
		{"vertexAttribI4bv", vertexAttribI4bv},
		{"vertexAttribI4ubv", vertexAttribI4ubv},
		{"vertexAttribI4sv", vertexAttribI4sv},
		{"vertexAttribI4usv", vertexAttribI4usv},
		{"vertexAttribI4iv", vertexAttribI4iv},
		{"vertexAttribI4uiv", vertexAttribI4uiv},
		{"vertexAttribP1ui", vertexAttribP1ui},
		{"vertexAttribP2ui", vertexAttribP2ui},
		{"vertexAttribP3ui", vertexAttribP3ui},
		{"vertexAttribP4ui", vertexAttribP4ui},
		{"vertexAttribDivisor", vertexAttribDivisor},
#endif
		{NULL, NULL}
	};
	luaL_register(L, "gl", localLib);

	return 1;
}
