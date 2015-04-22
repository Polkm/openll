#include "luaGL20.h"

#include <GL/glew.h>
#include "olua.h"

#ifdef GL_VERSION_2_0
// Attaches a shader object to a program object.
// Takes (program, shader)
static int attachShader(lua_State* L) {
	return lua_wrapfunction(L, glAttachShader);
}

// Associates a generic vertex attribute index with a named attribute variable.
// Takes (program, index, name)
static int bindAttribLocation(lua_State* L) {
	return lua_wrapfunction(L, glBindAttribLocation);
}

// Set the RGB blend equation and the alpha blend equation separately.
// Takes (modeRGB, modeAlpha)
static int blendEquationSeparate(lua_State* L) {
	return lua_wrapfunction(L, glBlendEquationSeparate);
}

// Compiles a shader object.
// Takes (shader)
static int compileShader(lua_State* L) {
	return lua_wrapfunction(L, glCompileShader);
}

// Creates a program object.
// Returns (programName)
static int createProgram(lua_State* L) {
	return lua_wrapfunction(L, glCreateProgram);
}

// Creates a shader object.
// Takes (shaderType)
static int createShader(lua_State* L) {
	return lua_wrapfunction(L, glCreateShader);
}

// Deletes a program object.
// Takes (program)
static int deleteProgram(lua_State* L) {
	return lua_wrapfunction(L, glDeleteProgram);
}

// Deletes a shader object.
// Takes (shader)
static int deleteShader(lua_State* L) {
	return lua_wrapfunction(L, glDeleteShader);
}

// Detaches a shader object from a program object to which it is attached.
static int detachShader(lua_State* L) {
	return lua_wrapfunction(L, glDetachShader);
}

// Disable a generic vertex attribute array.
// Takes (index)
static int disableVertexAttribArray(lua_State* L) {
	return lua_wrapfunction(L, glDisableVertexAttribArray);
}

// Specifies a list of color buffers to be drawn into.
// Takes (buf1, buf2, buf3, ...)
static int drawBuffers(lua_State* L) {
	return lua_wraploopfunction(L, glDrawBuffers);
}

// Enable a generic vertex attribute array.
// Takes (index)
static int enableVertexAttribArray(lua_State* L) {
	return lua_wrapfunction(L, glEnableVertexAttribArray);
}

// Returns information about an active attribute variable for the specified program object.
// Takes (program, index, bufSize) Returns (length, size, type, name)
static int getActiveAttrib(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto index = lua_tocast<GLuint>(L, 2);
	auto bufSize = lua_tocast<GLsizei>(L, 3);
	GLsizei length;
	GLint size;
	GLenum type;
	auto name = new char[bufSize];
	glGetActiveAttrib(program, index, bufSize, &length, &size, &type, name);
	lua_push(L, length);
	lua_push(L, size);
	lua_push(L, type);
	lua_push(L, name);
	delete [] name;
	return 4;
}

// Returns information about an active uniform variable for the specified program object.
// Takes (program, index, bufSize) Returns (name, type, size, length)
static int getActiveUniform(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto index = lua_tocast<GLuint>(L, 2);
	auto bufSize = lua_tocast<GLsizei>(L, 3);
	GLsizei length;
	GLint size;
	GLenum type;
	auto name = new char[bufSize];
	glGetActiveUniform(program, index, bufSize, &length, &size, &type, name);
	lua_push(L, name);
	lua_push(L, type);
	lua_push(L, size);
	lua_push(L, length);
	delete [] name;
	return 4;
}

// Query the name of an active uniform.
// Takes (program, uniformIndex, bufSize) Returns (uniformName, length)
static int getActiveUniformName(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto uniformIndex = lua_tocast<GLuint>(L, 2);
	auto bufSize = lua_tocast<GLsizei>(L, 3);
	GLsizei length;
	auto uniformName = new char[bufSize];
	glGetActiveUniformName(program, uniformIndex, bufSize, &length, uniformName);
	lua_push(L, uniformName);
	lua_push(L, length);
	delete [] uniformName;
	return 2;
}

// Returns information about several active uniform variables for the specified program object.
// Takes (program, uniformCount, uniformIndices, pname) Returns (params)
static int getActiveUniformsiv(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto uniformCount = lua_tocast<GLsizei>(L, 2);
	auto uniformIndices = lua_tabletobasicarray<GLuint>(L, 3);
	auto pname = lua_tocast<GLenum>(L, 4);
	auto params = new GLint[uniformCount];
	glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
	lua_pusharray(L, params, uniformCount, true);
	return 1;
}

// Returns the handles of the shader objects attached to a program object.
// Takes (program, maxCount) Return (shaders)
static int getAttachedShaders(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto maxCount = lua_tocast<GLsizei>(L, 2);
	GLsizei count;
	auto shaders = new GLuint[maxCount];
	glGetAttachedShaders(program, maxCount, &count, shaders);
	lua_pusharray(L, shaders, count, true);
	return 1;
}

// Returns the location of an attribute variable.
// Takes (program, name) Returns (location)
static int getAttribLocation(lua_State* L) {
	return lua_wrapfunction(L, glGetAttribLocation);
}

// Returns a parameter from a program object.
// Takes (program, pname, count) Returns (params)
static int getProgramiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetProgramiv);
}

// Returns the information log for a program object.
// Takes (program, maxLength) Returns (infoLog, length);
static int getProgramInfoLog(lua_State* L) {
	auto program = lua_tocast<GLuint>(L, 1);
	auto maxLength = lua_tocast<GLsizei>(L, 2);
	GLsizei length;
	auto infoLog = new GLchar[maxLength];
	glGetProgramInfoLog(program, maxLength, &length, infoLog);
	lua_push(L, infoLog);
	lua_push(L, length);
	delete [] infoLog;
	return 2;
}

// Returns a parameter from a shader object.
// Takes (shader, pname, count) Returns (params)
static int getShaderiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetShaderiv);
}

// Returns the information log for a shader object.
// Takes (shader, maxLength) Returns (infoLog, length)
static int getShaderInfoLog(lua_State* L) {
	auto shader = lua_tocast<GLuint>(L, 1);
	auto maxLength = lua_tocast<GLsizei>(L, 2);
	GLsizei length;
	auto infoLog = new GLchar[maxLength];
	glGetShaderInfoLog(shader, maxLength, &length, infoLog);
	lua_push(L, infoLog);
	lua_push(L, length);
	delete [] infoLog;
	return 2;
}

// Returns the source code string from a shader object.
// Takes (shader, bufSize) Returns (infoLog, length)
static int getShaderSource(lua_State* L) {
	auto shader = lua_tocast<GLuint>(L, 1);
	auto bufSize = lua_tocast<GLsizei>(L, 2);
	GLsizei length;
	auto source = new GLchar[bufSize];
	glGetShaderSource(shader, bufSize, &length, source);
	lua_push(L, source);
	lua_push(L, length);
	delete [] source;
	return 2;
}

// Returns the value of a uniform variable.
// Takes (program, location, count) Returns (params)
static int getUniformfv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetUniformfv);
}
static int getUniformiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetUniformiv);
}

// Returns the location of a uniform variable.
// Takes (program, name) Returns (location)
static int getUniformLocation(lua_State* L) {
	return lua_wrapfunction(L, glGetUniformLocation);
}

// Return a generic vertex attribute parameter.
// Takes (index, pname, count) Returns (params)
static int getVertexAttribdv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetVertexAttribdv);
}
static int getVertexAttribfv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetVertexAttribfv);
}
static int getVertexAttribiv(lua_State* L) {
	return lua_wrapgetfunction(L, glGetVertexAttribiv);
}

// Disabled until good solution comes up
// Return the address of the specified generic vertex attribute pointer.
// Takes (index, pname, size, count) Returns (pointerTable)
/*static int getVertexAttribPointerv(lua_State* L) {
	auto index = lua_tocast<GLuint>(L, 1);
	auto pname = lua_tocast<GLenum>(L, 2);
	auto size = lua_tocast<size_t>(L, 3);
	auto count = lua_tocast<GLuint>(L, 4);
}*/

// Determines if a name corresponds to a program object.
// Takes (program) Returns (boolean)
static int isProgram(lua_State* L) {
	return lua_wrapfunction(L, glIsProgram);
}

// Determines if a name corresponds to a shader object.
// Takes (shader) Returns (boolean)
static int isShader(lua_State* L) {
	return lua_wrapfunction(L, glIsShader);
}

// Links a program object.
// Takes (program)
static int linkProgram(lua_State* L) {
	return lua_wrapfunction(L, glLinkProgram);
}

// Replaces the source code in a shader object.
// Takes (shader, string)
static int shaderSource(lua_State* L) {
	auto shader = lua_tocast<GLuint>(L, 1);
	if (lua_istable(L, 2)) {
		GLsizei count = luaL_getn(L, 2);
		int* lengths = new int[count];
		const GLchar** strings = lua_tabletolstringarray(L, 2, lengths);
		glShaderSource(shader, count, strings, lengths);
		delete [] strings;
		delete [] lengths;
	} else {
		auto string = lua_tostring(L, 2);
		int length = strlen(string);
		glShaderSource(shader, 1, &string, &length);
	}
	return 0;
}

// Set front and/or back function and reference value for stencil testing.
// Takes (face, func, ref, mask)
static int stencilFuncSeparate(lua_State* L) {
	return lua_wrapfunction(L, glStencilFuncSeparate);
}

// Control the front and/or back writing of individual bits in the stencil planes.
// Takes (face, mask)
static int stencilMaskSeparate(lua_State* L) {
	return lua_wrapfunction(L, glStencilMaskSeparate);
}

// Set front and/or back stencil test actions.
// Takes (sfail, dpfail, dppass)
static int stencilOpSeparate(lua_State* L) {
	return lua_wrapfunction(L, glStencilOpSeparate);
}

// Specify the value of a uniform variable for the current program object.
// Takes (location, v0, v1, v2, ...)
static int uniform1f(lua_State* L) {
	return lua_wrapfunction(L, glUniform1f);
}
static int uniform2f(lua_State* L) {
	return lua_wrapfunction(L, glUniform2f);
}
static int uniform3f(lua_State* L) {
	return lua_wrapfunction(L, glUniform3f);
}
static int uniform4f(lua_State* L) {
	return lua_wrapfunction(L, glUniform4f);
}
static int uniform1i(lua_State* L) {
	return lua_wrapfunction(L, glUniform1i);
}
static int uniform2i(lua_State* L) {
	return lua_wrapfunction(L, glUniform2i);
}
static int uniform3i(lua_State* L) {
	return lua_wrapfunction(L, glUniform3i);
}
static int uniform4i(lua_State* L) {
	return lua_wrapfunction(L, glUniform4i);
}
// Takes (location, count, value)
static int uniform1fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform1fv);
}
static int uniform2fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform2fv);
}
static int uniform3fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform3fv);
}
static int uniform4fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform4fv);
}
static int uniform1iv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform1iv);
}
static int uniform2iv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform2iv);
}
static int uniform3iv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform3iv);
}
static int uniform4iv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniform4iv);
}
// Takes (location, count, transpose, value)
static int uniformMatrix2fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniformMatrix2fv);
}
static int uniformMatrix3fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniformMatrix3fv);
}
static int uniformMatrix4fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniformMatrix4fv);
}
static int uniformMatrix2x3fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniformMatrix2x3fv);
}
static int uniformMatrix3x2fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniformMatrix3x2fv);
}
static int uniformMatrix2x4fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniformMatrix2x4fv);
}
static int uniformMatrix4x2fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniformMatrix4x2fv);
}
static int uniformMatrix3x4fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniformMatrix3x4fv);
}
static int uniformMatrix4x3fv(lua_State* L) {
	return lua_wraparrayfunction(L, glUniformMatrix4x3fv);
}

// Installs a program object as part of current rendering state.
// Takes (program)
static int useProgram(lua_State* L) {
	return lua_wrapfunction(L, glUseProgram);
}

// Validates a program object
// Takes (program)
static int validateProgram(lua_State* L) {
	return lua_wrapfunction(L, glValidateProgram);
}

// Specifies the value of a generic vertex attribute.
// Takes (index, v0, v1, v2, ...)
static int vertexAttrib1f(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib1f);
}
static int vertexAttrib1s(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib1s);
}
static int vertexAttrib1d(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib1d);
}
static int vertexAttrib2f(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib2f);
}
static int vertexAttrib2s(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib2s);
}
static int vertexAttrib2d(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib2d);
}
static int vertexAttrib3f(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib3f);
}
static int vertexAttrib3s(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib3s);
}
static int vertexAttrib3d(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib3d);
}
static int vertexAttrib4f(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib4f);
}
static int vertexAttrib4s(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib4s);
}
static int vertexAttrib4d(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib4d);
}
static int vertexAttrib4Nub(lua_State* L) {
	return lua_wrapfunction(L, glVertexAttrib4Nub);
}
// Takes (index, v)
static int vertexAttrib1fv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib1fv);
}
static int vertexAttrib1sv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib1sv);
}
static int vertexAttrib1dv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib1dv);
}
static int vertexAttrib2fv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib2fv);
}
static int vertexAttrib2sv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib2sv);
}
static int vertexAttrib2dv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib2dv);
}
static int vertexAttrib3fv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib3fv);
}
static int vertexAttrib3sv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib3sv);
}
static int vertexAttrib3dv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib3dv);
}
static int vertexAttrib4fv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4fv);
}
static int vertexAttrib4sv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4sv);
}
static int vertexAttrib4dv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4dv);
}
static int vertexAttrib4iv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4iv);
}
static int vertexAttrib4bv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4bv);
}
static int vertexAttrib4ubv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4ubv);
}
static int vertexAttrib4usv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4usv);
}
static int vertexAttrib4uiv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttribI4uiv);
}
static int vertexAttrib4Nbv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4Nbv);
}
static int vertexAttrib4Nsv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4Nsv);
}
static int vertexAttrib4Niv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4Niv);
}
static int vertexAttrib4Nubv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4Nubv);
}
static int vertexAttrib4Nusv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4Nusv);
}
static int vertexAttrib4Nuiv(lua_State* L) {
	return lua_wraparrayfunction(L, glVertexAttrib4Nuiv);
}

// Define an array of generic vertex attribute data.
// Takes (index, size, type, normalized, stride, offset/data)
static int vertexAttribPointer(lua_State* L) {
	auto index = lua_tocast<GLuint>(L, 1);
	auto size = lua_tocast<GLint>(L, 2);
	auto type = lua_tocast<GLenum>(L, 3);
	auto normalized = lua_tocast<GLboolean>(L, 4);
	auto stride = lua_tocast<GLsizei>(L, 5);
	const GLvoid* pointer = 0;
	if (lua_istable(L, 6)) {
		GLsizeiptr size;
		pointer = lua_tabletoglarray(L, 6, type, size);
	} else {
		pointer = (GLvoid*)lua_tocast<GLsizei>(L, 6);
	}
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	return 0;
}
#endif

int olf::gl::registerLua20(lua_State* L) {
	const luaL_reg localLib[] = {
#ifdef GL_VERSION_2_0
		{"attachShader", attachShader},
		{"bindAttribLocation", bindAttribLocation},
		{"blendEquationSeparate", blendEquationSeparate},
		{"compileShader", compileShader},
		{"createProgram", createProgram},
		{"createShader", createShader},
		{"deleteProgram", deleteProgram},
		{"deleteShader", deleteShader},
		{"detachShader", detachShader},
		{"disableVertexAttribArray", disableVertexAttribArray},
		{"drawBuffers", drawBuffers},
		{"enableVertexAttribArray", enableVertexAttribArray},
		{"getActiveAttrib", getActiveAttrib},
		{"getActiveUniform", getActiveUniform},
		{"getActiveUniformName", getActiveUniformName},
		{"getActiveUniformsiv", getActiveUniformsiv},
		{"getAttachedShaders", getAttachedShaders},
		{"getAttribLocation", getAttribLocation},
		{"getProgramiv", getProgramiv},
		{"getProgramInfoLog", getProgramInfoLog},
		{"getShaderiv", getShaderiv},
		{"getShaderInfoLog", getShaderInfoLog},
		{"getShaderSource", getShaderSource},
		{"getUniformfv", getUniformfv},
		{"getUniformiv", getUniformiv},
		{"getUniformLocation", getUniformLocation},
		{"getVertexAttribdv", getVertexAttribdv},
		{"getVertexAttribfv", getVertexAttribfv},
		{"getVertexAttribiv", getVertexAttribiv},
		{"isProgram", isProgram},
		{"isShader", isShader},
		{"linkProgram", linkProgram},
		{"shaderSource", shaderSource},
		{"stencilFuncSeparate", stencilFuncSeparate},
		{"stencilMaskSeparate", stencilMaskSeparate},
		{"stencilOpSeparate", stencilOpSeparate},
		{"stencilOpSeparate", stencilOpSeparate},
		{"uniform1f", uniform1f},
		{"uniform2f", uniform2f},
		{"uniform3f", uniform3f},
		{"uniform4f", uniform4f},
		{"uniform1i", uniform1i},
		{"uniform2i", uniform2i},
		{"uniform3i", uniform3i},
		{"uniform4i", uniform4i},
		{"uniform1fv", uniform1fv},
		{"uniform2fv", uniform2fv},
		{"uniform3fv", uniform3fv},
		{"uniform4fv", uniform4fv},
		{"uniform1iv", uniform1iv},
		{"uniform2iv", uniform2iv},
		{"uniform3iv", uniform3iv},
		{"uniform4iv", uniform4iv},
		{"uniformMatrix2fv", uniformMatrix2fv},
		{"uniformMatrix3fv", uniformMatrix3fv},
		{"uniformMatrix4fv", uniformMatrix4fv},
		{"uniformMatrix2x3fv", uniformMatrix2x3fv},
		{"uniformMatrix3x2fv", uniformMatrix3x2fv},
		{"uniformMatrix2x4fv", uniformMatrix2x4fv},
		{"uniformMatrix4x2fv", uniformMatrix4x2fv},
		{"uniformMatrix3x4fv", uniformMatrix3x4fv},
		{"uniformMatrix4x3fv", uniformMatrix4x3fv},
		{"useProgram", useProgram},
		{"validateProgram", validateProgram},
		{"vertexAttrib1f", vertexAttrib1f},
		{"vertexAttrib1s", vertexAttrib1s},
		{"vertexAttrib1d", vertexAttrib1d},
		{"vertexAttrib2f", vertexAttrib2f},
		{"vertexAttrib2s", vertexAttrib2s},
		{"vertexAttrib2d", vertexAttrib2d},
		{"vertexAttrib3f", vertexAttrib3f},
		{"vertexAttrib3s", vertexAttrib3s},
		{"vertexAttrib3d", vertexAttrib3d},
		{"vertexAttrib4f", vertexAttrib4f},
		{"vertexAttrib4s", vertexAttrib4s},
		{"vertexAttrib4d", vertexAttrib4d},
		{"vertexAttrib4Nub", vertexAttrib4Nub},
		{"vertexAttrib1fv", vertexAttrib1fv},
		{"vertexAttrib1sv", vertexAttrib1sv},
		{"vertexAttrib1dv", vertexAttrib1dv},
		{"vertexAttrib2fv", vertexAttrib2fv},
		{"vertexAttrib2sv", vertexAttrib2sv},
		{"vertexAttrib2dv", vertexAttrib2dv},
		{"vertexAttrib3fv", vertexAttrib3fv},
		{"vertexAttrib3sv", vertexAttrib3sv},
		{"vertexAttrib3dv", vertexAttrib3dv},
		{"vertexAttrib4fv", vertexAttrib4fv},
		{"vertexAttrib4dv", vertexAttrib4dv},
		{"vertexAttrib4bv", vertexAttrib4bv},
		{"vertexAttrib4sv", vertexAttrib4sv},
		{"vertexAttrib4iv", vertexAttrib4iv},
		{"vertexAttrib4ubv", vertexAttrib4ubv},
		{"vertexAttrib4usv", vertexAttrib4usv},
		{"vertexAttrib4uiv", vertexAttrib4uiv},
		{"vertexAttrib4Nbv", vertexAttrib4Nbv},
		{"vertexAttrib4Nsv", vertexAttrib4Nsv},
		{"vertexAttrib4Niv", vertexAttrib4Niv},
		{"vertexAttrib4Nubv", vertexAttrib4Nubv},
		{"vertexAttrib4Nusv", vertexAttrib4Nusv},
		{"vertexAttrib4Nuiv", vertexAttrib4Nuiv},
		{"vertexAttribPointer", vertexAttribPointer},
#endif
		{NULL, NULL}
	};
	luaL_register(L, "gl", localLib);

	return 1;
}
