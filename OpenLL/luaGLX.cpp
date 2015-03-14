#include "luaGLX.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "olua.h"

#include <iostream>

using namespace olf::glx;

static int createShader(lua_State* L) {
	auto source = lua_tocast<std::string>(L, 1);
	auto type = lua_tocast<GLenum>(L, 2);
	auto src = source.c_str();

	auto shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	// If something went wrong print the log. Also delete the shader.
	int compileOK = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOK);
	if (compileOK != 1) {
		std::cout << "Shader Compile Error Log (Type " << type << ")\n";

		GLint logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		char* logText = new char[logLength];
		glGetShaderInfoLog(shader, logLength, nullptr, logText);
		std::cout << logText;
		delete [] logText;

		glDeleteShader(shader);
		shader = -1;
	}

	lua_pushnumber(L, shader);
	return 1;
}

static int createProgram(lua_State* L) {
	auto colorOut = lua_tostring(L, 1);
	lua_remove(L, 1);

	auto newProgram = glCreateProgram();

	auto n = lua_gettop(L);
	for (int i = 1; i <= n; ++i) {
		auto nextShader = lua_tocast<GLuint>(L, i);
		glAttachShader(newProgram, nextShader);
	}

	glBindFragDataLocation(newProgram, 0, colorOut);
	glLinkProgram(newProgram);

	for (int i = 1; i <= n; ++i) {
		auto nextShader = lua_tocast<GLuint>(L, i);
		glDetachShader(newProgram, nextShader);
		glDeleteShader(nextShader);
	}

	glUseProgram(newProgram);

	lua_pushnumber(L, newProgram);

	return 1;
}

static int enableVertexAttribPointer(lua_State* L) {
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
	glEnableVertexAttribArray(index);
	return 0;
}

static int genBindBufferData(lua_State* L) {
	auto target = lua_tocast<GLenum>(L, 1);
	auto type = lua_tocast<GLenum>(L, 2);
	GLsizeiptr size;
	auto data = lua_tabletoglarray(L, 3, type, size);
	auto usage = lua_tocast<GLenum>(L, 4);

	GLuint buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, usage);

	delete [] data; data = NULL;

	lua_pushnumber(L, buffer);

	return 1;
}

static int genBindVertexArrays(lua_State* L) {
	auto n = lua_wrapgenfunction(L, glGenVertexArrays);
	lua_wrapfunction(L, glBindVertexArray);
	return n;
}

int olf::glx::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{"createShader", createShader},
		{"createProgram", createProgram},
		{"enableVertexAttribPointer", enableVertexAttribPointer},
		{"genBindBufferData", genBindBufferData},
		{"genBindVertexArrays", genBindVertexArrays},
		{NULL, NULL}
	};
	luaL_openlib(L, "glx", localLib, 0);

	return 1;
}
