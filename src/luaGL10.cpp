#include "luaGL10.h"

#include <GL/glew.h>
#include "olua.h"

#include <cstdlib>

// Clear buffers to preset values.
// Takes (bufferBit1, bufferBit2, ...)
static int clear(lua_State* L) {
	int args = lua_gettop(L);
	GLbitfield mask = 0u;
	for (int i = 1; i <= args; ++i)
		mask = mask | lua_tocast<GLenum>(L, i);
	glClear(mask);
	return 0;
}

// Return a texture image.
// Takes (target, level, format, type, size) Returns (img)
static int getTexImage(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto format = lua_tocast<GLenum>(L, 3);
	auto type = lua_tocast<GLenum>(L, 4);
	auto size = lua_tocast<GLsizei>(L, 5);
	auto img = new lua_Number[size];
	glGetTexImage(target, level, format, type, img);
	lua_pusharray(L, img, size, true);
	return 1;
}

// Read a block of pixels from the frame buffer.
// Takes (x, y, width, height, format, type) Returns (data)
static int readPixels(lua_State* L) {
	auto x = lua_tocast<GLint>(L, 1);
	auto y = lua_tocast<GLint>(L, 2);
	auto width = lua_tocast<GLsizei>(L, 3);
	auto height = lua_tocast<GLsizei>(L, 4);
	auto format = lua_tocast<GLenum>(L, 5);
	auto type = lua_tocast<GLenum>(L, 6);
	GLuint size = width * height;
	if (format == GL_RGB || format == GL_BGR)
		size *= 3;
	else if (format == GL_RGBA || format == GL_BGRA)
		size *= 4;
	lua_Number* data = new lua_Number[size];
	glReadPixels(x, y, width, height, format, type, data);
	lua_newtable(L);
	for (unsigned int i = 0; i < size; ++i) {
		lua_pushtablekeyvalue(L, i + 1, data[i]);
	}
	delete [] data;
	return 1;
}

// Specify a one-dimensional texture image.
// Takes (target, level, internalFormat, width, border, format, type, data)
static int texImage1D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto internalFormat = lua_tocast<GLint>(L, 3);
	auto width = lua_tocast<GLsizei>(L, 4);
	auto border = lua_tocast<GLint>(L, 5);
	auto format = lua_tocast<GLenum>(L, 6);
	auto type = lua_tocast<GLenum>(L, 7);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 8, type, size);
	glTexImage1D(target, level, internalFormat, width, border, format, type, data);
	delete [] data;
	return 0;
}

// Specify a two-dimensional texture image.
// Takes (target, level, internalFormat, width, height, border, format, type, data)
static int texImage2D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto internalFormat = lua_tocast<GLint>(L, 3);
	auto width = lua_tocast<GLsizei>(L, 4);
	auto height = lua_tocast<GLsizei>(L, 5);
	auto border = lua_tocast<GLint>(L, 6);
	auto format = lua_tocast<GLenum>(L, 7);
	auto type = lua_tocast<GLenum>(L, 8);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 9, type, size);
	glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
	delete [] data;
	return 0;
}

// Specify a one-dimensional texture subimage.
// Takes (target, level, xoffset, width, format, type, data)
static int texSubImage1D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto xoffset = lua_tocast<GLint>(L, 3);
	auto width = lua_tocast<GLsizei>(L, 4);
	auto format = lua_tocast<GLenum>(L, 5);
	auto type = lua_tocast<GLenum>(L, 6);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 7, type, size);
	glTexSubImage1D(target, level, xoffset, width, format, type, data);
	delete [] data;
	return 0;
}

// Specify a two-dimensional texture subimage.
// Takes (target, level, xoffset, yoffset, width, height, format, type, data)
static int texSubImage2D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto xoffset = lua_tocast<GLint>(L, 3);
	auto yoffset = lua_tocast<GLint>(L, 4);
	auto width = lua_tocast<GLsizei>(L, 5);
	auto height = lua_tocast<GLsizei>(L, 6);
	auto format = lua_tocast<GLenum>(L, 7);
	auto type = lua_tocast<GLenum>(L, 8);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 9, type, size);
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, data);
	delete [] data;
	return 0;
}

#ifdef GL_VERSION_1_1

// Render primitives from array data.
// Takes (mode, count, type, indices)
static int drawElements(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto count = lua_tocast<GLsizei>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	auto indices = lua_tabletoglarray(L, 4, type);
	glDrawElements(mode, count, type, indices);
	delete [] indices;
	return 0;
}

// Generate texture names.
// Takes (n) Returns (obj1, obj2, obj3, ...)
static int genTextures(lua_State* L) {
	return lua_wrapgenfunction(L, glGenTextures);
}

// Determine if a name corresponds to a texture.
// Takes (texture) Returns (boolean)
static int isTexture(lua_State* L) {
	return lua_wrapfunction(L, glIsTexture);
}
#endif

#ifdef GL_VERSION_1_2
// Render primitives from array data.
// Takes (mode, start, end, count, type, indices)
static int drawRangeElements(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto start = lua_tocast<GLuint>(L, 2);
	auto end = lua_tocast<GLuint>(L, 3);
	auto count = lua_tocast<GLsizei>(L, 4);
	auto type = lua_tocast<GLenum>(L, 5);
	auto indices = lua_tabletoglarray(L, 6, type);
	glDrawRangeElements(mode, start, end, count, type, indices);
	delete [] indices;
	return 0;
}

// Specify a three-dimensional texture image.
// Takes (target, level, internalFormat, width, height, depth, border, format, type, data)
static int texImage3D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto internalFormat = lua_tocast<GLint>(L, 3);
	auto width = lua_tocast<GLsizei>(L, 4);
	auto height = lua_tocast<GLsizei>(L, 5);
	auto depth = lua_tocast<GLsizei>(L, 6);
	auto border = lua_tocast<GLint>(L, 7);
	auto format = lua_tocast<GLenum>(L, 8);
	auto type = lua_tocast<GLenum>(L, 9);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 10, type, size);
	glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, data);
	delete [] data;
	return 0;
}

// Specify a three-dimensional texture subimage.
// Takes (target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data)
static int texSubImage3D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto xoffset = lua_tocast<GLint>(L, 3);
	auto yoffset = lua_tocast<GLint>(L, 4);
	auto zoffset = lua_tocast<GLint>(L, 5);
	auto width = lua_tocast<GLsizei>(L, 6);
	auto height = lua_tocast<GLsizei>(L, 7);
	auto depth = lua_tocast<GLsizei>(L, 8);
	auto format = lua_tocast<GLenum>(L, 9);
	auto type = lua_tocast<GLenum>(L, 10);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 11, type, size);
	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
	delete [] data;
	return 0;
}
#endif

#ifdef GL_VERSION_1_3
// Specify a one-dimensional texture image in a compressed format.
// Takes (target, level, internalFormat, width, border, type, data)
static int compressedTexImage1D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto internalFormat = lua_tocast<GLint>(L, 3);
	auto width = lua_tocast<GLsizei>(L, 4);
	auto border = lua_tocast<GLint>(L, 5);
	auto type = lua_tocast<GLenum>(L, 6);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 7, type, size);
	glCompressedTexImage1D(target, level, internalFormat, width, border, size, data);
	delete [] data;
	return 0;
}

// Specify a two-dimensional texture image in a compressed format.
// Takes (target, level, internalFormat, width, height, border, type, data)
static int compressedTexImage2D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto internalFormat = lua_tocast<GLint>(L, 3);
	auto width = lua_tocast<GLsizei>(L, 4);
	auto height = lua_tocast<GLsizei>(L, 5);
	auto border = lua_tocast<GLint>(L, 6);
	auto type = lua_tocast<GLenum>(L, 7);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 8, type, size);
	glCompressedTexImage2D(target, level, internalFormat, width, height, border, size, data);
	delete [] data;
	return 0;
}

// Specify a three-dimensional texture image in a compressed format.
// Takes (target, level, internalFormat, width, height, depth, border, type, data)
static int compressedTexImage3D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto internalFormat = lua_tocast<GLint>(L, 3);
	auto width = lua_tocast<GLsizei>(L, 4);
	auto height = lua_tocast<GLsizei>(L, 5);
	auto depth = lua_tocast<GLsizei>(L, 6);
	auto border = lua_tocast<GLint>(L, 7);
	auto type = lua_tocast<GLenum>(L, 8);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 9, type, size);
	glCompressedTexImage3D(target, level, internalFormat, width, height, depth, border, size, data);
	delete [] data;
	return 0;
}

// Specify a one-dimensional texture subimage in a compressed format.
// Takes (target, level, xoffset, width, format, type, data)
static int compressedTexSubImage1D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto xoffset = lua_tocast<GLint>(L, 3);
	auto width = lua_tocast<GLsizei>(L, 4);
	auto format = lua_tocast<GLenum>(L, 5);
	auto type = lua_tocast<GLenum>(L, 6);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 7, type, size);
	glCompressedTexSubImage1D(target, level, xoffset, width, format, size, data);
	delete [] data;
	return 0;
}

// Specify a two-dimensional texture subimage in a compressed format.
// Takes (target, level, xoffset, yoffset, width, height, format, type, data)
static int compressedTexSubImage2D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto xoffset = lua_tocast<GLint>(L, 3);
	auto yoffset = lua_tocast<GLint>(L, 4);
	auto width = lua_tocast<GLsizei>(L, 5);
	auto height = lua_tocast<GLsizei>(L, 6);
	auto format = lua_tocast<GLenum>(L, 7);
	auto type = lua_tocast<GLenum>(L, 8);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 9, type, size);
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, size, data);
	delete [] data;
	return 0;
}

// Specify a three-dimensional texture subimage in a compressed format.
// Takes (target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data)
static int compressedTexSubImage3D(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto level = lua_tocast<GLint>(L, 2);
	auto xoffset = lua_tocast<GLint>(L, 3);
	auto yoffset = lua_tocast<GLint>(L, 4);
	auto zoffset = lua_tocast<GLint>(L, 5);
	auto width = lua_tocast<GLsizei>(L, 6);
	auto height = lua_tocast<GLsizei>(L, 7);
	auto depth = lua_tocast<GLsizei>(L, 8);
	auto format = lua_tocast<GLenum>(L, 9);
	auto type = lua_tocast<GLenum>(L, 10);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 11, type, size);
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, size, data);
	delete [] data;
	return 0;
}

// Return a compressed texture image.
// Takes (target, lod, count) Return (img)
static int getCompressedTexImage(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto lod = lua_tocast<GLint>(L, 2);
	auto size = lua_tocast<GLsizeiptr>(L, 3);
	auto count = lua_tocast<GLuint>(L, 4);
	auto img = malloc(size);
	glGetCompressedTexImage(target, lod, img);
	lua_pusharray(L, static_cast<unsigned char*>(img), count);
	free(img);
	return 1;
}

#endif

#ifdef GL_VERSION_1_4
// Specify pixel arithmetic for RGB and alpha components separately.
// Takes (srcRGB, dstRGB, srcAlpha, dstAlpha)
static int blendFuncSeparate(lua_State* L) {
	return lua_wrapfunction(L, glBlendFuncSeparate);
}

// Render multiple sets of primitives from array data.
// Takes (mode, firstTable, countTable, primcount)
static int multiDrawArrays(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto first = lua_tabletobasicarray<GLsizei>(L, 2);
	auto count = lua_tabletobasicarray<GLsizei>(L, 3);
	auto primcount = lua_tocast<GLsizei>(L, 4);
	glMultiDrawArrays(mode, first, count, primcount);
	delete [] first;
	delete [] count;
	return 0;
}

// Render multiple sets of primitives by specifying indices of array data elements.
// Takes (mode, countTable, type, indicesTable, primcount)
// Nested tables :'(
/*static int olf::gl::multiDrawElements(lua_State* L) {
	auto mode = lua_tocast<GLenum>(L, 1);
	auto count = lua_tabletobasicarray<GLsizei>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	auto count = lua_tabletonestedarray<void*>(L, 2);
	auto primcount = lua_tocast<GLsizei>(L, 5);
	
	return 0;
}*/

// Specify point parameters.
// Takes (pname, param)
static int pointParameterf(lua_State* L) {
	return lua_wrapfunction(L, glPointParameterf);
}
static int pointParameteri(lua_State* L) {
	return lua_wrapfunction(L, glPointParameteri);
}
#endif

#ifdef GL_VERSION_1_5
// Delimit the boundaries of a query object.
// Takes (target, id)
static int beginQuery(lua_State* L) {
	return lua_wrapfunction(L, glBeginQuery);
}

// Binds a buffer object to the specified buffer binding point.
// Takes (target, buffer)
static int bindBuffer(lua_State* L) {
	return lua_wrapfunction(L, glBindBuffer);
}

// Creates and initializes a buffer object's data store.
// Takes (target, type, data, usage)
static int bufferData(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto type = lua_tocast<GLenum>(L, 2);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 3, type, size);
	auto usage = lua_tocast<GLenum>(L, 4);
	glBufferData(target, size, data, usage);
	delete [] data;
	return 0;
}

// Updates a subset of a buffer object's data store.
// Takes (target, offset, type, data)
static int bufferSubData(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto offset = lua_tocast<GLintptr>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 4, type, size);
	glBufferSubData(target, offset, size, data);
	delete [] data;
	return 0;
}

// Delete named buffer objects.
// Takes (buffer1, buffer2, buffer3, ...)
static int deleteBuffers(lua_State* L) {
	return lua_wraploopfunction(L, glDeleteBuffers);
}

// Delete named query objects.
// Takes (id1, id2, id3, ...)
static int deleteQueries(lua_State* L) {
	return lua_wraploopfunction(L, glDeleteQueries);
}

// Delete named textures.
// Takes (texture1, texture2, texture3, ...)
static int deleteTextures(lua_State* L) {
	return lua_wraploopfunction(L, glDeleteTextures);
}

// End query object.
// Takes (target)
static int endQuery(lua_State* L) {
	return lua_wrapfunction(L, glEndQuery);
}

// Generate buffer object names.
// Takes (n) Returns (obj1, obj2, obj3, ...)
static int genBuffers(lua_State* L) {
	return lua_wrapgenfunction(L, glGenBuffers);
}

// Generate query object names.
// Takes (n) Returns (obj1, obj2, obj3, ...)
static int genQueries(lua_State* L) {
	return lua_wrapgenfunction(L, glGenQueries);
}

// Return parameters of a buffer object.
// Takes (target, value) Returns (data);
static int getBufferParameteriv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetBufferParameteriv);
}

// Return the pointer to a mapped buffer object's data store.
// Takes (target, pname) Returns (pointer)
static int getBufferPointerv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetBufferPointerv);
}

// Returns a subset of a buffer object's data store.
// Takes (target, offset, size, count) Return (data)
/*static int getBufferSubData(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto offset = lua_tocast<GLintptr>(L, 2);
	auto size = lua_tocast<GLsizeiptr>(L, 3);
	auto count = lua_tocast<GLuint>(L, 4);
	GLvoid* data = malloc(size);
	glGetBufferSubData(target, offset, size, data);
	lua_pusharray(L, data, count);
	free(data);
	return 1;
}*/

// Return parameters of a query object target.
// Takes (target, pname, count) Returns (params)
static int getQueryiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetQueryiv);
}

// Determine if a name corresponds to a buffer object.
// Takes (buffer) Returns (boolean)
static int isBuffer(lua_State* L) {
	return lua_wrapfunction(L, glIsBuffer);
}

// Determine if a name corresponds to a query object.
// Takes (id) Returns (boolean)
static int isQuery(lua_State* L) {
	return lua_wrapfunction(L, glIsQuery);
}

// Map a buffer object's data store.
// IDK how to make this work :S
//static int mapBuffer(lua_State* L);

// Map check
// Takes (target) Returns (valid)
static int unmapBuffer(lua_State* L) {
	return lua_wrapfunction(L, glUnmapBuffer);
}
#endif

int olf::gl::registerLua10(lua_State* L) {
	const luaL_reg localLib[] = {
		{"blendColor", LUA_FULL_WRAP(glBlendColor)},
		{"blendEquation", LUA_FULL_WRAP(glBlendEquation)},
		{"blendFunc", LUA_FULL_WRAP(glBlendFunc)},
		{"clear", clear},
		{"clearColor", LUA_FULL_WRAP(glClearColor)},
		{"clearDepth", LUA_FULL_WRAP(glClearDepth)},
		{"clearStencil", LUA_FULL_WRAP(glClearStencil)},
		{"colorMask", LUA_FULL_WRAP(glColorMask)},
		{"copyTexImage1D", LUA_FULL_WRAP(glCopyTexImage1D)},
		{"copyTexImage2D", LUA_FULL_WRAP(glCopyTexImage2D)},
		{"copyTexSubImage1D", LUA_FULL_WRAP(glCopyTexSubImage1D)},
		{"copyTexSubImage2D", LUA_FULL_WRAP(glCopyTexSubImage2D)},
		{"cullFace", LUA_FULL_WRAP(glCullFace)},
		{"depthFunc", LUA_FULL_WRAP(glDepthFunc)},
		{"depthMask", LUA_FULL_WRAP(glDepthMask)},
		{"depthRange", LUA_FULL_WRAP(glDepthRange)},
		{"disable", LUA_FULL_WRAP(glDisable)},
		{"drawBuffer", LUA_FULL_WRAP(glDrawBuffer)},
		{"enable", LUA_FULL_WRAP(glEnable)},
		{"finish", LUA_FULL_WRAP(glFinish)},
		{"flush", LUA_FULL_WRAP(glFlush)},
		{"frontFace", LUA_FULL_WRAP(glFrontFace)},
		{"getBooleanv", LUA_FULL_WRAP_GET(glGetBooleanv)},
		{"getDoublev", LUA_FULL_WRAP_GET(glGetDoublev)},
		{"getFloatv", LUA_FULL_WRAP_GET(glGetFloatv)},
		{"getIntegerv", LUA_FULL_WRAP_GET(glGetIntegerv)},
		{"getBooleani_v", LUA_FULL_WRAP_GET(glGetBooleani_v)},
		{"getIntegeri_v", LUA_FULL_WRAP_GET(glGetIntegeri_v)},
		{"getError", LUA_FULL_WRAP(glGetError)},
		{"getString", LUA_FULL_WRAP(glGetString)},
		{"getStringi", LUA_FULL_WRAP(glGetStringi)},
		{"getTexImage", getTexImage},
		{"getTexLevelParameterfv", LUA_FULL_WRAP_GET(glGetTexLevelParameterfv)},
		{"getTexLevelParameteriv", LUA_FULL_WRAP_GET(glGetTexLevelParameteriv)},
		{"getTexParameterfv", LUA_FULL_WRAP_GET(glGetTexParameterfv)},
		{"getTexParameteriv", LUA_FULL_WRAP_GET(glGetTexParameteriv)},
		{"hint", LUA_FULL_WRAP(glHint)},
		{"isEnabled", LUA_FULL_WRAP(glIsEnabled)},
		{"lineWidth", LUA_FULL_WRAP(glLineWidth)},
		{"logicOp", LUA_FULL_WRAP(glLogicOp)},
		{"pixelStoref", LUA_FULL_WRAP(glPixelStoref)},
		{"pixelStorei", LUA_FULL_WRAP(glPixelStorei)},
		{"pointSize", LUA_FULL_WRAP(glPointSize)},
		{"polygonMode", LUA_FULL_WRAP(glPolygonMode)},
		{"polygonOffset", LUA_FULL_WRAP(glPolygonOffset)},
		{"readBuffer", LUA_FULL_WRAP(glReadBuffer)},
		{"readPixels", readPixels},
		{"scissor", LUA_FULL_WRAP(glScissor)},
		{"stencilFunc", LUA_FULL_WRAP(glStencilFunc)},
		{"stencilMask", LUA_FULL_WRAP(glStencilMask)},
		{"stencilOp", LUA_FULL_WRAP(glStencilOp)},
		{"texImage1D", texImage1D},
		{"texImage2D", texImage2D},
		{"texParameterf", LUA_FULL_WRAP(glTexParameterf)},
		{"texParameteri", LUA_FULL_WRAP(glTexParameteri)},
		{"texParameterfv", LUA_FULL_WRAP_ARRAY(glTexParameterfv)},
		{"texParameteriv", LUA_FULL_WRAP_ARRAY(glTexParameteriv)},
		{"texSubImage1D", texSubImage1D},
		{"texSubImage2D", texSubImage2D},
		{"viewport", LUA_FULL_WRAP(glViewport)},
#ifdef GL_VERSION_1_1
		{"activeTexture", LUA_FULL_WRAP(glActiveTexture)},
		{"bindTexture", LUA_FULL_WRAP(glBindTexture)},
		{"copyTexSubImage3D", LUA_FULL_WRAP(glCopyTexSubImage3D)},
		{"drawArrays", LUA_FULL_WRAP(glDrawArrays)},

		{"drawElements", drawElements},
		{"genTextures", genTextures},
		{"isTexture", isTexture},
#endif
#ifdef GL_VERSION_1_2
		{"drawRangeElements", drawRangeElements},
		{"texImage3D", texImage3D},
		{"texSubImage3D", texSubImage3D},
#endif
#ifdef GL_VERSION_1_3
		{"compressedTexImage1D", compressedTexImage1D},
		{"compressedTexImage2D", compressedTexImage2D},
		{"compressedTexImage3D", compressedTexImage3D},
		{"compressedTexSubImage1D", compressedTexSubImage1D},
		{"compressedTexSubImage2D", compressedTexSubImage2D},
		{"compressedTexSubImage3D", compressedTexSubImage3D},
		{"getCompressedTexImage", getCompressedTexImage},
#endif
#ifdef GL_VERSION_1_4
		{"blendFuncSeparate", blendFuncSeparate},
		{"multiDrawArrays", multiDrawArrays},
		{"pointParameterf", pointParameterf},
		{"pointParameteri", pointParameteri},
#endif
#ifdef GL_VERSION_1_5
		{"beginQuery", beginQuery},
		{"bindBuffer", bindBuffer},
		{"bufferData", bufferData},
		{"bufferSubData", bufferSubData},
		{"deleteBuffers", deleteBuffers},
		{"deleteQueries", deleteQueries},
		{"deleteTextures", deleteTextures},
		{"endQuery", endQuery},
		{"genBuffers", genBuffers},
		{"genQueries", genQueries},
		{"getBufferParameteriv", getBufferParameteriv},
		{"getBufferPointerv", getBufferPointerv},
		{"getQueryiv", getQueryiv},
		{"isBuffer", isBuffer},
		{"isQuery", isQuery},
		{"unmapBuffer", unmapBuffer},
		{"unmapBuffer", unmapBuffer},
		//{"getBufferSubData", getBufferSubData},
#endif
		{NULL, NULL}
	};
	luaL_register(L, "gl", localLib);

	return 1;
}
