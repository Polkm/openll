#include "luaImport.h"

#include "olua.h"
#include "utilString.h"
#include "Vector3.h"

#include "SOIL.h"
#include <GL\glew.h>
#include <sndfile.h>
#include <lib3ds.h>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>

using namespace olf::import;

// Internal use only!
char* readIntoBuffer(const char* fileName) {
	std::ifstream is;
	is.open(fileName, std::ios::binary);

	// Get the length of the file.
	is.seekg(0, std::ios::end);
	auto length = is.tellg();
	is.seekg(0, std::ios::beg);

	auto buffer = new char[static_cast<unsigned int>(length)];

	// read data as a block:
	is.read(buffer, length);
	is.close();
	return buffer;
}
std::string readTextFile(const char* fileName) {
	std::string fileString = "";
	std::string line = "";
	std::ifstream file(fileName);

	if (file.is_open()) {
		while (!file.eof()) { // While we are not at the end of the file
			getline(file, line);
			fileString.append(line);
			fileString.append("\n");
		}
		file.close(); // Close the file
		if (fileString.length() > 0) {
			return fileString;
		}
	}
	// Failed push empty string
	return "";
}

// Import an audio file and return the audio data.
// Takes (fileName) Returns (data, sampleRate, bitsPerSample, channels)
static int audio(lua_State* L) {
	auto fileName = lua_tocast<const char*>(L, 1);

	SF_INFO info;
	auto file = sf_open(fileName, SFM_READ, &info);
	auto data = new short[static_cast<unsigned int>(info.frames * info.channels)];
	sf_readf_short(file, data, info.frames);

	lua_pusharray(L, (unsigned char*)data, static_cast<unsigned int>(info.frames * info.channels * 2), true);
	lua_push(L, info.samplerate);
	lua_push(L, 16);
	lua_push(L, info.channels);
	return 4;
}

// Import an image file.
// Takes (fileName, format) Returns (pixelTable, width, height, channels)
static int image(lua_State* L) {
	auto fileName = lua_tostring(L, 1);
	auto format = lua_tocast<int>(L, 2);

	int width, height, channels;
	unsigned char* image = SOIL_load_image(fileName, &width, &height, &channels, format);

	int imageChannels = channels;
	switch (format) {
	case SOIL_LOAD_L:
		imageChannels = 1; break;
	case SOIL_LOAD_LA:
		imageChannels = 2; break;
	case SOIL_LOAD_RGB:
		imageChannels = 3; break;
	case SOIL_LOAD_RGBA:
		imageChannels = 4; break;
	}

	lua_pusharray(L, image, width * height * imageChannels);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	lua_pushnumber(L, channels);

	SOIL_free_image_data(image);
	return 4;
}

// Import an image and create/bind a texture.
// Takes (fileName, imageFormat,textureFormat,  wrap, minFilter, magFilter) Returns (texture)
static int texture(lua_State* L) {
	auto fileName = lua_tostring(L, 1);
	auto imageFormat = lua_tocast<int>(L, 2);
	auto textureFormat = lua_tocast<GLenum>(L, 3);
	auto wrap = lua_tosafecast<GLenum>(L, 4, GL_REPEAT);
	auto minFilter = lua_tosafecast<GLenum>(L, 5, GL_LINEAR_MIPMAP_LINEAR);
	auto magFilter = lua_tosafecast<GLenum>(L, 6, GL_LINEAR);

	// Load textures
	GLuint texture;
	glGenTextures(1, &texture);
	
	int width, height;
	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, imageFormat);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

#ifndef GL_VERSION_3_0
	// Legacy mipmap generation
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#endif

	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

#ifdef GL_VERSION_3_0
	glEnable(GL_TEXTURE_2D); // ATI driver fix. Doesn't always work.
	glGenerateMipmap(GL_TEXTURE_2D);
#endif

	lua_pushnumber(L, texture);

	return 1;
}

// Reads a file as a text document.
// Takes (fileName) Returns (string)
static int text(lua_State* L) {
	auto fileName = lua_tocast<const char*>(L, 1);
	auto contents = readTextFile(fileName);
	lua_pushstring(L, contents.c_str());
	return 1;
}

// Imports PLY files
static int vertices(lua_State* L) {
	auto fileName = lua_tocast<const char*>(L, 1);
	auto buffer = readIntoBuffer(fileName);
	std::vector<float> vertexData;
	std::list<unsigned int> indexData;

    char* line = buffer;
    char* token = strchr(line, '\n');

	// Helper vars
	bool isHeader = true;
	bool isElement = false;
	char* element;
	int elementCounter = 0;
	int vertexCount = 0;
	
    while (token != NULL) {
        *token++ = '\0';

        //printf("%s\n", line);
		int listLength = 0;
		char* lastToken = NULL;
		auto token2 = strtok(line, " ");
        while (token2 != NULL) {
			if (isElement) {
				if (strcmp(lastToken, "vertex") == 0) {
					vertexCount = atoi(token2);
					printf("%d\n", vertexCount);
				}
				//if (strcmp(lastToken, "vertex") == 0) {
				//	vertexCount = atoi(token2);
				//	//printf("%d\n", vertexCount);
				//}
			} else {
				//printf("%s\n", isHeader ? "true" : "false");
				if (!isHeader) {
					if (elementCounter < vertexCount * 6) {
						//printf("'%s' ", token2);
						vertexData.push_back(static_cast<float>(atof(token2)));
					} else {
						if (lastToken != NULL) {
							//printf("%s ", token2);
							indexData.push_back(atoi(token2));
						} else {
							//listLength
						}
					}
					++elementCounter;
				}
				if (strcmp(token2, "end_header") == 0) isHeader = false;
				if (strcmp(token2, "element") == 0) isElement = true;
			}

            //printf("%s\n", token2);
			lastToken = token2;
            token2 = strtok(NULL, " ");
        }

		isElement = false;

		//printf("\n");

        line = token;
        token = strchr(line, '\n');
    }

	//vertexData.erase(vertexData.begin());
	lua_pushlist(L, vertexData);
	lua_pushlist(L, indexData);

	delete [] buffer;

	return 2;
}

// Imports 3DS files
static int mesh3ds(lua_State* L) {
	auto fileName = lua_tocast<const char*>(L, 1);
	Lib3dsFile* m_model = lib3ds_file_open(fileName);

	// Allocate memory for our vertices and normals
	std::vector<float> vertexData;
	std::list<unsigned int> indexData;

	// Loop through all the meshes
	for (int i = 0; i < m_model->nmeshes; ++i) {
		Lib3dsMesh* mesh = m_model->meshes[i];

		//// Calculate the normal for each vertex.
		float* normals = (float*)malloc(3*3*sizeof(float)*mesh->nfaces);
		//float (*normals)[3] = new float[mesh->nvertices][3];
		//lib3ds_mesh_calculate_face_normals(mesh, normals);

		float (*vertices)[3] = mesh->vertices;

		//// Add all the vertex data to the vertex data list.
		//for (int j = 0; j < mesh->nvertices; ++j) {
		//	vertexData.push_back(vertices[j][0]);
		//	vertexData.push_back(vertices[j][1]);
		//	vertexData.push_back(vertices[j][2]);
		//	vertexData.push_back(normals[j][0]);
		//	vertexData.push_back(normals[j][1]);
		//	vertexData.push_back(normals[j][2]);
		//}
		delete [] normals;

		//// Loop through every face.
		//Lib3dsFace* faces = mesh->faces;
		//for (int j = 0; j < mesh->nfaces; ++j) {
		//	Lib3dsFace face = faces[j];
		//	indexData.push_back(face.index[0]);
		//	indexData.push_back(face.index[1]);
		//	indexData.push_back(face.index[2]);
		//}
	}

	lua_pushlist(L, vertexData);
	lua_pushlist(L, indexData);

	// We no longer need lib3ds
	lib3ds_file_free(m_model);
	m_model = NULL;
	return 2;
}

int olf::import::registerLua(lua_State* L) {
	const luaL_reg localLib[] = {
		{"audio", audio},
		{"image", image},
		{"texture", texture},
		{"text", text},
		{"vertices", vertices},
		{"mesh3ds", mesh3ds},
		{NULL, NULL}
	};
	luaL_register(L, "import", localLib);

	lua_pushenumuration(L, "IMPORT_IMAGE_AUTO", SOIL_LOAD_AUTO);
	lua_pushenumuration(L, "IMPORT_IMAGE_L", SOIL_LOAD_L);
	lua_pushenumuration(L, "IMPORT_IMAGE_LA", SOIL_LOAD_LA);
	lua_pushenumuration(L, "IMPORT_IMAGE_RGB", SOIL_LOAD_RGB);
	lua_pushenumuration(L, "IMPORT_IMAGE_RGBA", SOIL_LOAD_RGBA);

	return 1;
}