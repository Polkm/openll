#include "luaGL.h"
#include "luaGL10.h"
#include "luaGL20.h"
#include "luaGL30.h"
#include "luaGL40.h"

#include <GL/glew.h>
#include "olua.h"

int olf::gl::registerLua(lua_State* L) {
	const struct luaL_reg localLib[] = {
		{NULL, NULL}
	};
	luaL_openlib(L, "gl", localLib, 0);

	olf::gl::registerLua10(L);
	olf::gl::registerLua20(L);
	olf::gl::registerLua30(L);
	olf::gl::registerLua40(L);

	lua_pushenumuration(L, "GL_DOUBLE_SIZE", sizeof(GLdouble));
	lua_pushenumuration(L, "GL_FLOAT_SIZE", sizeof(GLfloat));
	lua_pushenumuration(L, "GL_HALF_FLOAT_SIZE", sizeof(GLfloat) / 2);
	lua_pushenumuration(L, "GL_BYTE_SIZE", sizeof(GLbyte));
	lua_pushenumuration(L, "GL_SHORT_SIZE", sizeof(GLshort));
	lua_pushenumuration(L, "GL_INT_SIZE", sizeof(GLint));
	lua_pushenumuration(L, "GL_UNSIGNED_BYTE_SIZE", sizeof(GLubyte));
	lua_pushenumuration(L, "GL_UNSIGNED_SHORT_SIZE", sizeof(GLushort));
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SIZE", sizeof(GLuint));

#ifdef GL_VERSION_1_1
	lua_pushenumuration(L, "GL_DEPTH_BUFFER_BIT", 0x00000100);
	lua_pushenumuration(L, "GL_STENCIL_BUFFER_BIT", 0x00000400);
	lua_pushenumuration(L, "GL_COLOR_BUFFER_BIT", 0x00004000);
	lua_pushenumuration(L, "GL_FALSE", 0);
	lua_pushenumuration(L, "GL_TRUE", 1);
	lua_pushenumuration(L, "GL_POINTS", 0x0000);
	lua_pushenumuration(L, "GL_LINES", 0x0001);
	lua_pushenumuration(L, "GL_LINE_LOOP", 0x0002);
	lua_pushenumuration(L, "GL_LINE_STRIP", 0x0003);
	lua_pushenumuration(L, "GL_TRIANGLES", 0x0004);
	lua_pushenumuration(L, "GL_TRIANGLE_STRIP", 0x0005);
	lua_pushenumuration(L, "GL_TRIANGLE_FAN", 0x0006);
	lua_pushenumuration(L, "GL_NEVER", 0x0200);
	lua_pushenumuration(L, "GL_LESS", 0x0201);
	lua_pushenumuration(L, "GL_EQUAL", 0x0202);
	lua_pushenumuration(L, "GL_LEQUAL", 0x0203);
	lua_pushenumuration(L, "GL_GREATER", 0x0204);
	lua_pushenumuration(L, "GL_NOTEQUAL", 0x0205);
	lua_pushenumuration(L, "GL_GEQUAL", 0x0206);
	lua_pushenumuration(L, "GL_ALWAYS", 0x0207);
	lua_pushenumuration(L, "GL_ZERO", 0);
	lua_pushenumuration(L, "GL_ONE", 1);
	lua_pushenumuration(L, "GL_SRC_COLOR", 0x0300);
	lua_pushenumuration(L, "GL_ONE_MINUS_SRC_COLOR", 0x0301);
	lua_pushenumuration(L, "GL_SRC_ALPHA", 0x0302);
	lua_pushenumuration(L, "GL_ONE_MINUS_SRC_ALPHA", 0x0303);
	lua_pushenumuration(L, "GL_DST_ALPHA", 0x0304);
	lua_pushenumuration(L, "GL_ONE_MINUS_DST_ALPHA", 0x0305);
	lua_pushenumuration(L, "GL_DST_COLOR", 0x0306);
	lua_pushenumuration(L, "GL_ONE_MINUS_DST_COLOR", 0x0307);
	lua_pushenumuration(L, "GL_SRC_ALPHA_SATURATE", 0x0308);
	lua_pushenumuration(L, "GL_NONE", 0);
	lua_pushenumuration(L, "GL_FRONT_LEFT", 0x0400);
	lua_pushenumuration(L, "GL_FRONT_RIGHT", 0x0401);
	lua_pushenumuration(L, "GL_BACK_LEFT", 0x0402);
	lua_pushenumuration(L, "GL_BACK_RIGHT", 0x0403);
	lua_pushenumuration(L, "GL_FRONT", 0x0404);
	lua_pushenumuration(L, "GL_BACK", 0x0405);
	lua_pushenumuration(L, "GL_LEFT", 0x0406);
	lua_pushenumuration(L, "GL_RIGHT", 0x0407);
	lua_pushenumuration(L, "GL_FRONT_AND_BACK", 0x0408);
	lua_pushenumuration(L, "GL_NO_ERROR", 0);
	lua_pushenumuration(L, "GL_INVALID_ENUM", 0x0500);
	lua_pushenumuration(L, "GL_INVALID_VALUE", 0x0501);
	lua_pushenumuration(L, "GL_INVALID_OPERATION", 0x0502);
	lua_pushenumuration(L, "GL_OUT_OF_MEMORY", 0x0505);
	lua_pushenumuration(L, "GL_CW", 0x0900);
	lua_pushenumuration(L, "GL_CCW", 0x0901);
	lua_pushenumuration(L, "GL_POINT_SIZE", 0x0B11);
	lua_pushenumuration(L, "GL_POINT_SIZE_RANGE", 0x0B12);
	lua_pushenumuration(L, "GL_POINT_SIZE_GRANULARITY", 0x0B13);
	lua_pushenumuration(L, "GL_LINE_SMOOTH", 0x0B20);
	lua_pushenumuration(L, "GL_LINE_WIDTH", 0x0B21);
	lua_pushenumuration(L, "GL_LINE_WIDTH_RANGE", 0x0B22);
	lua_pushenumuration(L, "GL_LINE_WIDTH_GRANULARITY", 0x0B23);
	lua_pushenumuration(L, "GL_POLYGON_SMOOTH", 0x0B41);
	lua_pushenumuration(L, "GL_CULL_FACE", 0x0B44);
	lua_pushenumuration(L, "GL_CULL_FACE_MODE", 0x0B45);
	lua_pushenumuration(L, "GL_FRONT_FACE", 0x0B46);
	lua_pushenumuration(L, "GL_DEPTH_RANGE", 0x0B70);
	lua_pushenumuration(L, "GL_DEPTH_TEST", 0x0B71);
	lua_pushenumuration(L, "GL_DEPTH_WRITEMASK", 0x0B72);
	lua_pushenumuration(L, "GL_DEPTH_CLEAR_VALUE", 0x0B73);
	lua_pushenumuration(L, "GL_DEPTH_FUNC", 0x0B74);
	lua_pushenumuration(L, "GL_STENCIL_TEST", 0x0B90);
	lua_pushenumuration(L, "GL_STENCIL_CLEAR_VALUE", 0x0B91);
	lua_pushenumuration(L, "GL_STENCIL_FUNC", 0x0B92);
	lua_pushenumuration(L, "GL_STENCIL_VALUE_MASK", 0x0B93);
	lua_pushenumuration(L, "GL_STENCIL_FAIL", 0x0B94);
	lua_pushenumuration(L, "GL_STENCIL_PASS_DEPTH_FAIL", 0x0B95);
	lua_pushenumuration(L, "GL_STENCIL_PASS_DEPTH_PASS", 0x0B96);
	lua_pushenumuration(L, "GL_STENCIL_REF", 0x0B97);
	lua_pushenumuration(L, "GL_STENCIL_WRITEMASK", 0x0B98);
	lua_pushenumuration(L, "GL_VIEWPORT", 0x0BA2);
	lua_pushenumuration(L, "GL_DITHER", 0x0BD0);
	lua_pushenumuration(L, "GL_BLEND_DST", 0x0BE0);
	lua_pushenumuration(L, "GL_BLEND_SRC", 0x0BE1);
	lua_pushenumuration(L, "GL_BLEND", 0x0BE2);
	lua_pushenumuration(L, "GL_LOGIC_OP_MODE", 0x0BF0);
	lua_pushenumuration(L, "GL_COLOR_LOGIC_OP", 0x0BF2);
	lua_pushenumuration(L, "GL_DRAW_BUFFER", 0x0C01);
	lua_pushenumuration(L, "GL_READ_BUFFER", 0x0C02);
	lua_pushenumuration(L, "GL_SCISSOR_BOX", 0x0C10);
	lua_pushenumuration(L, "GL_SCISSOR_TEST", 0x0C11);
	lua_pushenumuration(L, "GL_COLOR_CLEAR_VALUE", 0x0C22);
	lua_pushenumuration(L, "GL_COLOR_WRITEMASK", 0x0C23);
	lua_pushenumuration(L, "GL_DOUBLEBUFFER", 0x0C32);
	lua_pushenumuration(L, "GL_STEREO", 0x0C33);
	lua_pushenumuration(L, "GL_LINE_SMOOTH_HINT", 0x0C52);
	lua_pushenumuration(L, "GL_POLYGON_SMOOTH_HINT", 0x0C53);
	lua_pushenumuration(L, "GL_UNPACK_SWAP_BYTES", 0x0CF0);
	lua_pushenumuration(L, "GL_UNPACK_LSB_FIRST", 0x0CF1);
	lua_pushenumuration(L, "GL_UNPACK_ROW_LENGTH", 0x0CF2);
	lua_pushenumuration(L, "GL_UNPACK_SKIP_ROWS", 0x0CF3);
	lua_pushenumuration(L, "GL_UNPACK_SKIP_PIXELS", 0x0CF4);
	lua_pushenumuration(L, "GL_UNPACK_ALIGNMENT", 0x0CF5);
	lua_pushenumuration(L, "GL_PACK_SWAP_BYTES", 0x0D00);
	lua_pushenumuration(L, "GL_PACK_LSB_FIRST", 0x0D01);
	lua_pushenumuration(L, "GL_PACK_ROW_LENGTH", 0x0D02);
	lua_pushenumuration(L, "GL_PACK_SKIP_ROWS", 0x0D03);
	lua_pushenumuration(L, "GL_PACK_SKIP_PIXELS", 0x0D04);
	lua_pushenumuration(L, "GL_PACK_ALIGNMENT", 0x0D05);
	lua_pushenumuration(L, "GL_MAX_TEXTURE_SIZE", 0x0D33);
	lua_pushenumuration(L, "GL_MAX_VIEWPORT_DIMS", 0x0D3A);
	lua_pushenumuration(L, "GL_SUBPIXEL_BITS", 0x0D50);
	lua_pushenumuration(L, "GL_TEXTURE_1D", 0x0DE0);
	lua_pushenumuration(L, "GL_TEXTURE_2D", 0x0DE1);
	lua_pushenumuration(L, "GL_POLYGON_OFFSET_UNITS", 0x2A00);
	lua_pushenumuration(L, "GL_POLYGON_OFFSET_POINT", 0x2A01);
	lua_pushenumuration(L, "GL_POLYGON_OFFSET_LINE", 0x2A02);
	lua_pushenumuration(L, "GL_POLYGON_OFFSET_FILL", 0x8037);
	lua_pushenumuration(L, "GL_POLYGON_OFFSET_FACTOR", 0x8038);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_1D", 0x8068);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_2D", 0x8069);
	lua_pushenumuration(L, "GL_TEXTURE_WIDTH", 0x1000);
	lua_pushenumuration(L, "GL_TEXTURE_HEIGHT", 0x1001);
	lua_pushenumuration(L, "GL_TEXTURE_INTERNAL_FORMAT", 0x1003);
	lua_pushenumuration(L, "GL_TEXTURE_BORDER_COLOR", 0x1004);
	lua_pushenumuration(L, "GL_TEXTURE_RED_SIZE", 0x805C);
	lua_pushenumuration(L, "GL_TEXTURE_GREEN_SIZE", 0x805D);
	lua_pushenumuration(L, "GL_TEXTURE_BLUE_SIZE", 0x805E);
	lua_pushenumuration(L, "GL_TEXTURE_ALPHA_SIZE", 0x805F);
	lua_pushenumuration(L, "GL_DONT_CARE", 0x1100);
	lua_pushenumuration(L, "GL_FASTEST", 0x1101);
	lua_pushenumuration(L, "GL_NICEST", 0x1102);
	lua_pushenumuration(L, "GL_BYTE", 0x1400);
	lua_pushenumuration(L, "GL_UNSIGNED_BYTE", 0x1401);
	lua_pushenumuration(L, "GL_SHORT", 0x1402);
	lua_pushenumuration(L, "GL_UNSIGNED_SHORT", 0x1403);
	lua_pushenumuration(L, "GL_INT", 0x1404);
	lua_pushenumuration(L, "GL_UNSIGNED_INT", 0x1405);
	lua_pushenumuration(L, "GL_FLOAT", 0x1406);
	lua_pushenumuration(L, "GL_DOUBLE", 0x140A);
	lua_pushenumuration(L, "GL_STACK_OVERFLOW", 0x0503);
	lua_pushenumuration(L, "GL_STACK_UNDERFLOW", 0x0504);
	lua_pushenumuration(L, "GL_CLEAR", 0x1500);
	lua_pushenumuration(L, "GL_AND", 0x1501);
	lua_pushenumuration(L, "GL_AND_REVERSE", 0x1502);
	lua_pushenumuration(L, "GL_COPY", 0x1503);
	lua_pushenumuration(L, "GL_AND_INVERTED", 0x1504);
	lua_pushenumuration(L, "GL_NOOP", 0x1505);
	lua_pushenumuration(L, "GL_XOR", 0x1506);
	lua_pushenumuration(L, "GL_OR", 0x1507);
	lua_pushenumuration(L, "GL_NOR", 0x1508);
	lua_pushenumuration(L, "GL_EQUIV", 0x1509);
	lua_pushenumuration(L, "GL_INVERT", 0x150A);
	lua_pushenumuration(L, "GL_OR_REVERSE", 0x150B);
	lua_pushenumuration(L, "GL_COPY_INVERTED", 0x150C);
	lua_pushenumuration(L, "GL_OR_INVERTED", 0x150D);
	lua_pushenumuration(L, "GL_NAND", 0x150E);
	lua_pushenumuration(L, "GL_SET", 0x150F);
	lua_pushenumuration(L, "GL_TEXTURE", 0x1702);
	lua_pushenumuration(L, "GL_COLOR", 0x1800);
	lua_pushenumuration(L, "GL_DEPTH", 0x1801);
	lua_pushenumuration(L, "GL_STENCIL", 0x1802);
	lua_pushenumuration(L, "GL_STENCIL_INDEX", 0x1901);
	lua_pushenumuration(L, "GL_DEPTH_COMPONENT", 0x1902);
	lua_pushenumuration(L, "GL_RED", 0x1903);
	lua_pushenumuration(L, "GL_GREEN", 0x1904);
	lua_pushenumuration(L, "GL_BLUE", 0x1905);
	lua_pushenumuration(L, "GL_ALPHA", 0x1906);
	lua_pushenumuration(L, "GL_RGB", 0x1907);
	lua_pushenumuration(L, "GL_RGBA", 0x1908);
	lua_pushenumuration(L, "GL_POINT", 0x1B00);
	lua_pushenumuration(L, "GL_LINE", 0x1B01);
	lua_pushenumuration(L, "GL_FILL", 0x1B02);
	lua_pushenumuration(L, "GL_KEEP", 0x1E00);
	lua_pushenumuration(L, "GL_REPLACE", 0x1E01);
	lua_pushenumuration(L, "GL_INCR", 0x1E02);
	lua_pushenumuration(L, "GL_DECR", 0x1E03);
	lua_pushenumuration(L, "GL_VENDOR", 0x1F00);
	lua_pushenumuration(L, "GL_RENDERER", 0x1F01);
	lua_pushenumuration(L, "GL_VERSION", 0x1F02);
	lua_pushenumuration(L, "GL_EXTENSIONS", 0x1F03);
	lua_pushenumuration(L, "GL_NEAREST", 0x2600);
	lua_pushenumuration(L, "GL_LINEAR", 0x2601);
	lua_pushenumuration(L, "GL_NEAREST_MIPMAP_NEAREST", 0x2700);
	lua_pushenumuration(L, "GL_LINEAR_MIPMAP_NEAREST", 0x2701);
	lua_pushenumuration(L, "GL_NEAREST_MIPMAP_LINEAR", 0x2702);
	lua_pushenumuration(L, "GL_LINEAR_MIPMAP_LINEAR", 0x2703);
	lua_pushenumuration(L, "GL_TEXTURE_MAG_FILTER", 0x2800);
	lua_pushenumuration(L, "GL_TEXTURE_MIN_FILTER", 0x2801);
	lua_pushenumuration(L, "GL_TEXTURE_WRAP_S", 0x2802);
	lua_pushenumuration(L, "GL_TEXTURE_WRAP_T", 0x2803);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_1D", 0x8063);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_2D", 0x8064);
	lua_pushenumuration(L, "GL_REPEAT", 0x2901);
	lua_pushenumuration(L, "GL_R3_G3_B2", 0x2A10);
	lua_pushenumuration(L, "GL_RGB4", 0x804F);
	lua_pushenumuration(L, "GL_RGB5", 0x8050);
	lua_pushenumuration(L, "GL_RGB8", 0x8051);
	lua_pushenumuration(L, "GL_RGB10", 0x8052);
	lua_pushenumuration(L, "GL_RGB12", 0x8053);
	lua_pushenumuration(L, "GL_RGB16", 0x8054);
	lua_pushenumuration(L, "GL_RGBA2", 0x8055);
	lua_pushenumuration(L, "GL_RGBA4", 0x8056);
	lua_pushenumuration(L, "GL_RGB5_A1", 0x8057);
	lua_pushenumuration(L, "GL_RGBA8", 0x8058);
	lua_pushenumuration(L, "GL_RGB10_A2", 0x8059);
	lua_pushenumuration(L, "GL_RGBA12", 0x805A);
	lua_pushenumuration(L, "GL_RGBA16", 0x805B);
#endif
#ifdef GL_VERSION_1_2
	lua_pushenumuration(L, "GL_UNSIGNED_BYTE_3_3_2", 0x8032);
	lua_pushenumuration(L, "GL_UNSIGNED_SHORT_4_4_4_4", 0x8033);
	lua_pushenumuration(L, "GL_UNSIGNED_SHORT_5_5_5_1", 0x8034);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_8_8_8_8", 0x8035);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_10_10_10_2", 0x8036);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_3D", 0x806A);
	lua_pushenumuration(L, "GL_PACK_SKIP_IMAGES", 0x806B);
	lua_pushenumuration(L, "GL_PACK_IMAGE_HEIGHT", 0x806C);
	lua_pushenumuration(L, "GL_UNPACK_SKIP_IMAGES", 0x806D);
	lua_pushenumuration(L, "GL_UNPACK_IMAGE_HEIGHT", 0x806E);
	lua_pushenumuration(L, "GL_TEXTURE_3D", 0x806F);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_3D", 0x8070);
	lua_pushenumuration(L, "GL_TEXTURE_DEPTH", 0x8071);
	lua_pushenumuration(L, "GL_TEXTURE_WRAP_R", 0x8072);
	lua_pushenumuration(L, "GL_MAX_3D_TEXTURE_SIZE", 0x8073);
	lua_pushenumuration(L, "GL_UNSIGNED_BYTE_2_3_3_REV", 0x8362);
	lua_pushenumuration(L, "GL_UNSIGNED_SHORT_5_6_5", 0x8363);
	lua_pushenumuration(L, "GL_UNSIGNED_SHORT_5_6_5_REV", 0x8364);
	lua_pushenumuration(L, "GL_UNSIGNED_SHORT_4_4_4_4_REV", 0x8365);
	lua_pushenumuration(L, "GL_UNSIGNED_SHORT_1_5_5_5_REV", 0x8366);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_8_8_8_8_REV", 0x8367);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_2_10_10_10_REV", 0x8368);
	lua_pushenumuration(L, "GL_BGR", 0x80E0);
	lua_pushenumuration(L, "GL_BGRA", 0x80E1);
	lua_pushenumuration(L, "GL_MAX_ELEMENTS_VERTICES", 0x80E8);
	lua_pushenumuration(L, "GL_MAX_ELEMENTS_INDICES", 0x80E9);
	lua_pushenumuration(L, "GL_CLAMP_TO_EDGE", 0x812F);
	lua_pushenumuration(L, "GL_TEXTURE_MIN_LOD", 0x813A);
	lua_pushenumuration(L, "GL_TEXTURE_MAX_LOD", 0x813B);
	lua_pushenumuration(L, "GL_TEXTURE_BASE_LEVEL", 0x813C);
	lua_pushenumuration(L, "GL_TEXTURE_MAX_LEVEL", 0x813D);
	lua_pushenumuration(L, "GL_SMOOTH_POINT_SIZE_RANGE", 0x0B12);
	lua_pushenumuration(L, "GL_SMOOTH_POINT_SIZE_GRANULARITY", 0x0B13);
	lua_pushenumuration(L, "GL_SMOOTH_LINE_WIDTH_RANGE", 0x0B22);
	lua_pushenumuration(L, "GL_SMOOTH_LINE_WIDTH_GRANULARITY", 0x0B23);
	lua_pushenumuration(L, "GL_ALIASED_LINE_WIDTH_RANGE", 0x846E);
#endif
#ifdef GL_ARB_imaging
	lua_pushenumuration(L, "GL_CONSTANT_COLOR", 0x8001);
	lua_pushenumuration(L, "GL_ONE_MINUS_CONSTANT_COLOR", 0x8002);
	lua_pushenumuration(L, "GL_CONSTANT_ALPHA", 0x8003);
	lua_pushenumuration(L, "GL_ONE_MINUS_CONSTANT_ALPHA", 0x8004);
	lua_pushenumuration(L, "GL_BLEND_COLOR", 0x8005);
	lua_pushenumuration(L, "GL_FUNC_ADD", 0x8006);
	lua_pushenumuration(L, "GL_MIN", 0x8007);
	lua_pushenumuration(L, "GL_MAX", 0x8008);
	lua_pushenumuration(L, "GL_BLEND_EQUATION", 0x8009);
	lua_pushenumuration(L, "GL_FUNC_SUBTRACT", 0x800A);
	lua_pushenumuration(L, "GL_FUNC_REVERSE_SUBTRACT", 0x800B);
#endif
#ifdef GL_VERSION_1_3
	lua_pushenumuration(L, "GL_TEXTURE0", 0x84C0);
	lua_pushenumuration(L, "GL_TEXTURE1", 0x84C1);
	lua_pushenumuration(L, "GL_TEXTURE2", 0x84C2);
	lua_pushenumuration(L, "GL_TEXTURE3", 0x84C3);
	lua_pushenumuration(L, "GL_TEXTURE4", 0x84C4);
	lua_pushenumuration(L, "GL_TEXTURE5", 0x84C5);
	lua_pushenumuration(L, "GL_TEXTURE6", 0x84C6);
	lua_pushenumuration(L, "GL_TEXTURE7", 0x84C7);
	lua_pushenumuration(L, "GL_TEXTURE8", 0x84C8);
	lua_pushenumuration(L, "GL_TEXTURE9", 0x84C9);
	lua_pushenumuration(L, "GL_TEXTURE10", 0x84CA);
	lua_pushenumuration(L, "GL_TEXTURE11", 0x84CB);
	lua_pushenumuration(L, "GL_TEXTURE12", 0x84CC);
	lua_pushenumuration(L, "GL_TEXTURE13", 0x84CD);
	lua_pushenumuration(L, "GL_TEXTURE14", 0x84CE);
	lua_pushenumuration(L, "GL_TEXTURE15", 0x84CF);
	lua_pushenumuration(L, "GL_TEXTURE16", 0x84D0);
	lua_pushenumuration(L, "GL_TEXTURE17", 0x84D1);
	lua_pushenumuration(L, "GL_TEXTURE18", 0x84D2);
	lua_pushenumuration(L, "GL_TEXTURE19", 0x84D3);
	lua_pushenumuration(L, "GL_TEXTURE20", 0x84D4);
	lua_pushenumuration(L, "GL_TEXTURE21", 0x84D5);
	lua_pushenumuration(L, "GL_TEXTURE22", 0x84D6);
	lua_pushenumuration(L, "GL_TEXTURE23", 0x84D7);
	lua_pushenumuration(L, "GL_TEXTURE24", 0x84D8);
	lua_pushenumuration(L, "GL_TEXTURE25", 0x84D9);
	lua_pushenumuration(L, "GL_TEXTURE26", 0x84DA);
	lua_pushenumuration(L, "GL_TEXTURE27", 0x84DB);
	lua_pushenumuration(L, "GL_TEXTURE28", 0x84DC);
	lua_pushenumuration(L, "GL_TEXTURE29", 0x84DD);
	lua_pushenumuration(L, "GL_TEXTURE30", 0x84DE);
	lua_pushenumuration(L, "GL_TEXTURE31", 0x84DF);
	lua_pushenumuration(L, "GL_ACTIVE_TEXTURE", 0x84E0);
	lua_pushenumuration(L, "GL_MULTISAMPLE", 0x809D);
	lua_pushenumuration(L, "GL_SAMPLE_ALPHA_TO_COVERAGE", 0x809E);
	lua_pushenumuration(L, "GL_SAMPLE_ALPHA_TO_ONE", 0x809F);
	lua_pushenumuration(L, "GL_SAMPLE_COVERAGE", 0x80A0);
	lua_pushenumuration(L, "GL_SAMPLE_BUFFERS", 0x80A8);
	lua_pushenumuration(L, "GL_SAMPLES", 0x80A9);
	lua_pushenumuration(L, "GL_SAMPLE_COVERAGE_VALUE", 0x80AA);
	lua_pushenumuration(L, "GL_SAMPLE_COVERAGE_INVERT", 0x80AB);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP", 0x8513);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_CUBE_MAP", 0x8514);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_POSITIVE_X", 0x8515);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_NEGATIVE_X", 0x8516);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_POSITIVE_Y", 0x8517);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y", 0x8518);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_POSITIVE_Z", 0x8519);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Z", 0x851A);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_CUBE_MAP", 0x851B);
	lua_pushenumuration(L, "GL_MAX_CUBE_MAP_TEXTURE_SIZE", 0x851C);
	lua_pushenumuration(L, "GL_COMPRESSED_RGB", 0x84ED);
	lua_pushenumuration(L, "GL_COMPRESSED_RGBA", 0x84EE);
	lua_pushenumuration(L, "GL_TEXTURE_COMPRESSION_HINT", 0x84EF);
	lua_pushenumuration(L, "GL_TEXTURE_COMPRESSED_IMAGE_SIZE", 0x86A0);
	lua_pushenumuration(L, "GL_TEXTURE_COMPRESSED", 0x86A1);
	lua_pushenumuration(L, "GL_NUM_COMPRESSED_TEXTURE_FORMATS", 0x86A2);
	lua_pushenumuration(L, "GL_COMPRESSED_TEXTURE_FORMATS", 0x86A3);
	lua_pushenumuration(L, "GL_CLAMP_TO_BORDER", 0x812D);
#endif
#ifdef GL_VERSION_1_4
	lua_pushenumuration(L, "GL_BLEND_DST_RGB", 0x80C8);
	lua_pushenumuration(L, "GL_BLEND_SRC_RGB", 0x80C9);
	lua_pushenumuration(L, "GL_BLEND_DST_ALPHA", 0x80CA);
	lua_pushenumuration(L, "GL_BLEND_SRC_ALPHA", 0x80CB);
	lua_pushenumuration(L, "GL_POINT_FADE_THRESHOLD_SIZE", 0x8128);
	lua_pushenumuration(L, "GL_DEPTH_COMPONENT16", 0x81A5);
	lua_pushenumuration(L, "GL_DEPTH_COMPONENT24", 0x81A6);
	lua_pushenumuration(L, "GL_DEPTH_COMPONENT32", 0x81A7);
	lua_pushenumuration(L, "GL_MIRRORED_REPEAT", 0x8370);
	lua_pushenumuration(L, "GL_MAX_TEXTURE_LOD_BIAS", 0x84FD);
	lua_pushenumuration(L, "GL_TEXTURE_LOD_BIAS", 0x8501);
	lua_pushenumuration(L, "GL_INCR_WRAP", 0x8507);
	lua_pushenumuration(L, "GL_DECR_WRAP", 0x8508);
	lua_pushenumuration(L, "GL_TEXTURE_DEPTH_SIZE", 0x884A);
	lua_pushenumuration(L, "GL_TEXTURE_COMPARE_MODE", 0x884C);
	lua_pushenumuration(L, "GL_TEXTURE_COMPARE_FUNC", 0x884D);
#endif
#ifdef GL_VERSION_1_5
	lua_pushenumuration(L, "GL_BUFFER_SIZE", 0x8764);
	lua_pushenumuration(L, "GL_BUFFER_USAGE", 0x8765);
	lua_pushenumuration(L, "GL_QUERY_COUNTER_BITS", 0x8864);
	lua_pushenumuration(L, "GL_CURRENT_QUERY", 0x8865);
	lua_pushenumuration(L, "GL_QUERY_RESULT", 0x8866);
	lua_pushenumuration(L, "GL_QUERY_RESULT_AVAILABLE", 0x8867);
	lua_pushenumuration(L, "GL_ARRAY_BUFFER", 0x8892);
	lua_pushenumuration(L, "GL_ELEMENT_ARRAY_BUFFER", 0x8893);
	lua_pushenumuration(L, "GL_ARRAY_BUFFER_BINDING", 0x8894);
	lua_pushenumuration(L, "GL_ELEMENT_ARRAY_BUFFER_BINDING", 0x8895);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING", 0x889F);
	lua_pushenumuration(L, "GL_READ_ONLY", 0x88B8);
	lua_pushenumuration(L, "GL_WRITE_ONLY", 0x88B9);
	lua_pushenumuration(L, "GL_READ_WRITE", 0x88BA);
	lua_pushenumuration(L, "GL_BUFFER_ACCESS", 0x88BB);
	lua_pushenumuration(L, "GL_BUFFER_MAPPED", 0x88BC);
	lua_pushenumuration(L, "GL_BUFFER_MAP_POINTER", 0x88BD);
	lua_pushenumuration(L, "GL_STREAM_DRAW", 0x88E0);
	lua_pushenumuration(L, "GL_STREAM_READ", 0x88E1);
	lua_pushenumuration(L, "GL_STREAM_COPY", 0x88E2);
	lua_pushenumuration(L, "GL_STATIC_DRAW", 0x88E4);
	lua_pushenumuration(L, "GL_STATIC_READ", 0x88E5);
	lua_pushenumuration(L, "GL_STATIC_COPY", 0x88E6);
	lua_pushenumuration(L, "GL_DYNAMIC_DRAW", 0x88E8);
	lua_pushenumuration(L, "GL_DYNAMIC_READ", 0x88E9);
	lua_pushenumuration(L, "GL_DYNAMIC_COPY", 0x88EA);
	lua_pushenumuration(L, "GL_SAMPLES_PASSED", 0x8914);
#endif
#ifdef GL_VERSION_2_0
	lua_pushenumuration(L, "GL_BLEND_EQUATION_RGB", 0x8009);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_ENABLED", 0x8622);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_SIZE", 0x8623);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_STRIDE", 0x8624);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_TYPE", 0x8625);
	lua_pushenumuration(L, "GL_CURRENT_VERTEX_ATTRIB", 0x8626);
	lua_pushenumuration(L, "GL_VERTEX_PROGRAM_POINT_SIZE", 0x8642);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_POINTER", 0x8645);
	lua_pushenumuration(L, "GL_STENCIL_BACK_FUNC", 0x8800);
	lua_pushenumuration(L, "GL_STENCIL_BACK_FAIL", 0x8801);
	lua_pushenumuration(L, "GL_STENCIL_BACK_PASS_DEPTH_FAIL", 0x8802);
	lua_pushenumuration(L, "GL_STENCIL_BACK_PASS_DEPTH_PASS", 0x8803);
	lua_pushenumuration(L, "GL_MAX_DRAW_BUFFERS", 0x8824);
	lua_pushenumuration(L, "GL_DRAW_BUFFER0", 0x8825);
	lua_pushenumuration(L, "GL_DRAW_BUFFER1", 0x8826);
	lua_pushenumuration(L, "GL_DRAW_BUFFER2", 0x8827);
	lua_pushenumuration(L, "GL_DRAW_BUFFER3", 0x8828);
	lua_pushenumuration(L, "GL_DRAW_BUFFER4", 0x8829);
	lua_pushenumuration(L, "GL_DRAW_BUFFER5", 0x882A);
	lua_pushenumuration(L, "GL_DRAW_BUFFER6", 0x882B);
	lua_pushenumuration(L, "GL_DRAW_BUFFER7", 0x882C);
	lua_pushenumuration(L, "GL_DRAW_BUFFER8", 0x882D);
	lua_pushenumuration(L, "GL_DRAW_BUFFER9", 0x882E);
	lua_pushenumuration(L, "GL_DRAW_BUFFER10", 0x882F);
	lua_pushenumuration(L, "GL_DRAW_BUFFER11", 0x8830);
	lua_pushenumuration(L, "GL_DRAW_BUFFER12", 0x8831);
	lua_pushenumuration(L, "GL_DRAW_BUFFER13", 0x8832);
	lua_pushenumuration(L, "GL_DRAW_BUFFER14", 0x8833);
	lua_pushenumuration(L, "GL_DRAW_BUFFER15", 0x8834);
	lua_pushenumuration(L, "GL_BLEND_EQUATION_ALPHA", 0x883D);
	lua_pushenumuration(L, "GL_MAX_VERTEX_ATTRIBS", 0x8869);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_NORMALIZED", 0x886A);
	lua_pushenumuration(L, "GL_MAX_TEXTURE_IMAGE_UNITS", 0x8872);
	lua_pushenumuration(L, "GL_FRAGMENT_SHADER", 0x8B30);
	lua_pushenumuration(L, "GL_VERTEX_SHADER", 0x8B31);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS", 0x8B49);
	lua_pushenumuration(L, "GL_MAX_VERTEX_UNIFORM_COMPONENTS", 0x8B4A);
	lua_pushenumuration(L, "GL_MAX_VARYING_FLOATS", 0x8B4B);
	lua_pushenumuration(L, "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS", 0x8B4C);
	lua_pushenumuration(L, "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS", 0x8B4D);
	lua_pushenumuration(L, "GL_SHADER_TYPE", 0x8B4F);
	lua_pushenumuration(L, "GL_FLOAT_VEC2", 0x8B50);
	lua_pushenumuration(L, "GL_FLOAT_VEC3", 0x8B51);
	lua_pushenumuration(L, "GL_FLOAT_VEC4", 0x8B52);
	lua_pushenumuration(L, "GL_INT_VEC2", 0x8B53);
	lua_pushenumuration(L, "GL_INT_VEC3", 0x8B54);
	lua_pushenumuration(L, "GL_INT_VEC4", 0x8B55);
	lua_pushenumuration(L, "GL_BOOL", 0x8B56);
	lua_pushenumuration(L, "GL_BOOL_VEC2", 0x8B57);
	lua_pushenumuration(L, "GL_BOOL_VEC3", 0x8B58);
	lua_pushenumuration(L, "GL_BOOL_VEC4", 0x8B59);
	lua_pushenumuration(L, "GL_FLOAT_MAT2", 0x8B5A);
	lua_pushenumuration(L, "GL_FLOAT_MAT3", 0x8B5B);
	lua_pushenumuration(L, "GL_FLOAT_MAT4", 0x8B5C);
	lua_pushenumuration(L, "GL_SAMPLER_1D", 0x8B5D);
	lua_pushenumuration(L, "GL_SAMPLER_2D", 0x8B5E);
	lua_pushenumuration(L, "GL_SAMPLER_3D", 0x8B5F);
	lua_pushenumuration(L, "GL_SAMPLER_CUBE", 0x8B60);
	lua_pushenumuration(L, "GL_SAMPLER_1D_SHADOW", 0x8B61);
	lua_pushenumuration(L, "GL_SAMPLER_2D_SHADOW", 0x8B62);
	lua_pushenumuration(L, "GL_DELETE_STATUS", 0x8B80);
	lua_pushenumuration(L, "GL_COMPILE_STATUS", 0x8B81);
	lua_pushenumuration(L, "GL_LINK_STATUS", 0x8B82);
	lua_pushenumuration(L, "GL_VALIDATE_STATUS", 0x8B83);
	lua_pushenumuration(L, "GL_INFO_LOG_LENGTH", 0x8B84);
	lua_pushenumuration(L, "GL_ATTACHED_SHADERS", 0x8B85);
	lua_pushenumuration(L, "GL_ACTIVE_UNIFORMS", 0x8B86);
	lua_pushenumuration(L, "GL_ACTIVE_UNIFORM_MAX_LENGTH", 0x8B87);
	lua_pushenumuration(L, "GL_SHADER_SOURCE_LENGTH", 0x8B88);
	lua_pushenumuration(L, "GL_ACTIVE_ATTRIBUTES", 0x8B89);
	lua_pushenumuration(L, "GL_ACTIVE_ATTRIBUTE_MAX_LENGTH", 0x8B8A);
	lua_pushenumuration(L, "GL_FRAGMENT_SHADER_DERIVATIVE_HINT", 0x8B8B);
	lua_pushenumuration(L, "GL_SHADING_LANGUAGE_VERSION", 0x8B8C);
	lua_pushenumuration(L, "GL_CURRENT_PROGRAM", 0x8B8D);
	lua_pushenumuration(L, "GL_POINT_SPRITE_COORD_ORIGIN", 0x8CA0);
	lua_pushenumuration(L, "GL_LOWER_LEFT", 0x8CA1);
	lua_pushenumuration(L, "GL_UPPER_LEFT", 0x8CA2);
	lua_pushenumuration(L, "GL_STENCIL_BACK_REF", 0x8CA3);
	lua_pushenumuration(L, "GL_STENCIL_BACK_VALUE_MASK", 0x8CA4);
	lua_pushenumuration(L, "GL_STENCIL_BACK_WRITEMASK", 0x8CA5);
#endif
#ifdef GL_VERSION_2_1
	lua_pushenumuration(L, "GL_PIXEL_PACK_BUFFER", 0x88EB);
	lua_pushenumuration(L, "GL_PIXEL_UNPACK_BUFFER", 0x88EC);
	lua_pushenumuration(L, "GL_PIXEL_PACK_BUFFER_BINDING", 0x88ED);
	lua_pushenumuration(L, "GL_PIXEL_UNPACK_BUFFER_BINDING", 0x88EF);
	lua_pushenumuration(L, "GL_FLOAT_MAT2x3", 0x8B65);
	lua_pushenumuration(L, "GL_FLOAT_MAT2x4", 0x8B66);
	lua_pushenumuration(L, "GL_FLOAT_MAT3x2", 0x8B67);
	lua_pushenumuration(L, "GL_FLOAT_MAT3x4", 0x8B68);
	lua_pushenumuration(L, "GL_FLOAT_MAT4x2", 0x8B69);
	lua_pushenumuration(L, "GL_FLOAT_MAT4x3", 0x8B6A);
	lua_pushenumuration(L, "GL_SRGB", 0x8C40);
	lua_pushenumuration(L, "GL_SRGB8", 0x8C41);
	lua_pushenumuration(L, "GL_SRGB_ALPHA", 0x8C42);
	lua_pushenumuration(L, "GL_SRGB8_ALPHA8", 0x8C43);
	lua_pushenumuration(L, "GL_COMPRESSED_SRGB", 0x8C48);
	lua_pushenumuration(L, "GL_COMPRESSED_SRGB_ALPHA", 0x8C49);
#endif
#ifdef GL_VERSION_3_0
	lua_pushenumuration(L, "GL_COMPARE_REF_TO_TEXTURE", 0x884E);
	lua_pushenumuration(L, "GL_CLIP_DISTANCE0", 0x3000);
	lua_pushenumuration(L, "GL_CLIP_DISTANCE1", 0x3001);
	lua_pushenumuration(L, "GL_CLIP_DISTANCE2", 0x3002);
	lua_pushenumuration(L, "GL_CLIP_DISTANCE3", 0x3003);
	lua_pushenumuration(L, "GL_CLIP_DISTANCE4", 0x3004);
	lua_pushenumuration(L, "GL_CLIP_DISTANCE5", 0x3005);
	lua_pushenumuration(L, "GL_CLIP_DISTANCE6", 0x3006);
	lua_pushenumuration(L, "GL_CLIP_DISTANCE7", 0x3007);
	lua_pushenumuration(L, "GL_MAX_CLIP_DISTANCES", 0x0D32);
	lua_pushenumuration(L, "GL_MAJOR_VERSION", 0x821B);
	lua_pushenumuration(L, "GL_MINOR_VERSION", 0x821C);
	lua_pushenumuration(L, "GL_NUM_EXTENSIONS", 0x821D);
	lua_pushenumuration(L, "GL_CONTEXT_FLAGS", 0x821E);
	lua_pushenumuration(L, "GL_COMPRESSED_RED", 0x8225);
	lua_pushenumuration(L, "GL_COMPRESSED_RG", 0x8226);
	lua_pushenumuration(L, "GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT", 0x0001);
	lua_pushenumuration(L, "GL_RGBA32F", 0x8814);
	lua_pushenumuration(L, "GL_RGB32F", 0x8815);
	lua_pushenumuration(L, "GL_RGBA16F", 0x881A);
	lua_pushenumuration(L, "GL_RGB16F", 0x881B);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_INTEGER", 0x88FD);
	lua_pushenumuration(L, "GL_MAX_ARRAY_TEXTURE_LAYERS", 0x88FF);
	lua_pushenumuration(L, "GL_MIN_PROGRAM_TEXEL_OFFSET", 0x8904);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_TEXEL_OFFSET", 0x8905);
	lua_pushenumuration(L, "GL_CLAMP_READ_COLOR", 0x891C);
	lua_pushenumuration(L, "GL_FIXED_ONLY", 0x891D);
	lua_pushenumuration(L, "GL_MAX_VARYING_COMPONENTS", 0x8B4B);
	lua_pushenumuration(L, "GL_TEXTURE_1D_ARRAY", 0x8C18);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_1D_ARRAY", 0x8C19);
	lua_pushenumuration(L, "GL_TEXTURE_2D_ARRAY", 0x8C1A);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_2D_ARRAY", 0x8C1B);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_1D_ARRAY", 0x8C1C);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_2D_ARRAY", 0x8C1D);
	lua_pushenumuration(L, "GL_R11F_G11F_B10F", 0x8C3A);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_10F_11F_11F_REV", 0x8C3B);
	lua_pushenumuration(L, "GL_RGB9_E5", 0x8C3D);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_5_9_9_9_REV", 0x8C3E);
	lua_pushenumuration(L, "GL_TEXTURE_SHARED_SIZE", 0x8C3F);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH", 0x8C76);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_BUFFER_MODE", 0x8C7F);
	lua_pushenumuration(L, "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS", 0x8C80);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_VARYINGS", 0x8C83);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_BUFFER_START", 0x8C84);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_BUFFER_SIZE", 0x8C85);
	lua_pushenumuration(L, "GL_PRIMITIVES_GENERATED", 0x8C87);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN", 0x8C88);
	lua_pushenumuration(L, "GL_RASTERIZER_DISCARD", 0x8C89);
	lua_pushenumuration(L, "GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS", 0x8C8A);
	lua_pushenumuration(L, "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS", 0x8C8B);
	lua_pushenumuration(L, "GL_INTERLEAVED_ATTRIBS", 0x8C8C);
	lua_pushenumuration(L, "GL_SEPARATE_ATTRIBS", 0x8C8D);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_BUFFER", 0x8C8E);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING", 0x8C8F);
	lua_pushenumuration(L, "GL_RGBA32UI", 0x8D70);
	lua_pushenumuration(L, "GL_RGB32UI", 0x8D71);
	lua_pushenumuration(L, "GL_RGBA16UI", 0x8D76);
	lua_pushenumuration(L, "GL_RGB16UI", 0x8D77);
	lua_pushenumuration(L, "GL_RGBA8UI", 0x8D7C);
	lua_pushenumuration(L, "GL_RGB8UI", 0x8D7D);
	lua_pushenumuration(L, "GL_RGBA32I", 0x8D82);
	lua_pushenumuration(L, "GL_RGB32I", 0x8D83);
	lua_pushenumuration(L, "GL_RGBA16I", 0x8D88);
	lua_pushenumuration(L, "GL_RGB16I", 0x8D89);
	lua_pushenumuration(L, "GL_RGBA8I", 0x8D8E);
	lua_pushenumuration(L, "GL_RGB8I", 0x8D8F);
	lua_pushenumuration(L, "GL_RED_INTEGER", 0x8D94);
	lua_pushenumuration(L, "GL_GREEN_INTEGER", 0x8D95);
	lua_pushenumuration(L, "GL_BLUE_INTEGER", 0x8D96);
	lua_pushenumuration(L, "GL_RGB_INTEGER", 0x8D98);
	lua_pushenumuration(L, "GL_RGBA_INTEGER", 0x8D99);
	lua_pushenumuration(L, "GL_BGR_INTEGER", 0x8D9A);
	lua_pushenumuration(L, "GL_BGRA_INTEGER", 0x8D9B);
	lua_pushenumuration(L, "GL_SAMPLER_1D_ARRAY", 0x8DC0);
	lua_pushenumuration(L, "GL_SAMPLER_2D_ARRAY", 0x8DC1);
	lua_pushenumuration(L, "GL_SAMPLER_1D_ARRAY_SHADOW", 0x8DC3);
	lua_pushenumuration(L, "GL_SAMPLER_2D_ARRAY_SHADOW", 0x8DC4);
	lua_pushenumuration(L, "GL_SAMPLER_CUBE_SHADOW", 0x8DC5);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_VEC2", 0x8DC6);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_VEC3", 0x8DC7);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_VEC4", 0x8DC8);
	lua_pushenumuration(L, "GL_INT_SAMPLER_1D", 0x8DC9);
	lua_pushenumuration(L, "GL_INT_SAMPLER_2D", 0x8DCA);
	lua_pushenumuration(L, "GL_INT_SAMPLER_3D", 0x8DCB);
	lua_pushenumuration(L, "GL_INT_SAMPLER_CUBE", 0x8DCC);
	lua_pushenumuration(L, "GL_INT_SAMPLER_1D_ARRAY", 0x8DCE);
	lua_pushenumuration(L, "GL_INT_SAMPLER_2D_ARRAY", 0x8DCF);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_1D", 0x8DD1);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_2D", 0x8DD2);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_3D", 0x8DD3);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_CUBE", 0x8DD4);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_1D_ARRAY", 0x8DD6);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY", 0x8DD7);
	lua_pushenumuration(L, "GL_QUERY_WAIT", 0x8E13);
	lua_pushenumuration(L, "GL_QUERY_NO_WAIT", 0x8E14);
	lua_pushenumuration(L, "GL_QUERY_BY_REGION_WAIT", 0x8E15);
	lua_pushenumuration(L, "GL_QUERY_BY_REGION_NO_WAIT", 0x8E16);
	lua_pushenumuration(L, "GL_BUFFER_ACCESS_FLAGS", 0x911F);
	lua_pushenumuration(L, "GL_BUFFER_MAP_LENGTH", 0x9120);
	lua_pushenumuration(L, "GL_BUFFER_MAP_OFFSET", 0x9121);
#endif
#ifdef GL_VERSION_3_1
	lua_pushenumuration(L, "GL_SAMPLER_2D_RECT", 0x8B63);
	lua_pushenumuration(L, "GL_SAMPLER_2D_RECT_SHADOW", 0x8B64);
	lua_pushenumuration(L, "GL_SAMPLER_BUFFER", 0x8DC2);
	lua_pushenumuration(L, "GL_INT_SAMPLER_2D_RECT", 0x8DCD);
	lua_pushenumuration(L, "GL_INT_SAMPLER_BUFFER", 0x8DD0);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_2D_RECT", 0x8DD5);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_BUFFER", 0x8DD8);
	lua_pushenumuration(L, "GL_TEXTURE_BUFFER", 0x8C2A);
	lua_pushenumuration(L, "GL_MAX_TEXTURE_BUFFER_SIZE", 0x8C2B);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_BUFFER", 0x8C2C);
	lua_pushenumuration(L, "GL_TEXTURE_BUFFER_DATA_STORE_BINDING", 0x8C2D);
	lua_pushenumuration(L, "GL_TEXTURE_BUFFER_FORMAT", 0x8C2E);
	lua_pushenumuration(L, "GL_TEXTURE_RECTANGLE", 0x84F5);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_RECTANGLE", 0x84F6);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_RECTANGLE", 0x84F7);
	lua_pushenumuration(L, "GL_MAX_RECTANGLE_TEXTURE_SIZE", 0x84F8);
	lua_pushenumuration(L, "GL_RED_SNORM", 0x8F90);
	lua_pushenumuration(L, "GL_RG_SNORM", 0x8F91);
	lua_pushenumuration(L, "GL_RGB_SNORM", 0x8F92);
	lua_pushenumuration(L, "GL_RGBA_SNORM", 0x8F93);
	lua_pushenumuration(L, "GL_R8_SNORM", 0x8F94);
	lua_pushenumuration(L, "GL_RG8_SNORM", 0x8F95);
	lua_pushenumuration(L, "GL_RGB8_SNORM", 0x8F96);
	lua_pushenumuration(L, "GL_RGBA8_SNORM", 0x8F97);
	lua_pushenumuration(L, "GL_R16_SNORM", 0x8F98);
	lua_pushenumuration(L, "GL_RG16_SNORM", 0x8F99);
	lua_pushenumuration(L, "GL_RGB16_SNORM", 0x8F9A);
	lua_pushenumuration(L, "GL_RGBA16_SNORM", 0x8F9B);
	lua_pushenumuration(L, "GL_SIGNED_NORMALIZED", 0x8F9C);
	lua_pushenumuration(L, "GL_PRIMITIVE_RESTART", 0x8F9D);
	lua_pushenumuration(L, "GL_PRIMITIVE_RESTART_INDEX", 0x8F9E);
#endif
#ifdef GL_VERSION_3_2
	lua_pushenumuration(L, "GL_CONTEXT_CORE_PROFILE_BIT", 0x00000001);
	lua_pushenumuration(L, "GL_CONTEXT_COMPATIBILITY_PROFILE_BIT", 0x00000002);
	lua_pushenumuration(L, "GL_LINES_ADJACENCY", 0x000A);
	lua_pushenumuration(L, "GL_LINE_STRIP_ADJACENCY", 0x000B);
	lua_pushenumuration(L, "GL_TRIANGLES_ADJACENCY", 0x000C);
	lua_pushenumuration(L, "GL_TRIANGLE_STRIP_ADJACENCY", 0x000D);
	lua_pushenumuration(L, "GL_PROGRAM_POINT_SIZE", 0x8642);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS", 0x8C29);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_LAYERED", 0x8DA7);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS", 0x8DA8);
	lua_pushenumuration(L, "GL_GEOMETRY_SHADER", 0x8DD9);
	lua_pushenumuration(L, "GL_GEOMETRY_VERTICES_OUT", 0x8916);
	lua_pushenumuration(L, "GL_GEOMETRY_INPUT_TYPE", 0x8917);
	lua_pushenumuration(L, "GL_GEOMETRY_OUTPUT_TYPE", 0x8918);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_UNIFORM_COMPONENTS", 0x8DDF);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_OUTPUT_VERTICES", 0x8DE0);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS", 0x8DE1);
	lua_pushenumuration(L, "GL_MAX_VERTEX_OUTPUT_COMPONENTS", 0x9122);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_INPUT_COMPONENTS", 0x9123);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_OUTPUT_COMPONENTS", 0x9124);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_INPUT_COMPONENTS", 0x9125);
	lua_pushenumuration(L, "GL_CONTEXT_PROFILE_MASK", 0x9126);
#endif
#ifdef GL_VERSION_3_3
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_DIVISOR", 0x88FE);
#endif
#ifdef GL_VERSION_4_0
	lua_pushenumuration(L, "GL_SAMPLE_SHADING", 0x8C36);
	lua_pushenumuration(L, "GL_MIN_SAMPLE_SHADING_VALUE", 0x8C37);
	lua_pushenumuration(L, "GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET", 0x8E5E);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET", 0x8E5F);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_ARRAY", 0x9009);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_CUBE_MAP_ARRAY", 0x900A);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_CUBE_MAP_ARRAY", 0x900B);
	lua_pushenumuration(L, "GL_SAMPLER_CUBE_MAP_ARRAY", 0x900C);
	lua_pushenumuration(L, "GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW", 0x900D);
	lua_pushenumuration(L, "GL_INT_SAMPLER_CUBE_MAP_ARRAY", 0x900E);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY", 0x900F);
#endif
#ifdef GL_VERSION_4_1
#endif
#ifdef GL_VERSION_4_2
#endif
#ifdef GL_VERSION_4_3
	lua_pushenumuration(L, "GL_NUM_SHADING_LANGUAGE_VERSIONS", 0x82E9);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_LONG", 0x874E);
#endif
#ifdef GL_ARB_multitexture
	lua_pushenumuration(L, "GL_TEXTURE0_ARB", 0x84C0);
	lua_pushenumuration(L, "GL_TEXTURE1_ARB", 0x84C1);
	lua_pushenumuration(L, "GL_TEXTURE2_ARB", 0x84C2);
	lua_pushenumuration(L, "GL_TEXTURE3_ARB", 0x84C3);
	lua_pushenumuration(L, "GL_TEXTURE4_ARB", 0x84C4);
	lua_pushenumuration(L, "GL_TEXTURE5_ARB", 0x84C5);
	lua_pushenumuration(L, "GL_TEXTURE6_ARB", 0x84C6);
	lua_pushenumuration(L, "GL_TEXTURE7_ARB", 0x84C7);
	lua_pushenumuration(L, "GL_TEXTURE8_ARB", 0x84C8);
	lua_pushenumuration(L, "GL_TEXTURE9_ARB", 0x84C9);
	lua_pushenumuration(L, "GL_TEXTURE10_ARB", 0x84CA);
	lua_pushenumuration(L, "GL_TEXTURE11_ARB", 0x84CB);
	lua_pushenumuration(L, "GL_TEXTURE12_ARB", 0x84CC);
	lua_pushenumuration(L, "GL_TEXTURE13_ARB", 0x84CD);
	lua_pushenumuration(L, "GL_TEXTURE14_ARB", 0x84CE);
	lua_pushenumuration(L, "GL_TEXTURE15_ARB", 0x84CF);
	lua_pushenumuration(L, "GL_TEXTURE16_ARB", 0x84D0);
	lua_pushenumuration(L, "GL_TEXTURE17_ARB", 0x84D1);
	lua_pushenumuration(L, "GL_TEXTURE18_ARB", 0x84D2);
	lua_pushenumuration(L, "GL_TEXTURE19_ARB", 0x84D3);
	lua_pushenumuration(L, "GL_TEXTURE20_ARB", 0x84D4);
	lua_pushenumuration(L, "GL_TEXTURE21_ARB", 0x84D5);
	lua_pushenumuration(L, "GL_TEXTURE22_ARB", 0x84D6);
	lua_pushenumuration(L, "GL_TEXTURE23_ARB", 0x84D7);
	lua_pushenumuration(L, "GL_TEXTURE24_ARB", 0x84D8);
	lua_pushenumuration(L, "GL_TEXTURE25_ARB", 0x84D9);
	lua_pushenumuration(L, "GL_TEXTURE26_ARB", 0x84DA);
	lua_pushenumuration(L, "GL_TEXTURE27_ARB", 0x84DB);
	lua_pushenumuration(L, "GL_TEXTURE28_ARB", 0x84DC);
	lua_pushenumuration(L, "GL_TEXTURE29_ARB", 0x84DD);
	lua_pushenumuration(L, "GL_TEXTURE30_ARB", 0x84DE);
	lua_pushenumuration(L, "GL_TEXTURE31_ARB", 0x84DF);
	lua_pushenumuration(L, "GL_ACTIVE_TEXTURE_ARB", 0x84E0);
	lua_pushenumuration(L, "GL_CLIENT_ACTIVE_TEXTURE_ARB", 0x84E1);
	lua_pushenumuration(L, "GL_MAX_TEXTURE_UNITS_ARB", 0x84E2);
#endif
#ifdef GL_ARB_transpose_matrix
	lua_pushenumuration(L, "GL_TRANSPOSE_MODELVIEW_MATRIX_ARB", 0x84E3);
	lua_pushenumuration(L, "GL_TRANSPOSE_PROJECTION_MATRIX_ARB", 0x84E4);
	lua_pushenumuration(L, "GL_TRANSPOSE_TEXTURE_MATRIX_ARB", 0x84E5);
	lua_pushenumuration(L, "GL_TRANSPOSE_COLOR_MATRIX_ARB", 0x84E6);
#endif
#ifdef GL_ARB_multisample
	lua_pushenumuration(L, "GL_MULTISAMPLE_ARB", 0x809D);
	lua_pushenumuration(L, "GL_SAMPLE_ALPHA_TO_COVERAGE_ARB", 0x809E);
	lua_pushenumuration(L, "GL_SAMPLE_ALPHA_TO_ONE_ARB", 0x809F);
	lua_pushenumuration(L, "GL_SAMPLE_COVERAGE_ARB", 0x80A0);
	lua_pushenumuration(L, "GL_SAMPLE_BUFFERS_ARB", 0x80A8);
	lua_pushenumuration(L, "GL_SAMPLES_ARB", 0x80A9);
	lua_pushenumuration(L, "GL_SAMPLE_COVERAGE_VALUE_ARB", 0x80AA);
	lua_pushenumuration(L, "GL_SAMPLE_COVERAGE_INVERT_ARB", 0x80AB);
	lua_pushenumuration(L, "GL_MULTISAMPLE_BIT_ARB", 0x20000000);
#endif
#ifdef GL_ARB_texture_env_add
#endif
#ifdef GL_ARB_texture_cube_map
	lua_pushenumuration(L, "GL_NORMAL_MAP_ARB", 0x8511);
	lua_pushenumuration(L, "GL_REFLECTION_MAP_ARB", 0x8512);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_ARB", 0x8513);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_CUBE_MAP_ARB", 0x8514);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB", 0x8515);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB", 0x8516);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB", 0x8517);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB", 0x8518);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB", 0x8519);
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB", 0x851A);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_CUBE_MAP_ARB", 0x851B);
	lua_pushenumuration(L, "GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB", 0x851C);
#endif
#ifdef GL_ARB_texture_compression
	lua_pushenumuration(L, "GL_COMPRESSED_ALPHA_ARB", 0x84E9);
	lua_pushenumuration(L, "GL_COMPRESSED_LUMINANCE_ARB", 0x84EA);
	lua_pushenumuration(L, "GL_COMPRESSED_LUMINANCE_ALPHA_ARB", 0x84EB);
	lua_pushenumuration(L, "GL_COMPRESSED_INTENSITY_ARB", 0x84EC);
	lua_pushenumuration(L, "GL_COMPRESSED_RGB_ARB", 0x84ED);
	lua_pushenumuration(L, "GL_COMPRESSED_RGBA_ARB", 0x84EE);
	lua_pushenumuration(L, "GL_TEXTURE_COMPRESSION_HINT_ARB", 0x84EF);
	lua_pushenumuration(L, "GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB", 0x86A0);
	lua_pushenumuration(L, "GL_TEXTURE_COMPRESSED_ARB", 0x86A1);
	lua_pushenumuration(L, "GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB", 0x86A2);
	lua_pushenumuration(L, "GL_COMPRESSED_TEXTURE_FORMATS_ARB", 0x86A3);
#endif
#ifdef GL_ARB_texture_border_clamp
	lua_pushenumuration(L, "GL_CLAMP_TO_BORDER_ARB", 0x812D);
#endif
#ifdef GL_ARB_point_parameters
	lua_pushenumuration(L, "GL_POINT_SIZE_MIN_ARB", 0x8126);
	lua_pushenumuration(L, "GL_POINT_SIZE_MAX_ARB", 0x8127);
	lua_pushenumuration(L, "GL_POINT_FADE_THRESHOLD_SIZE_ARB", 0x8128);
	lua_pushenumuration(L, "GL_POINT_DISTANCE_ATTENUATION_ARB", 0x8129);
#endif
#ifdef GL_ARB_vertex_blend
	lua_pushenumuration(L, "GL_MAX_VERTEX_UNITS_ARB", 0x86A4);
	lua_pushenumuration(L, "GL_ACTIVE_VERTEX_UNITS_ARB", 0x86A5);
	lua_pushenumuration(L, "GL_WEIGHT_SUM_UNITY_ARB", 0x86A6);
	lua_pushenumuration(L, "GL_VERTEX_BLEND_ARB", 0x86A7);
	lua_pushenumuration(L, "GL_CURRENT_WEIGHT_ARB", 0x86A8);
	lua_pushenumuration(L, "GL_WEIGHT_ARRAY_TYPE_ARB", 0x86A9);
	lua_pushenumuration(L, "GL_WEIGHT_ARRAY_STRIDE_ARB", 0x86AA);
	lua_pushenumuration(L, "GL_WEIGHT_ARRAY_SIZE_ARB", 0x86AB);
	lua_pushenumuration(L, "GL_WEIGHT_ARRAY_POINTER_ARB", 0x86AC);
	lua_pushenumuration(L, "GL_WEIGHT_ARRAY_ARB", 0x86AD);
	lua_pushenumuration(L, "GL_MODELVIEW0_ARB", 0x1700);
	lua_pushenumuration(L, "GL_MODELVIEW1_ARB", 0x850A);
	lua_pushenumuration(L, "GL_MODELVIEW2_ARB", 0x8722);
	lua_pushenumuration(L, "GL_MODELVIEW3_ARB", 0x8723);
	lua_pushenumuration(L, "GL_MODELVIEW4_ARB", 0x8724);
	lua_pushenumuration(L, "GL_MODELVIEW5_ARB", 0x8725);
	lua_pushenumuration(L, "GL_MODELVIEW6_ARB", 0x8726);
	lua_pushenumuration(L, "GL_MODELVIEW7_ARB", 0x8727);
	lua_pushenumuration(L, "GL_MODELVIEW8_ARB", 0x8728);
	lua_pushenumuration(L, "GL_MODELVIEW9_ARB", 0x8729);
	lua_pushenumuration(L, "GL_MODELVIEW10_ARB", 0x872A);
	lua_pushenumuration(L, "GL_MODELVIEW11_ARB", 0x872B);
	lua_pushenumuration(L, "GL_MODELVIEW12_ARB", 0x872C);
	lua_pushenumuration(L, "GL_MODELVIEW13_ARB", 0x872D);
	lua_pushenumuration(L, "GL_MODELVIEW14_ARB", 0x872E);
	lua_pushenumuration(L, "GL_MODELVIEW15_ARB", 0x872F);
	lua_pushenumuration(L, "GL_MODELVIEW16_ARB", 0x8730);
	lua_pushenumuration(L, "GL_MODELVIEW17_ARB", 0x8731);
	lua_pushenumuration(L, "GL_MODELVIEW18_ARB", 0x8732);
	lua_pushenumuration(L, "GL_MODELVIEW19_ARB", 0x8733);
	lua_pushenumuration(L, "GL_MODELVIEW20_ARB", 0x8734);
	lua_pushenumuration(L, "GL_MODELVIEW21_ARB", 0x8735);
	lua_pushenumuration(L, "GL_MODELVIEW22_ARB", 0x8736);
	lua_pushenumuration(L, "GL_MODELVIEW23_ARB", 0x8737);
	lua_pushenumuration(L, "GL_MODELVIEW24_ARB", 0x8738);
	lua_pushenumuration(L, "GL_MODELVIEW25_ARB", 0x8739);
	lua_pushenumuration(L, "GL_MODELVIEW26_ARB", 0x873A);
	lua_pushenumuration(L, "GL_MODELVIEW27_ARB", 0x873B);
	lua_pushenumuration(L, "GL_MODELVIEW28_ARB", 0x873C);
	lua_pushenumuration(L, "GL_MODELVIEW29_ARB", 0x873D);
	lua_pushenumuration(L, "GL_MODELVIEW30_ARB", 0x873E);
	lua_pushenumuration(L, "GL_MODELVIEW31_ARB", 0x873F);
#endif
#ifdef GL_ARB_matrix_palette
	lua_pushenumuration(L, "GL_MATRIX_PALETTE_ARB", 0x8840);
	lua_pushenumuration(L, "GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB", 0x8841);
	lua_pushenumuration(L, "GL_MAX_PALETTE_MATRICES_ARB", 0x8842);
	lua_pushenumuration(L, "GL_CURRENT_PALETTE_MATRIX_ARB", 0x8843);
	lua_pushenumuration(L, "GL_MATRIX_INDEX_ARRAY_ARB", 0x8844);
	lua_pushenumuration(L, "GL_CURRENT_MATRIX_INDEX_ARB", 0x8845);
	lua_pushenumuration(L, "GL_MATRIX_INDEX_ARRAY_SIZE_ARB", 0x8846);
	lua_pushenumuration(L, "GL_MATRIX_INDEX_ARRAY_TYPE_ARB", 0x8847);
	lua_pushenumuration(L, "GL_MATRIX_INDEX_ARRAY_STRIDE_ARB", 0x8848);
	lua_pushenumuration(L, "GL_MATRIX_INDEX_ARRAY_POINTER_ARB", 0x8849);
#endif
#ifdef GL_ARB_texture_env_combine
	lua_pushenumuration(L, "GL_COMBINE_ARB", 0x8570);
	lua_pushenumuration(L, "GL_COMBINE_RGB_ARB", 0x8571);
	lua_pushenumuration(L, "GL_COMBINE_ALPHA_ARB", 0x8572);
	lua_pushenumuration(L, "GL_SOURCE0_RGB_ARB", 0x8580);
	lua_pushenumuration(L, "GL_SOURCE1_RGB_ARB", 0x8581);
	lua_pushenumuration(L, "GL_SOURCE2_RGB_ARB", 0x8582);
	lua_pushenumuration(L, "GL_SOURCE0_ALPHA_ARB", 0x8588);
	lua_pushenumuration(L, "GL_SOURCE1_ALPHA_ARB", 0x8589);
	lua_pushenumuration(L, "GL_SOURCE2_ALPHA_ARB", 0x858A);
	lua_pushenumuration(L, "GL_OPERAND0_RGB_ARB", 0x8590);
	lua_pushenumuration(L, "GL_OPERAND1_RGB_ARB", 0x8591);
	lua_pushenumuration(L, "GL_OPERAND2_RGB_ARB", 0x8592);
	lua_pushenumuration(L, "GL_OPERAND0_ALPHA_ARB", 0x8598);
	lua_pushenumuration(L, "GL_OPERAND1_ALPHA_ARB", 0x8599);
	lua_pushenumuration(L, "GL_OPERAND2_ALPHA_ARB", 0x859A);
	lua_pushenumuration(L, "GL_RGB_SCALE_ARB", 0x8573);
	lua_pushenumuration(L, "GL_ADD_SIGNED_ARB", 0x8574);
	lua_pushenumuration(L, "GL_INTERPOLATE_ARB", 0x8575);
	lua_pushenumuration(L, "GL_SUBTRACT_ARB", 0x84E7);
	lua_pushenumuration(L, "GL_CONSTANT_ARB", 0x8576);
	lua_pushenumuration(L, "GL_PRIMARY_COLOR_ARB", 0x8577);
	lua_pushenumuration(L, "GL_PREVIOUS_ARB", 0x8578);
#endif
#ifdef GL_ARB_texture_env_crossbar
#endif
#ifdef GL_ARB_texture_env_dot3
	lua_pushenumuration(L, "GL_DOT3_RGB_ARB", 0x86AE);
	lua_pushenumuration(L, "GL_DOT3_RGBA_ARB", 0x86AF);
#endif
#ifdef GL_ARB_texture_mirrored_repeat
	lua_pushenumuration(L, "GL_MIRRORED_REPEAT_ARB", 0x8370);
#endif
#ifdef GL_ARB_depth_texture
	lua_pushenumuration(L, "GL_DEPTH_COMPONENT16_ARB", 0x81A5);
	lua_pushenumuration(L, "GL_DEPTH_COMPONENT24_ARB", 0x81A6);
	lua_pushenumuration(L, "GL_DEPTH_COMPONENT32_ARB", 0x81A7);
	lua_pushenumuration(L, "GL_TEXTURE_DEPTH_SIZE_ARB", 0x884A);
	lua_pushenumuration(L, "GL_DEPTH_TEXTURE_MODE_ARB", 0x884B);
#endif
#ifdef GL_ARB_shadow
	lua_pushenumuration(L, "GL_TEXTURE_COMPARE_MODE_ARB", 0x884C);
	lua_pushenumuration(L, "GL_TEXTURE_COMPARE_FUNC_ARB", 0x884D);
	lua_pushenumuration(L, "GL_COMPARE_R_TO_TEXTURE_ARB", 0x884E);
#endif
#ifdef GL_ARB_shadow_ambient
	lua_pushenumuration(L, "GL_TEXTURE_COMPARE_FAIL_VALUE_ARB", 0x80BF);
#endif
#ifdef GL_ARB_window_pos
#endif
#ifdef GL_ARB_vertex_program
	lua_pushenumuration(L, "GL_COLOR_SUM_ARB", 0x8458);
	lua_pushenumuration(L, "GL_VERTEX_PROGRAM_ARB", 0x8620);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB", 0x8622);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB", 0x8623);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB", 0x8624);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB", 0x8625);
	lua_pushenumuration(L, "GL_CURRENT_VERTEX_ATTRIB_ARB", 0x8626);
	lua_pushenumuration(L, "GL_PROGRAM_LENGTH_ARB", 0x8627);
	lua_pushenumuration(L, "GL_PROGRAM_STRING_ARB", 0x8628);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB", 0x862E);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_MATRICES_ARB", 0x862F);
	lua_pushenumuration(L, "GL_CURRENT_MATRIX_STACK_DEPTH_ARB", 0x8640);
	lua_pushenumuration(L, "GL_CURRENT_MATRIX_ARB", 0x8641);
	lua_pushenumuration(L, "GL_VERTEX_PROGRAM_POINT_SIZE_ARB", 0x8642);
	lua_pushenumuration(L, "GL_VERTEX_PROGRAM_TWO_SIDE_ARB", 0x8643);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB", 0x8645);
	lua_pushenumuration(L, "GL_PROGRAM_ERROR_POSITION_ARB", 0x864B);
	lua_pushenumuration(L, "GL_PROGRAM_BINDING_ARB", 0x8677);
	lua_pushenumuration(L, "GL_MAX_VERTEX_ATTRIBS_ARB", 0x8869);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB", 0x886A);
	lua_pushenumuration(L, "GL_PROGRAM_ERROR_STRING_ARB", 0x8874);
	lua_pushenumuration(L, "GL_PROGRAM_FORMAT_ASCII_ARB", 0x8875);
	lua_pushenumuration(L, "GL_PROGRAM_FORMAT_ARB", 0x8876);
	lua_pushenumuration(L, "GL_PROGRAM_INSTRUCTIONS_ARB", 0x88A0);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_INSTRUCTIONS_ARB", 0x88A1);
	lua_pushenumuration(L, "GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB", 0x88A2);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB", 0x88A3);
	lua_pushenumuration(L, "GL_PROGRAM_TEMPORARIES_ARB", 0x88A4);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_TEMPORARIES_ARB", 0x88A5);
	lua_pushenumuration(L, "GL_PROGRAM_NATIVE_TEMPORARIES_ARB", 0x88A6);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB", 0x88A7);
	lua_pushenumuration(L, "GL_PROGRAM_PARAMETERS_ARB", 0x88A8);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_PARAMETERS_ARB", 0x88A9);
	lua_pushenumuration(L, "GL_PROGRAM_NATIVE_PARAMETERS_ARB", 0x88AA);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB", 0x88AB);
	lua_pushenumuration(L, "GL_PROGRAM_ATTRIBS_ARB", 0x88AC);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_ATTRIBS_ARB", 0x88AD);
	lua_pushenumuration(L, "GL_PROGRAM_NATIVE_ATTRIBS_ARB", 0x88AE);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB", 0x88AF);
	lua_pushenumuration(L, "GL_PROGRAM_ADDRESS_REGISTERS_ARB", 0x88B0);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB", 0x88B1);
	lua_pushenumuration(L, "GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB", 0x88B2);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB", 0x88B3);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB", 0x88B4);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_ENV_PARAMETERS_ARB", 0x88B5);
	lua_pushenumuration(L, "GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB", 0x88B6);
	lua_pushenumuration(L, "GL_TRANSPOSE_CURRENT_MATRIX_ARB", 0x88B7);
	lua_pushenumuration(L, "GL_MATRIX0_ARB", 0x88C0);
	lua_pushenumuration(L, "GL_MATRIX1_ARB", 0x88C1);
	lua_pushenumuration(L, "GL_MATRIX2_ARB", 0x88C2);
	lua_pushenumuration(L, "GL_MATRIX3_ARB", 0x88C3);
	lua_pushenumuration(L, "GL_MATRIX4_ARB", 0x88C4);
	lua_pushenumuration(L, "GL_MATRIX5_ARB", 0x88C5);
	lua_pushenumuration(L, "GL_MATRIX6_ARB", 0x88C6);
	lua_pushenumuration(L, "GL_MATRIX7_ARB", 0x88C7);
	lua_pushenumuration(L, "GL_MATRIX8_ARB", 0x88C8);
	lua_pushenumuration(L, "GL_MATRIX9_ARB", 0x88C9);
	lua_pushenumuration(L, "GL_MATRIX10_ARB", 0x88CA);
	lua_pushenumuration(L, "GL_MATRIX11_ARB", 0x88CB);
	lua_pushenumuration(L, "GL_MATRIX12_ARB", 0x88CC);
	lua_pushenumuration(L, "GL_MATRIX13_ARB", 0x88CD);
	lua_pushenumuration(L, "GL_MATRIX14_ARB", 0x88CE);
	lua_pushenumuration(L, "GL_MATRIX15_ARB", 0x88CF);
	lua_pushenumuration(L, "GL_MATRIX16_ARB", 0x88D0);
	lua_pushenumuration(L, "GL_MATRIX17_ARB", 0x88D1);
	lua_pushenumuration(L, "GL_MATRIX18_ARB", 0x88D2);
	lua_pushenumuration(L, "GL_MATRIX19_ARB", 0x88D3);
	lua_pushenumuration(L, "GL_MATRIX20_ARB", 0x88D4);
	lua_pushenumuration(L, "GL_MATRIX21_ARB", 0x88D5);
	lua_pushenumuration(L, "GL_MATRIX22_ARB", 0x88D6);
	lua_pushenumuration(L, "GL_MATRIX23_ARB", 0x88D7);
	lua_pushenumuration(L, "GL_MATRIX24_ARB", 0x88D8);
	lua_pushenumuration(L, "GL_MATRIX25_ARB", 0x88D9);
	lua_pushenumuration(L, "GL_MATRIX26_ARB", 0x88DA);
	lua_pushenumuration(L, "GL_MATRIX27_ARB", 0x88DB);
	lua_pushenumuration(L, "GL_MATRIX28_ARB", 0x88DC);
	lua_pushenumuration(L, "GL_MATRIX29_ARB", 0x88DD);
	lua_pushenumuration(L, "GL_MATRIX30_ARB", 0x88DE);
	lua_pushenumuration(L, "GL_MATRIX31_ARB", 0x88DF);
#endif
#ifdef GL_ARB_fragment_program
	lua_pushenumuration(L, "GL_FRAGMENT_PROGRAM_ARB", 0x8804);
	lua_pushenumuration(L, "GL_PROGRAM_ALU_INSTRUCTIONS_ARB", 0x8805);
	lua_pushenumuration(L, "GL_PROGRAM_TEX_INSTRUCTIONS_ARB", 0x8806);
	lua_pushenumuration(L, "GL_PROGRAM_TEX_INDIRECTIONS_ARB", 0x8807);
	lua_pushenumuration(L, "GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB", 0x8808);
	lua_pushenumuration(L, "GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB", 0x8809);
	lua_pushenumuration(L, "GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB", 0x880A);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB", 0x880B);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB", 0x880C);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB", 0x880D);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB", 0x880E);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB", 0x880F);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB", 0x8810);
	lua_pushenumuration(L, "GL_MAX_TEXTURE_COORDS_ARB", 0x8871);
	lua_pushenumuration(L, "GL_MAX_TEXTURE_IMAGE_UNITS_ARB", 0x8872);
#endif
#ifdef GL_ARB_vertex_buffer_object
	lua_pushenumuration(L, "GL_BUFFER_SIZE_ARB", 0x8764);
	lua_pushenumuration(L, "GL_BUFFER_USAGE_ARB", 0x8765);
	lua_pushenumuration(L, "GL_ARRAY_BUFFER_ARB", 0x8892);
	lua_pushenumuration(L, "GL_ELEMENT_ARRAY_BUFFER_ARB", 0x8893);
	lua_pushenumuration(L, "GL_ARRAY_BUFFER_BINDING_ARB", 0x8894);
	lua_pushenumuration(L, "GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB", 0x8895);
	lua_pushenumuration(L, "GL_VERTEX_ARRAY_BUFFER_BINDING_ARB", 0x8896);
	lua_pushenumuration(L, "GL_NORMAL_ARRAY_BUFFER_BINDING_ARB", 0x8897);
	lua_pushenumuration(L, "GL_COLOR_ARRAY_BUFFER_BINDING_ARB", 0x8898);
	lua_pushenumuration(L, "GL_INDEX_ARRAY_BUFFER_BINDING_ARB", 0x8899);
	lua_pushenumuration(L, "GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB", 0x889A);
	lua_pushenumuration(L, "GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB", 0x889B);
	lua_pushenumuration(L, "GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB", 0x889C);
	lua_pushenumuration(L, "GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB", 0x889D);
	lua_pushenumuration(L, "GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB", 0x889E);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB", 0x889F);
	lua_pushenumuration(L, "GL_READ_ONLY_ARB", 0x88B8);
	lua_pushenumuration(L, "GL_WRITE_ONLY_ARB", 0x88B9);
	lua_pushenumuration(L, "GL_READ_WRITE_ARB", 0x88BA);
	lua_pushenumuration(L, "GL_BUFFER_ACCESS_ARB", 0x88BB);
	lua_pushenumuration(L, "GL_BUFFER_MAPPED_ARB", 0x88BC);
	lua_pushenumuration(L, "GL_BUFFER_MAP_POINTER_ARB", 0x88BD);
	lua_pushenumuration(L, "GL_STREAM_DRAW_ARB", 0x88E0);
	lua_pushenumuration(L, "GL_STREAM_READ_ARB", 0x88E1);
	lua_pushenumuration(L, "GL_STREAM_COPY_ARB", 0x88E2);
	lua_pushenumuration(L, "GL_STATIC_DRAW_ARB", 0x88E4);
	lua_pushenumuration(L, "GL_STATIC_READ_ARB", 0x88E5);
	lua_pushenumuration(L, "GL_STATIC_COPY_ARB", 0x88E6);
	lua_pushenumuration(L, "GL_DYNAMIC_DRAW_ARB", 0x88E8);
	lua_pushenumuration(L, "GL_DYNAMIC_READ_ARB", 0x88E9);
	lua_pushenumuration(L, "GL_DYNAMIC_COPY_ARB", 0x88EA);
#endif
#ifdef GL_ARB_occlusion_query
	lua_pushenumuration(L, "GL_QUERY_COUNTER_BITS_ARB", 0x8864);
	lua_pushenumuration(L, "GL_CURRENT_QUERY_ARB", 0x8865);
	lua_pushenumuration(L, "GL_QUERY_RESULT_ARB", 0x8866);
	lua_pushenumuration(L, "GL_QUERY_RESULT_AVAILABLE_ARB", 0x8867);
	lua_pushenumuration(L, "GL_SAMPLES_PASSED_ARB", 0x8914);
#endif
#ifdef GL_ARB_shader_objects
	lua_pushenumuration(L, "GL_PROGRAM_OBJECT_ARB", 0x8B40);
	lua_pushenumuration(L, "GL_SHADER_OBJECT_ARB", 0x8B48);
	lua_pushenumuration(L, "GL_OBJECT_TYPE_ARB", 0x8B4E);
	lua_pushenumuration(L, "GL_OBJECT_SUBTYPE_ARB", 0x8B4F);
	lua_pushenumuration(L, "GL_FLOAT_VEC2_ARB", 0x8B50);
	lua_pushenumuration(L, "GL_FLOAT_VEC3_ARB", 0x8B51);
	lua_pushenumuration(L, "GL_FLOAT_VEC4_ARB", 0x8B52);
	lua_pushenumuration(L, "GL_INT_VEC2_ARB", 0x8B53);
	lua_pushenumuration(L, "GL_INT_VEC3_ARB", 0x8B54);
	lua_pushenumuration(L, "GL_INT_VEC4_ARB", 0x8B55);
	lua_pushenumuration(L, "GL_BOOL_ARB", 0x8B56);
	lua_pushenumuration(L, "GL_BOOL_VEC2_ARB", 0x8B57);
	lua_pushenumuration(L, "GL_BOOL_VEC3_ARB", 0x8B58);
	lua_pushenumuration(L, "GL_BOOL_VEC4_ARB", 0x8B59);
	lua_pushenumuration(L, "GL_FLOAT_MAT2_ARB", 0x8B5A);
	lua_pushenumuration(L, "GL_FLOAT_MAT3_ARB", 0x8B5B);
	lua_pushenumuration(L, "GL_FLOAT_MAT4_ARB", 0x8B5C);
	lua_pushenumuration(L, "GL_SAMPLER_1D_ARB", 0x8B5D);
	lua_pushenumuration(L, "GL_SAMPLER_2D_ARB", 0x8B5E);
	lua_pushenumuration(L, "GL_SAMPLER_3D_ARB", 0x8B5F);
	lua_pushenumuration(L, "GL_SAMPLER_CUBE_ARB", 0x8B60);
	lua_pushenumuration(L, "GL_SAMPLER_1D_SHADOW_ARB", 0x8B61);
	lua_pushenumuration(L, "GL_SAMPLER_2D_SHADOW_ARB", 0x8B62);
	lua_pushenumuration(L, "GL_SAMPLER_2D_RECT_ARB", 0x8B63);
	lua_pushenumuration(L, "GL_SAMPLER_2D_RECT_SHADOW_ARB", 0x8B64);
	lua_pushenumuration(L, "GL_OBJECT_DELETE_STATUS_ARB", 0x8B80);
	lua_pushenumuration(L, "GL_OBJECT_COMPILE_STATUS_ARB", 0x8B81);
	lua_pushenumuration(L, "GL_OBJECT_LINK_STATUS_ARB", 0x8B82);
	lua_pushenumuration(L, "GL_OBJECT_VALIDATE_STATUS_ARB", 0x8B83);
	lua_pushenumuration(L, "GL_OBJECT_INFO_LOG_LENGTH_ARB", 0x8B84);
	lua_pushenumuration(L, "GL_OBJECT_ATTACHED_OBJECTS_ARB", 0x8B85);
	lua_pushenumuration(L, "GL_OBJECT_ACTIVE_UNIFORMS_ARB", 0x8B86);
	lua_pushenumuration(L, "GL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB", 0x8B87);
	lua_pushenumuration(L, "GL_OBJECT_SHADER_SOURCE_LENGTH_ARB", 0x8B88);
#endif
#ifdef GL_ARB_vertex_shader
	lua_pushenumuration(L, "GL_VERTEX_SHADER_ARB", 0x8B31);
	lua_pushenumuration(L, "GL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB", 0x8B4A);
	lua_pushenumuration(L, "GL_MAX_VARYING_FLOATS_ARB", 0x8B4B);
	lua_pushenumuration(L, "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB", 0x8B4C);
	lua_pushenumuration(L, "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB", 0x8B4D);
	lua_pushenumuration(L, "GL_OBJECT_ACTIVE_ATTRIBUTES_ARB", 0x8B89);
	lua_pushenumuration(L, "GL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB", 0x8B8A);
#endif
#ifdef GL_ARB_fragment_shader
	lua_pushenumuration(L, "GL_FRAGMENT_SHADER_ARB", 0x8B30);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB", 0x8B49);
	lua_pushenumuration(L, "GL_FRAGMENT_SHADER_DERIVATIVE_HINT_ARB", 0x8B8B);
#endif
#ifdef GL_ARB_shading_language_100
	lua_pushenumuration(L, "GL_SHADING_LANGUAGE_VERSION_ARB", 0x8B8C);
#endif
#ifdef GL_ARB_texture_non_power_of_two
#endif
#ifdef GL_ARB_point_sprite
	lua_pushenumuration(L, "GL_POINT_SPRITE_ARB", 0x8861);
	lua_pushenumuration(L, "GL_COORD_REPLACE_ARB", 0x8862);
#endif
#ifdef GL_ARB_fragment_program_shadow
#endif
#ifdef GL_ARB_draw_buffers
	lua_pushenumuration(L, "GL_MAX_DRAW_BUFFERS_ARB", 0x8824);
	lua_pushenumuration(L, "GL_DRAW_BUFFER0_ARB", 0x8825);
	lua_pushenumuration(L, "GL_DRAW_BUFFER1_ARB", 0x8826);
	lua_pushenumuration(L, "GL_DRAW_BUFFER2_ARB", 0x8827);
	lua_pushenumuration(L, "GL_DRAW_BUFFER3_ARB", 0x8828);
	lua_pushenumuration(L, "GL_DRAW_BUFFER4_ARB", 0x8829);
	lua_pushenumuration(L, "GL_DRAW_BUFFER5_ARB", 0x882A);
	lua_pushenumuration(L, "GL_DRAW_BUFFER6_ARB", 0x882B);
	lua_pushenumuration(L, "GL_DRAW_BUFFER7_ARB", 0x882C);
	lua_pushenumuration(L, "GL_DRAW_BUFFER8_ARB", 0x882D);
	lua_pushenumuration(L, "GL_DRAW_BUFFER9_ARB", 0x882E);
	lua_pushenumuration(L, "GL_DRAW_BUFFER10_ARB", 0x882F);
	lua_pushenumuration(L, "GL_DRAW_BUFFER11_ARB", 0x8830);
	lua_pushenumuration(L, "GL_DRAW_BUFFER12_ARB", 0x8831);
	lua_pushenumuration(L, "GL_DRAW_BUFFER13_ARB", 0x8832);
	lua_pushenumuration(L, "GL_DRAW_BUFFER14_ARB", 0x8833);
	lua_pushenumuration(L, "GL_DRAW_BUFFER15_ARB", 0x8834);
#endif
#ifdef GL_ARB_texture_rectangle
	lua_pushenumuration(L, "GL_TEXTURE_RECTANGLE_ARB", 0x84F5);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_RECTANGLE_ARB", 0x84F6);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_RECTANGLE_ARB", 0x84F7);
	lua_pushenumuration(L, "GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB", 0x84F8);
#endif
#ifdef GL_ARB_color_buffer_float
	lua_pushenumuration(L, "GL_RGBA_FLOAT_MODE_ARB", 0x8820);
	lua_pushenumuration(L, "GL_CLAMP_VERTEX_COLOR_ARB", 0x891A);
	lua_pushenumuration(L, "GL_CLAMP_FRAGMENT_COLOR_ARB", 0x891B);
	lua_pushenumuration(L, "GL_CLAMP_READ_COLOR_ARB", 0x891C);
	lua_pushenumuration(L, "GL_FIXED_ONLY_ARB", 0x891D);
#endif
#ifdef GL_ARB_half_float_pixel
	lua_pushenumuration(L, "GL_HALF_FLOAT_ARB", 0x140B);
#endif
#ifdef GL_ARB_texture_float
	lua_pushenumuration(L, "GL_TEXTURE_RED_TYPE_ARB", 0x8C10);
	lua_pushenumuration(L, "GL_TEXTURE_GREEN_TYPE_ARB", 0x8C11);
	lua_pushenumuration(L, "GL_TEXTURE_BLUE_TYPE_ARB", 0x8C12);
	lua_pushenumuration(L, "GL_TEXTURE_ALPHA_TYPE_ARB", 0x8C13);
	lua_pushenumuration(L, "GL_TEXTURE_LUMINANCE_TYPE_ARB", 0x8C14);
	lua_pushenumuration(L, "GL_TEXTURE_INTENSITY_TYPE_ARB", 0x8C15);
	lua_pushenumuration(L, "GL_TEXTURE_DEPTH_TYPE_ARB", 0x8C16);
	lua_pushenumuration(L, "GL_UNSIGNED_NORMALIZED_ARB", 0x8C17);
	lua_pushenumuration(L, "GL_RGBA32F_ARB", 0x8814);
	lua_pushenumuration(L, "GL_RGB32F_ARB", 0x8815);
	lua_pushenumuration(L, "GL_ALPHA32F_ARB", 0x8816);
	lua_pushenumuration(L, "GL_INTENSITY32F_ARB", 0x8817);
	lua_pushenumuration(L, "GL_LUMINANCE32F_ARB", 0x8818);
	lua_pushenumuration(L, "GL_LUMINANCE_ALPHA32F_ARB", 0x8819);
	lua_pushenumuration(L, "GL_RGBA16F_ARB", 0x881A);
	lua_pushenumuration(L, "GL_RGB16F_ARB", 0x881B);
	lua_pushenumuration(L, "GL_ALPHA16F_ARB", 0x881C);
	lua_pushenumuration(L, "GL_INTENSITY16F_ARB", 0x881D);
	lua_pushenumuration(L, "GL_LUMINANCE16F_ARB", 0x881E);
	lua_pushenumuration(L, "GL_LUMINANCE_ALPHA16F_ARB", 0x881F);
#endif
#ifdef GL_ARB_pixel_buffer_object
	lua_pushenumuration(L, "GL_PIXEL_PACK_BUFFER_ARB", 0x88EB);
	lua_pushenumuration(L, "GL_PIXEL_UNPACK_BUFFER_ARB", 0x88EC);
	lua_pushenumuration(L, "GL_PIXEL_PACK_BUFFER_BINDING_ARB", 0x88ED);
	lua_pushenumuration(L, "GL_PIXEL_UNPACK_BUFFER_BINDING_ARB", 0x88EF);
#endif
#ifdef GL_ARB_depth_buffer_float
	lua_pushenumuration(L, "GL_DEPTH_COMPONENT32F", 0x8CAC);
	lua_pushenumuration(L, "GL_DEPTH32F_STENCIL8", 0x8CAD);
	lua_pushenumuration(L, "GL_FLOAT_32_UNSIGNED_INT_24_8_REV", 0x8DAD);
#endif
#ifdef GL_ARB_draw_instanced
#endif
#ifdef GL_ARB_framebuffer_object
	lua_pushenumuration(L, "GL_INVALID_FRAMEBUFFER_OPERATION", 0x0506);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING", 0x8210);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE", 0x8211);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE", 0x8212);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE", 0x8213);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE", 0x8214);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE", 0x8215);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE", 0x8216);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE", 0x8217);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_DEFAULT", 0x8218);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_UNDEFINED", 0x8219);
	lua_pushenumuration(L, "GL_DEPTH_STENCIL_ATTACHMENT", 0x821A);
	lua_pushenumuration(L, "GL_MAX_RENDERBUFFER_SIZE", 0x84E8);
	lua_pushenumuration(L, "GL_DEPTH_STENCIL", 0x84F9);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_24_8", 0x84FA);
	lua_pushenumuration(L, "GL_DEPTH24_STENCIL8", 0x88F0);
	lua_pushenumuration(L, "GL_TEXTURE_STENCIL_SIZE", 0x88F1);
	lua_pushenumuration(L, "GL_TEXTURE_RED_TYPE", 0x8C10);
	lua_pushenumuration(L, "GL_TEXTURE_GREEN_TYPE", 0x8C11);
	lua_pushenumuration(L, "GL_TEXTURE_BLUE_TYPE", 0x8C12);
	lua_pushenumuration(L, "GL_TEXTURE_ALPHA_TYPE", 0x8C13);
	lua_pushenumuration(L, "GL_TEXTURE_DEPTH_TYPE", 0x8C16);
	lua_pushenumuration(L, "GL_UNSIGNED_NORMALIZED", 0x8C17);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_BINDING", 0x8CA6);
	lua_pushenumuration(L, "GL_DRAW_FRAMEBUFFER_BINDING", GL_FRAMEBUFFER_BINDING);
	lua_pushenumuration(L, "GL_RENDERBUFFER_BINDING", 0x8CA7);
	lua_pushenumuration(L, "GL_READ_FRAMEBUFFER", 0x8CA8);
	lua_pushenumuration(L, "GL_DRAW_FRAMEBUFFER", 0x8CA9);
	lua_pushenumuration(L, "GL_READ_FRAMEBUFFER_BINDING", 0x8CAA);
	lua_pushenumuration(L, "GL_RENDERBUFFER_SAMPLES", 0x8CAB);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE", 0x8CD0);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME", 0x8CD1);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL", 0x8CD2);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE", 0x8CD3);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER", 0x8CD4);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_COMPLETE", 0x8CD5);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT", 0x8CD6);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT", 0x8CD7);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER", 0x8CDB);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER", 0x8CDC);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_UNSUPPORTED", 0x8CDD);
	lua_pushenumuration(L, "GL_MAX_COLOR_ATTACHMENTS", 0x8CDF);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT0", 0x8CE0);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT1", 0x8CE1);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT2", 0x8CE2);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT3", 0x8CE3);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT4", 0x8CE4);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT5", 0x8CE5);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT6", 0x8CE6);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT7", 0x8CE7);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT8", 0x8CE8);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT9", 0x8CE9);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT10", 0x8CEA);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT11", 0x8CEB);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT12", 0x8CEC);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT13", 0x8CED);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT14", 0x8CEE);
	lua_pushenumuration(L, "GL_COLOR_ATTACHMENT15", 0x8CEF);
	lua_pushenumuration(L, "GL_DEPTH_ATTACHMENT", 0x8D00);
	lua_pushenumuration(L, "GL_STENCIL_ATTACHMENT", 0x8D20);
	lua_pushenumuration(L, "GL_FRAMEBUFFER", 0x8D40);
	lua_pushenumuration(L, "GL_RENDERBUFFER", 0x8D41);
	lua_pushenumuration(L, "GL_RENDERBUFFER_WIDTH", 0x8D42);
	lua_pushenumuration(L, "GL_RENDERBUFFER_HEIGHT", 0x8D43);
	lua_pushenumuration(L, "GL_RENDERBUFFER_INTERNAL_FORMAT", 0x8D44);
	lua_pushenumuration(L, "GL_STENCIL_INDEX1", 0x8D46);
	lua_pushenumuration(L, "GL_STENCIL_INDEX4", 0x8D47);
	lua_pushenumuration(L, "GL_STENCIL_INDEX8", 0x8D48);
	lua_pushenumuration(L, "GL_STENCIL_INDEX16", 0x8D49);
	lua_pushenumuration(L, "GL_RENDERBUFFER_RED_SIZE", 0x8D50);
	lua_pushenumuration(L, "GL_RENDERBUFFER_GREEN_SIZE", 0x8D51);
	lua_pushenumuration(L, "GL_RENDERBUFFER_BLUE_SIZE", 0x8D52);
	lua_pushenumuration(L, "GL_RENDERBUFFER_ALPHA_SIZE", 0x8D53);
	lua_pushenumuration(L, "GL_RENDERBUFFER_DEPTH_SIZE", 0x8D54);
	lua_pushenumuration(L, "GL_RENDERBUFFER_STENCIL_SIZE", 0x8D55);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE", 0x8D56);
	lua_pushenumuration(L, "GL_MAX_SAMPLES", 0x8D57);
#endif
#ifdef GL_ARB_framebuffer_sRGB
	lua_pushenumuration(L, "GL_FRAMEBUFFER_SRGB", 0x8DB9);
#endif
#ifdef GL_ARB_geometry_shader4
	lua_pushenumuration(L, "GL_LINES_ADJACENCY_ARB", 0x000A);
	lua_pushenumuration(L, "GL_LINE_STRIP_ADJACENCY_ARB", 0x000B);
	lua_pushenumuration(L, "GL_TRIANGLES_ADJACENCY_ARB", 0x000C);
	lua_pushenumuration(L, "GL_TRIANGLE_STRIP_ADJACENCY_ARB", 0x000D);
	lua_pushenumuration(L, "GL_PROGRAM_POINT_SIZE_ARB", 0x8642);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_ARB", 0x8C29);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_ATTACHMENT_LAYERED_ARB", 0x8DA7);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_ARB", 0x8DA8);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB", 0x8DA9);
	lua_pushenumuration(L, "GL_GEOMETRY_SHADER_ARB", 0x8DD9);
	lua_pushenumuration(L, "GL_GEOMETRY_VERTICES_OUT_ARB", 0x8DDA);
	lua_pushenumuration(L, "GL_GEOMETRY_INPUT_TYPE_ARB", 0x8DDB);
	lua_pushenumuration(L, "GL_GEOMETRY_OUTPUT_TYPE_ARB", 0x8DDC);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB", 0x8DDD);
	lua_pushenumuration(L, "GL_MAX_VERTEX_VARYING_COMPONENTS_ARB", 0x8DDE);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_ARB", 0x8DDF);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_OUTPUT_VERTICES_ARB", 0x8DE0);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_ARB", 0x8DE1);
#endif
#ifdef GL_ARB_half_float_vertex
	lua_pushenumuration(L, "GL_HALF_FLOAT", 0x140B);
#endif
#ifdef GL_ARB_instanced_arrays
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ARB", 0x88FE);
#endif
#ifdef GL_ARB_map_buffer_range
	lua_pushenumuration(L, "GL_MAP_READ_BIT", 0x0001);
	lua_pushenumuration(L, "GL_MAP_WRITE_BIT", 0x0002);
	lua_pushenumuration(L, "GL_MAP_INVALIDATE_RANGE_BIT", 0x0004);
	lua_pushenumuration(L, "GL_MAP_INVALIDATE_BUFFER_BIT", 0x0008);
	lua_pushenumuration(L, "GL_MAP_FLUSH_EXPLICIT_BIT", 0x0010);
	lua_pushenumuration(L, "GL_MAP_UNSYNCHRONIZED_BIT", 0x0020);
#endif
#ifdef GL_ARB_texture_buffer_object
	lua_pushenumuration(L, "GL_TEXTURE_BUFFER_ARB", 0x8C2A);
	lua_pushenumuration(L, "GL_MAX_TEXTURE_BUFFER_SIZE_ARB", 0x8C2B);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_BUFFER_ARB", 0x8C2C);
	lua_pushenumuration(L, "GL_TEXTURE_BUFFER_DATA_STORE_BINDING_ARB", 0x8C2D);
	lua_pushenumuration(L, "GL_TEXTURE_BUFFER_FORMAT_ARB", 0x8C2E);
#endif
#ifdef GL_ARB_texture_compression_rgtc
	lua_pushenumuration(L, "GL_COMPRESSED_RED_RGTC1", 0x8DBB);
	lua_pushenumuration(L, "GL_COMPRESSED_SIGNED_RED_RGTC1", 0x8DBC);
	lua_pushenumuration(L, "GL_COMPRESSED_RG_RGTC2", 0x8DBD);
	lua_pushenumuration(L, "GL_COMPRESSED_SIGNED_RG_RGTC2", 0x8DBE);
#endif
#ifdef GL_ARB_texture_rg
	lua_pushenumuration(L, "GL_RG", 0x8227);
	lua_pushenumuration(L, "GL_RG_INTEGER", 0x8228);
	lua_pushenumuration(L, "GL_R8", 0x8229);
	lua_pushenumuration(L, "GL_R16", 0x822A);
	lua_pushenumuration(L, "GL_RG8", 0x822B);
	lua_pushenumuration(L, "GL_RG16", 0x822C);
	lua_pushenumuration(L, "GL_R16F", 0x822D);
	lua_pushenumuration(L, "GL_R32F", 0x822E);
	lua_pushenumuration(L, "GL_RG16F", 0x822F);
	lua_pushenumuration(L, "GL_RG32F", 0x8230);
	lua_pushenumuration(L, "GL_R8I", 0x8231);
	lua_pushenumuration(L, "GL_R8UI", 0x8232);
	lua_pushenumuration(L, "GL_R16I", 0x8233);
	lua_pushenumuration(L, "GL_R16UI", 0x8234);
	lua_pushenumuration(L, "GL_R32I", 0x8235);
	lua_pushenumuration(L, "GL_R32UI", 0x8236);
	lua_pushenumuration(L, "GL_RG8I", 0x8237);
	lua_pushenumuration(L, "GL_RG8UI", 0x8238);
	lua_pushenumuration(L, "GL_RG16I", 0x8239);
	lua_pushenumuration(L, "GL_RG16UI", 0x823A);
	lua_pushenumuration(L, "GL_RG32I", 0x823B);
	lua_pushenumuration(L, "GL_RG32UI", 0x823C);
#endif
#ifdef GL_ARB_vertex_array_object
	lua_pushenumuration(L, "GL_VERTEX_ARRAY_BINDING", 0x85B5);
#endif
#ifdef GL_ARB_uniform_buffer_object
	lua_pushenumuration(L, "GL_UNIFORM_BUFFER", 0x8A11);
	lua_pushenumuration(L, "GL_UNIFORM_BUFFER_BINDING", 0x8A28);
	lua_pushenumuration(L, "GL_UNIFORM_BUFFER_START", 0x8A29);
	lua_pushenumuration(L, "GL_UNIFORM_BUFFER_SIZE", 0x8A2A);
	lua_pushenumuration(L, "GL_MAX_VERTEX_UNIFORM_BLOCKS", 0x8A2B);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_UNIFORM_BLOCKS", 0x8A2C);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_UNIFORM_BLOCKS", 0x8A2D);
	lua_pushenumuration(L, "GL_MAX_COMBINED_UNIFORM_BLOCKS", 0x8A2E);
	lua_pushenumuration(L, "GL_MAX_UNIFORM_BUFFER_BINDINGS", 0x8A2F);
	lua_pushenumuration(L, "GL_MAX_UNIFORM_BLOCK_SIZE", 0x8A30);
	lua_pushenumuration(L, "GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS", 0x8A31);
	lua_pushenumuration(L, "GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS", 0x8A32);
	lua_pushenumuration(L, "GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS", 0x8A33);
	lua_pushenumuration(L, "GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT", 0x8A34);
	lua_pushenumuration(L, "GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH", 0x8A35);
	lua_pushenumuration(L, "GL_ACTIVE_UNIFORM_BLOCKS", 0x8A36);
	lua_pushenumuration(L, "GL_UNIFORM_TYPE", 0x8A37);
	lua_pushenumuration(L, "GL_UNIFORM_SIZE", 0x8A38);
	lua_pushenumuration(L, "GL_UNIFORM_NAME_LENGTH", 0x8A39);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_INDEX", 0x8A3A);
	lua_pushenumuration(L, "GL_UNIFORM_OFFSET", 0x8A3B);
	lua_pushenumuration(L, "GL_UNIFORM_ARRAY_STRIDE", 0x8A3C);
	lua_pushenumuration(L, "GL_UNIFORM_MATRIX_STRIDE", 0x8A3D);
	lua_pushenumuration(L, "GL_UNIFORM_IS_ROW_MAJOR", 0x8A3E);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_BINDING", 0x8A3F);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_DATA_SIZE", 0x8A40);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_NAME_LENGTH", 0x8A41);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS", 0x8A42);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES", 0x8A43);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER", 0x8A44);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER", 0x8A45);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER", 0x8A46);
	lua_pushenumuration(L, "GL_INVALID_INDEX", 0xFFFFFFFFu);
#endif
#ifdef GL_ARB_compatibility
#endif
#ifdef GL_ARB_copy_buffer
	lua_pushenumuration(L, "GL_COPY_READ_BUFFER_BINDING", 0x8F36);
	//lua_pushenumuration(L, "GL_COPY_READ_BUFFER", GL_COPY_READ_BUFFER_BINDING);
	lua_pushenumuration(L, "GL_COPY_WRITE_BUFFER_BINDING", 0x8F37);
	//lua_pushenumuration(L, "GL_COPY_WRITE_BUFFER", GL_COPY_WRITE_BUFFER_BINDING);
#endif
#ifdef GL_ARB_shader_texture_lod
#endif
#ifdef GL_ARB_depth_clamp
	lua_pushenumuration(L, "GL_DEPTH_CLAMP", 0x864F);
#endif
#ifdef GL_ARB_draw_elements_base_vertex
#endif
#ifdef GL_ARB_fragment_coord_conventions
#endif
#ifdef GL_ARB_provoking_vertex
	lua_pushenumuration(L, "GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION", 0x8E4C);
	lua_pushenumuration(L, "GL_FIRST_VERTEX_CONVENTION", 0x8E4D);
	lua_pushenumuration(L, "GL_LAST_VERTEX_CONVENTION", 0x8E4E);
	lua_pushenumuration(L, "GL_PROVOKING_VERTEX", 0x8E4F);
#endif
#ifdef GL_ARB_seamless_cube_map
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_SEAMLESS", 0x884F);
#endif
#ifdef GL_ARB_sync
	lua_pushenumuration(L, "GL_MAX_SERVER_WAIT_TIMEOUT", 0x9111);
	lua_pushenumuration(L, "GL_OBJECT_TYPE", 0x9112);
	lua_pushenumuration(L, "GL_SYNC_CONDITION", 0x9113);
	lua_pushenumuration(L, "GL_SYNC_STATUS", 0x9114);
	lua_pushenumuration(L, "GL_SYNC_FLAGS", 0x9115);
	lua_pushenumuration(L, "GL_SYNC_FENCE", 0x9116);
	lua_pushenumuration(L, "GL_SYNC_GPU_COMMANDS_COMPLETE", 0x9117);
	lua_pushenumuration(L, "GL_UNSIGNALED", 0x9118);
	lua_pushenumuration(L, "GL_SIGNALED", 0x9119);
	lua_pushenumuration(L, "GL_ALREADY_SIGNALED", 0x911A);
	lua_pushenumuration(L, "GL_TIMEOUT_EXPIRED", 0x911B);
	lua_pushenumuration(L, "GL_CONDITION_SATISFIED", 0x911C);
	lua_pushenumuration(L, "GL_WAIT_FAILED", 0x911D);
	lua_pushenumuration(L, "GL_SYNC_FLUSH_COMMANDS_BIT", 0x00000001);
	lua_pushenumuration(L, "GL_TIMEOUT_IGNORED", 0xFFFFFFFFFFFFFFFFull);
#endif
#ifdef GL_ARB_texture_multisample
	lua_pushenumuration(L, "GL_SAMPLE_POSITION", 0x8E50);
	lua_pushenumuration(L, "GL_SAMPLE_MASK", 0x8E51);
	lua_pushenumuration(L, "GL_SAMPLE_MASK_VALUE", 0x8E52);
	lua_pushenumuration(L, "GL_MAX_SAMPLE_MASK_WORDS", 0x8E59);
	lua_pushenumuration(L, "GL_TEXTURE_2D_MULTISAMPLE", 0x9100);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_2D_MULTISAMPLE", 0x9101);
	lua_pushenumuration(L, "GL_TEXTURE_2D_MULTISAMPLE_ARRAY", 0x9102);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY", 0x9103);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_2D_MULTISAMPLE", 0x9104);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY", 0x9105);
	lua_pushenumuration(L, "GL_TEXTURE_SAMPLES", 0x9106);
	lua_pushenumuration(L, "GL_TEXTURE_FIXED_SAMPLE_LOCATIONS", 0x9107);
	lua_pushenumuration(L, "GL_SAMPLER_2D_MULTISAMPLE", 0x9108);
	lua_pushenumuration(L, "GL_INT_SAMPLER_2D_MULTISAMPLE", 0x9109);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE", 0x910A);
	lua_pushenumuration(L, "GL_SAMPLER_2D_MULTISAMPLE_ARRAY", 0x910B);
	lua_pushenumuration(L, "GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY", 0x910C);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY", 0x910D);
	lua_pushenumuration(L, "GL_MAX_COLOR_TEXTURE_SAMPLES", 0x910E);
	lua_pushenumuration(L, "GL_MAX_DEPTH_TEXTURE_SAMPLES", 0x910F);
	lua_pushenumuration(L, "GL_MAX_INTEGER_SAMPLES", 0x9110);
#endif
#ifdef GL_ARB_vertex_array_bgra
#endif
#ifdef GL_ARB_draw_buffers_blend
#endif
#ifdef GL_ARB_sample_shading
	lua_pushenumuration(L, "GL_SAMPLE_SHADING_ARB", 0x8C36);
	lua_pushenumuration(L, "GL_MIN_SAMPLE_SHADING_VALUE_ARB", 0x8C37);
#endif
#ifdef GL_ARB_texture_cube_map_array
	lua_pushenumuration(L, "GL_TEXTURE_CUBE_MAP_ARRAY_ARB", 0x9009);
	lua_pushenumuration(L, "GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_ARB", 0x900A);
	lua_pushenumuration(L, "GL_PROXY_TEXTURE_CUBE_MAP_ARRAY_ARB", 0x900B);
	lua_pushenumuration(L, "GL_SAMPLER_CUBE_MAP_ARRAY_ARB", 0x900C);
	lua_pushenumuration(L, "GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_ARB", 0x900D);
	lua_pushenumuration(L, "GL_INT_SAMPLER_CUBE_MAP_ARRAY_ARB", 0x900E);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_ARB", 0x900F);
#endif
#ifdef GL_ARB_texture_gather
	lua_pushenumuration(L, "GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB", 0x8E5E);
	lua_pushenumuration(L, "GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_ARB", 0x8E5F);
#endif
#ifdef GL_ARB_texture_query_lod
#endif
#ifdef GL_ARB_shading_language_include
	lua_pushenumuration(L, "GL_SHADER_INCLUDE_ARB", 0x8DAE);
	lua_pushenumuration(L, "GL_NAMED_STRING_LENGTH_ARB", 0x8DE9);
	lua_pushenumuration(L, "GL_NAMED_STRING_TYPE_ARB", 0x8DEA);
#endif
#ifdef GL_ARB_texture_compression_bptc
	lua_pushenumuration(L, "GL_COMPRESSED_RGBA_BPTC_UNORM_ARB", 0x8E8C);
	lua_pushenumuration(L, "GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB", 0x8E8D);
	lua_pushenumuration(L, "GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB", 0x8E8E);
	lua_pushenumuration(L, "GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB", 0x8E8F);
#endif
#ifdef GL_ARB_blend_func_extended
	lua_pushenumuration(L, "GL_SRC1_COLOR", 0x88F9);
	lua_pushenumuration(L, "GL_ONE_MINUS_SRC1_COLOR", 0x88FA);
	lua_pushenumuration(L, "GL_ONE_MINUS_SRC1_ALPHA", 0x88FB);
	lua_pushenumuration(L, "GL_MAX_DUAL_SOURCE_DRAW_BUFFERS", 0x88FC);
#endif
#ifdef GL_ARB_explicit_attrib_location
#endif
#ifdef GL_ARB_occlusion_query2
	lua_pushenumuration(L, "GL_ANY_SAMPLES_PASSED", 0x8C2F);
#endif
#ifdef GL_ARB_sampler_objects
	lua_pushenumuration(L, "GL_SAMPLER_BINDING", 0x8919);
#endif
#ifdef GL_ARB_shader_bit_encoding
#endif
#ifdef GL_ARB_texture_rgb10_a2ui
	lua_pushenumuration(L, "GL_RGB10_A2UI", 0x906F);
#endif
#ifdef GL_ARB_texture_swizzle
	lua_pushenumuration(L, "GL_TEXTURE_SWIZZLE_R", 0x8E42);
	lua_pushenumuration(L, "GL_TEXTURE_SWIZZLE_G", 0x8E43);
	lua_pushenumuration(L, "GL_TEXTURE_SWIZZLE_B", 0x8E44);
	lua_pushenumuration(L, "GL_TEXTURE_SWIZZLE_A", 0x8E45);
	lua_pushenumuration(L, "GL_TEXTURE_SWIZZLE_RGBA", 0x8E46);
#endif
#ifdef GL_ARB_timer_query
	lua_pushenumuration(L, "GL_TIME_ELAPSED", 0x88BF);
	lua_pushenumuration(L, "GL_TIMESTAMP", 0x8E28);
#endif
#ifdef GL_ARB_vertex_type_2_10_10_10_rev
	lua_pushenumuration(L, "GL_INT_2_10_10_10_REV", 0x8D9F);
#endif
#ifdef GL_ARB_draw_indirect
	lua_pushenumuration(L, "GL_DRAW_INDIRECT_BUFFER", 0x8F3F);
	lua_pushenumuration(L, "GL_DRAW_INDIRECT_BUFFER_BINDING", 0x8F43);
#endif
#ifdef GL_ARB_gpu_shader5
	lua_pushenumuration(L, "GL_GEOMETRY_SHADER_INVOCATIONS", 0x887F);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_SHADER_INVOCATIONS", 0x8E5A);
	lua_pushenumuration(L, "GL_MIN_FRAGMENT_INTERPOLATION_OFFSET", 0x8E5B);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_INTERPOLATION_OFFSET", 0x8E5C);
	lua_pushenumuration(L, "GL_FRAGMENT_INTERPOLATION_OFFSET_BITS", 0x8E5D);
#endif
#ifdef GL_ARB_gpu_shader_fp64
	lua_pushenumuration(L, "GL_DOUBLE_VEC2", 0x8FFC);
	lua_pushenumuration(L, "GL_DOUBLE_VEC3", 0x8FFD);
	lua_pushenumuration(L, "GL_DOUBLE_VEC4", 0x8FFE);
	lua_pushenumuration(L, "GL_DOUBLE_MAT2", 0x8F46);
	lua_pushenumuration(L, "GL_DOUBLE_MAT3", 0x8F47);
	lua_pushenumuration(L, "GL_DOUBLE_MAT4", 0x8F48);
	lua_pushenumuration(L, "GL_DOUBLE_MAT2x3", 0x8F49);
	lua_pushenumuration(L, "GL_DOUBLE_MAT2x4", 0x8F4A);
	lua_pushenumuration(L, "GL_DOUBLE_MAT3x2", 0x8F4B);
	lua_pushenumuration(L, "GL_DOUBLE_MAT3x4", 0x8F4C);
	lua_pushenumuration(L, "GL_DOUBLE_MAT4x2", 0x8F4D);
	lua_pushenumuration(L, "GL_DOUBLE_MAT4x3", 0x8F4E);
#endif
#ifdef GL_ARB_shader_subroutine
	lua_pushenumuration(L, "GL_ACTIVE_SUBROUTINES", 0x8DE5);
	lua_pushenumuration(L, "GL_ACTIVE_SUBROUTINE_UNIFORMS", 0x8DE6);
	lua_pushenumuration(L, "GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS", 0x8E47);
	lua_pushenumuration(L, "GL_ACTIVE_SUBROUTINE_MAX_LENGTH", 0x8E48);
	lua_pushenumuration(L, "GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH", 0x8E49);
	lua_pushenumuration(L, "GL_MAX_SUBROUTINES", 0x8DE7);
	lua_pushenumuration(L, "GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS", 0x8DE8);
	lua_pushenumuration(L, "GL_NUM_COMPATIBLE_SUBROUTINES", 0x8E4A);
	lua_pushenumuration(L, "GL_COMPATIBLE_SUBROUTINES", 0x8E4B);
#endif
#ifdef GL_ARB_tessellation_shader
	lua_pushenumuration(L, "GL_PATCHES", 0x000E);
	lua_pushenumuration(L, "GL_PATCH_VERTICES", 0x8E72);
	lua_pushenumuration(L, "GL_PATCH_DEFAULT_INNER_LEVEL", 0x8E73);
	lua_pushenumuration(L, "GL_PATCH_DEFAULT_OUTER_LEVEL", 0x8E74);
	lua_pushenumuration(L, "GL_TESS_CONTROL_OUTPUT_VERTICES", 0x8E75);
	lua_pushenumuration(L, "GL_TESS_GEN_MODE", 0x8E76);
	lua_pushenumuration(L, "GL_TESS_GEN_SPACING", 0x8E77);
	lua_pushenumuration(L, "GL_TESS_GEN_VERTEX_ORDER", 0x8E78);
	lua_pushenumuration(L, "GL_TESS_GEN_POINT_MODE", 0x8E79);
	lua_pushenumuration(L, "GL_ISOLINES", 0x8E7A);
	lua_pushenumuration(L, "GL_FRACTIONAL_ODD", 0x8E7B);
	lua_pushenumuration(L, "GL_FRACTIONAL_EVEN", 0x8E7C);
	lua_pushenumuration(L, "GL_MAX_PATCH_VERTICES", 0x8E7D);
	lua_pushenumuration(L, "GL_MAX_TESS_GEN_LEVEL", 0x8E7E);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS", 0x8E7F);
	lua_pushenumuration(L, "GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS", 0x8E80);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS", 0x8E81);
	lua_pushenumuration(L, "GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS", 0x8E82);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS", 0x8E83);
	lua_pushenumuration(L, "GL_MAX_TESS_PATCH_COMPONENTS", 0x8E84);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS", 0x8E85);
	lua_pushenumuration(L, "GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS", 0x8E86);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS", 0x8E89);
	lua_pushenumuration(L, "GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS", 0x8E8A);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_INPUT_COMPONENTS", 0x886C);
	lua_pushenumuration(L, "GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS", 0x886D);
	lua_pushenumuration(L, "GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS", 0x8E1E);
	lua_pushenumuration(L, "GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS", 0x8E1F);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER", 0x84F0);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER", 0x84F1);
	lua_pushenumuration(L, "GL_TESS_EVALUATION_SHADER", 0x8E87);
	lua_pushenumuration(L, "GL_TESS_CONTROL_SHADER", 0x8E88);
#endif
#ifdef GL_ARB_texture_buffer_object_rgb32
#endif
#ifdef GL_ARB_transform_feedback2
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK", 0x8E22);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_PAUSED", 0x8E23);
	//lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED", GL_TRANSFORM_FEEDBACK_PAUSED);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_ACTIVE", 0x8E24);
	//lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE", GL_TRANSFORM_FEEDBACK_ACTIVE);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_BINDING", 0x8E25);
#endif
#ifdef GL_ARB_transform_feedback3
	lua_pushenumuration(L, "GL_MAX_TRANSFORM_FEEDBACK_BUFFERS", 0x8E70);
	lua_pushenumuration(L, "GL_MAX_VERTEX_STREAMS", 0x8E71);
#endif
#ifdef GL_ARB_ES2_compatibility
	lua_pushenumuration(L, "GL_FIXED", 0x140C);
	lua_pushenumuration(L, "GL_IMPLEMENTATION_COLOR_READ_TYPE", 0x8B9A);
	lua_pushenumuration(L, "GL_IMPLEMENTATION_COLOR_READ_FORMAT", 0x8B9B);
	lua_pushenumuration(L, "GL_LOW_FLOAT", 0x8DF0);
	lua_pushenumuration(L, "GL_MEDIUM_FLOAT", 0x8DF1);
	lua_pushenumuration(L, "GL_HIGH_FLOAT", 0x8DF2);
	lua_pushenumuration(L, "GL_LOW_INT", 0x8DF3);
	lua_pushenumuration(L, "GL_MEDIUM_INT", 0x8DF4);
	lua_pushenumuration(L, "GL_HIGH_INT", 0x8DF5);
	lua_pushenumuration(L, "GL_SHADER_COMPILER", 0x8DFA);
	lua_pushenumuration(L, "GL_NUM_SHADER_BINARY_FORMATS", 0x8DF9);
	lua_pushenumuration(L, "GL_MAX_VERTEX_UNIFORM_VECTORS", 0x8DFB);
	lua_pushenumuration(L, "GL_MAX_VARYING_VECTORS", 0x8DFC);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_UNIFORM_VECTORS", 0x8DFD);
	lua_pushenumuration(L, "GL_RGB565", 0x8D62);
#endif
#ifdef GL_ARB_get_program_binary
	lua_pushenumuration(L, "GL_PROGRAM_BINARY_RETRIEVABLE_HINT", 0x8257);
	lua_pushenumuration(L, "GL_PROGRAM_BINARY_LENGTH", 0x8741);
	lua_pushenumuration(L, "GL_NUM_PROGRAM_BINARY_FORMATS", 0x87FE);
	lua_pushenumuration(L, "GL_PROGRAM_BINARY_FORMATS", 0x87FF);
#endif
#ifdef GL_ARB_separate_shader_objects
	lua_pushenumuration(L, "GL_VERTEX_SHADER_BIT", 0x00000001);
	lua_pushenumuration(L, "GL_FRAGMENT_SHADER_BIT", 0x00000002);
	lua_pushenumuration(L, "GL_GEOMETRY_SHADER_BIT", 0x00000004);
	lua_pushenumuration(L, "GL_TESS_CONTROL_SHADER_BIT", 0x00000008);
	lua_pushenumuration(L, "GL_TESS_EVALUATION_SHADER_BIT", 0x00000010);
	lua_pushenumuration(L, "GL_ALL_SHADER_BITS", 0xFFFFFFFF);
	lua_pushenumuration(L, "GL_PROGRAM_SEPARABLE", 0x8258);
	lua_pushenumuration(L, "GL_ACTIVE_PROGRAM", 0x8259);
	lua_pushenumuration(L, "GL_PROGRAM_PIPELINE_BINDING", 0x825A);
#endif
#ifdef GL_ARB_shader_precision
#endif
#ifdef GL_ARB_vertex_attrib_64bit
#endif
#ifdef GL_ARB_viewport_array
	lua_pushenumuration(L, "GL_MAX_VIEWPORTS", 0x825B);
	lua_pushenumuration(L, "GL_VIEWPORT_SUBPIXEL_BITS", 0x825C);
	lua_pushenumuration(L, "GL_VIEWPORT_BOUNDS_RANGE", 0x825D);
	lua_pushenumuration(L, "GL_LAYER_PROVOKING_VERTEX", 0x825E);
	lua_pushenumuration(L, "GL_VIEWPORT_INDEX_PROVOKING_VERTEX", 0x825F);
	lua_pushenumuration(L, "GL_UNDEFINED_VERTEX", 0x8260);
#endif
#ifdef GL_ARB_cl_event
	lua_pushenumuration(L, "GL_SYNC_CL_EVENT_ARB", 0x8240);
	lua_pushenumuration(L, "GL_SYNC_CL_EVENT_COMPLETE_ARB", 0x8241);
#endif
#ifdef GL_ARB_debug_output
	lua_pushenumuration(L, "GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB", 0x8242);
	lua_pushenumuration(L, "GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_ARB", 0x8243);
	lua_pushenumuration(L, "GL_DEBUG_CALLBACK_FUNCTION_ARB", 0x8244);
	lua_pushenumuration(L, "GL_DEBUG_CALLBACK_USER_PARAM_ARB", 0x8245);
	lua_pushenumuration(L, "GL_DEBUG_SOURCE_API_ARB", 0x8246);
	lua_pushenumuration(L, "GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB", 0x8247);
	lua_pushenumuration(L, "GL_DEBUG_SOURCE_SHADER_COMPILER_ARB", 0x8248);
	lua_pushenumuration(L, "GL_DEBUG_SOURCE_THIRD_PARTY_ARB", 0x8249);
	lua_pushenumuration(L, "GL_DEBUG_SOURCE_APPLICATION_ARB", 0x824A);
	lua_pushenumuration(L, "GL_DEBUG_SOURCE_OTHER_ARB", 0x824B);
	lua_pushenumuration(L, "GL_DEBUG_TYPE_ERROR_ARB", 0x824C);
	lua_pushenumuration(L, "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB", 0x824D);
	lua_pushenumuration(L, "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB", 0x824E);
	lua_pushenumuration(L, "GL_DEBUG_TYPE_PORTABILITY_ARB", 0x824F);
	lua_pushenumuration(L, "GL_DEBUG_TYPE_PERFORMANCE_ARB", 0x8250);
	lua_pushenumuration(L, "GL_DEBUG_TYPE_OTHER_ARB", 0x8251);
	lua_pushenumuration(L, "GL_MAX_DEBUG_MESSAGE_LENGTH_ARB", 0x9143);
	lua_pushenumuration(L, "GL_MAX_DEBUG_LOGGED_MESSAGES_ARB", 0x9144);
	lua_pushenumuration(L, "GL_DEBUG_LOGGED_MESSAGES_ARB", 0x9145);
	lua_pushenumuration(L, "GL_DEBUG_SEVERITY_HIGH_ARB", 0x9146);
	lua_pushenumuration(L, "GL_DEBUG_SEVERITY_MEDIUM_ARB", 0x9147);
	lua_pushenumuration(L, "GL_DEBUG_SEVERITY_LOW_ARB", 0x9148);
#endif
#ifdef GL_ARB_robustness
	lua_pushenumuration(L, "GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT_ARB", 0x00000004);
	lua_pushenumuration(L, "GL_LOSE_CONTEXT_ON_RESET_ARB", 0x8252);
	lua_pushenumuration(L, "GL_GUILTY_CONTEXT_RESET_ARB", 0x8253);
	lua_pushenumuration(L, "GL_INNOCENT_CONTEXT_RESET_ARB", 0x8254);
	lua_pushenumuration(L, "GL_UNKNOWN_CONTEXT_RESET_ARB", 0x8255);
	lua_pushenumuration(L, "GL_RESET_NOTIFICATION_STRATEGY_ARB", 0x8256);
	lua_pushenumuration(L, "GL_NO_RESET_NOTIFICATION_ARB", 0x8261);
#endif
#ifdef GL_ARB_shader_stencil_export
#endif
#ifdef GL_ARB_base_instance
#endif
#ifdef GL_ARB_shading_language_420pack
#endif
#ifdef GL_ARB_transform_feedback_instanced
#endif
#ifdef GL_ARB_compressed_texture_pixel_storage
	lua_pushenumuration(L, "GL_UNPACK_COMPRESSED_BLOCK_WIDTH", 0x9127);
	lua_pushenumuration(L, "GL_UNPACK_COMPRESSED_BLOCK_HEIGHT", 0x9128);
	lua_pushenumuration(L, "GL_UNPACK_COMPRESSED_BLOCK_DEPTH", 0x9129);
	lua_pushenumuration(L, "GL_UNPACK_COMPRESSED_BLOCK_SIZE", 0x912A);
	lua_pushenumuration(L, "GL_PACK_COMPRESSED_BLOCK_WIDTH", 0x912B);
	lua_pushenumuration(L, "GL_PACK_COMPRESSED_BLOCK_HEIGHT", 0x912C);
	lua_pushenumuration(L, "GL_PACK_COMPRESSED_BLOCK_DEPTH", 0x912D);
	lua_pushenumuration(L, "GL_PACK_COMPRESSED_BLOCK_SIZE", 0x912E);
#endif
#ifdef GL_ARB_conservative_depth
#endif
#ifdef GL_ARB_internalformat_query
	lua_pushenumuration(L, "GL_NUM_SAMPLE_COUNTS", 0x9380);
#endif
#ifdef GL_ARB_map_buffer_alignment
	lua_pushenumuration(L, "GL_MIN_MAP_BUFFER_ALIGNMENT", 0x90BC);
#endif
#ifdef GL_ARB_shader_atomic_counters
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER", 0x92C0);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_BINDING", 0x92C1);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_START", 0x92C2);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_SIZE", 0x92C3);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE", 0x92C4);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS", 0x92C5);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES", 0x92C6);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER", 0x92C7);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER", 0x92C8);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER", 0x92C9);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER", 0x92CA);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER", 0x92CB);
	lua_pushenumuration(L, "GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS", 0x92CC);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS", 0x92CD);
	lua_pushenumuration(L, "GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS", 0x92CE);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS", 0x92CF);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS", 0x92D0);
	lua_pushenumuration(L, "GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS", 0x92D1);
	lua_pushenumuration(L, "GL_MAX_VERTEX_ATOMIC_COUNTERS", 0x92D2);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS", 0x92D3);
	lua_pushenumuration(L, "GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS", 0x92D4);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_ATOMIC_COUNTERS", 0x92D5);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_ATOMIC_COUNTERS", 0x92D6);
	lua_pushenumuration(L, "GL_MAX_COMBINED_ATOMIC_COUNTERS", 0x92D7);
	lua_pushenumuration(L, "GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE", 0x92D8);
	lua_pushenumuration(L, "GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS", 0x92DC);
	lua_pushenumuration(L, "GL_ACTIVE_ATOMIC_COUNTER_BUFFERS", 0x92D9);
	lua_pushenumuration(L, "GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX", 0x92DA);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_ATOMIC_COUNTER", 0x92DB);
#endif
#ifdef GL_ARB_shader_image_load_store
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT", 0x00000001);
	lua_pushenumuration(L, "GL_ELEMENT_ARRAY_BARRIER_BIT", 0x00000002);
	lua_pushenumuration(L, "GL_UNIFORM_BARRIER_BIT", 0x00000004);
	lua_pushenumuration(L, "GL_TEXTURE_FETCH_BARRIER_BIT", 0x00000008);
	lua_pushenumuration(L, "GL_SHADER_IMAGE_ACCESS_BARRIER_BIT", 0x00000020);
	lua_pushenumuration(L, "GL_COMMAND_BARRIER_BIT", 0x00000040);
	lua_pushenumuration(L, "GL_PIXEL_BUFFER_BARRIER_BIT", 0x00000080);
	lua_pushenumuration(L, "GL_TEXTURE_UPDATE_BARRIER_BIT", 0x00000100);
	lua_pushenumuration(L, "GL_BUFFER_UPDATE_BARRIER_BIT", 0x00000200);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_BARRIER_BIT", 0x00000400);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_BARRIER_BIT", 0x00000800);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BARRIER_BIT", 0x00001000);
	lua_pushenumuration(L, "GL_ALL_BARRIER_BITS", 0xFFFFFFFF);
	lua_pushenumuration(L, "GL_MAX_IMAGE_UNITS", 0x8F38);
	lua_pushenumuration(L, "GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS", 0x8F39);
	lua_pushenumuration(L, "GL_IMAGE_BINDING_NAME", 0x8F3A);
	lua_pushenumuration(L, "GL_IMAGE_BINDING_LEVEL", 0x8F3B);
	lua_pushenumuration(L, "GL_IMAGE_BINDING_LAYERED", 0x8F3C);
	lua_pushenumuration(L, "GL_IMAGE_BINDING_LAYER", 0x8F3D);
	lua_pushenumuration(L, "GL_IMAGE_BINDING_ACCESS", 0x8F3E);
	lua_pushenumuration(L, "GL_IMAGE_1D", 0x904C);
	lua_pushenumuration(L, "GL_IMAGE_2D", 0x904D);
	lua_pushenumuration(L, "GL_IMAGE_3D", 0x904E);
	lua_pushenumuration(L, "GL_IMAGE_2D_RECT", 0x904F);
	lua_pushenumuration(L, "GL_IMAGE_CUBE", 0x9050);
	lua_pushenumuration(L, "GL_IMAGE_BUFFER", 0x9051);
	lua_pushenumuration(L, "GL_IMAGE_1D_ARRAY", 0x9052);
	lua_pushenumuration(L, "GL_IMAGE_2D_ARRAY", 0x9053);
	lua_pushenumuration(L, "GL_IMAGE_CUBE_MAP_ARRAY", 0x9054);
	lua_pushenumuration(L, "GL_IMAGE_2D_MULTISAMPLE", 0x9055);
	lua_pushenumuration(L, "GL_IMAGE_2D_MULTISAMPLE_ARRAY", 0x9056);
	lua_pushenumuration(L, "GL_INT_IMAGE_1D", 0x9057);
	lua_pushenumuration(L, "GL_INT_IMAGE_2D", 0x9058);
	lua_pushenumuration(L, "GL_INT_IMAGE_3D", 0x9059);
	lua_pushenumuration(L, "GL_INT_IMAGE_2D_RECT", 0x905A);
	lua_pushenumuration(L, "GL_INT_IMAGE_CUBE", 0x905B);
	lua_pushenumuration(L, "GL_INT_IMAGE_BUFFER", 0x905C);
	lua_pushenumuration(L, "GL_INT_IMAGE_1D_ARRAY", 0x905D);
	lua_pushenumuration(L, "GL_INT_IMAGE_2D_ARRAY", 0x905E);
	lua_pushenumuration(L, "GL_INT_IMAGE_CUBE_MAP_ARRAY", 0x905F);
	lua_pushenumuration(L, "GL_INT_IMAGE_2D_MULTISAMPLE", 0x9060);
	lua_pushenumuration(L, "GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY", 0x9061);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_1D", 0x9062);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_2D", 0x9063);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_3D", 0x9064);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_2D_RECT", 0x9065);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_CUBE", 0x9066);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_BUFFER", 0x9067);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_1D_ARRAY", 0x9068);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_2D_ARRAY", 0x9069);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY", 0x906A);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE", 0x906B);
	lua_pushenumuration(L, "GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY", 0x906C);
	lua_pushenumuration(L, "GL_MAX_IMAGE_SAMPLES", 0x906D);
	lua_pushenumuration(L, "GL_IMAGE_BINDING_FORMAT", 0x906E);
	lua_pushenumuration(L, "GL_IMAGE_FORMAT_COMPATIBILITY_TYPE", 0x90C7);
	lua_pushenumuration(L, "GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE", 0x90C8);
	lua_pushenumuration(L, "GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS", 0x90C9);
	lua_pushenumuration(L, "GL_MAX_VERTEX_IMAGE_UNIFORMS", 0x90CA);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS", 0x90CB);
	lua_pushenumuration(L, "GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS", 0x90CC);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_IMAGE_UNIFORMS", 0x90CD);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_IMAGE_UNIFORMS", 0x90CE);
	lua_pushenumuration(L, "GL_MAX_COMBINED_IMAGE_UNIFORMS", 0x90CF);
#endif
#ifdef GL_ARB_shading_language_packing
#endif
#ifdef GL_ARB_texture_storage
	lua_pushenumuration(L, "GL_TEXTURE_IMMUTABLE_FORMAT", 0x912F);
#endif
#ifdef GL_ARB_arrays_of_arrays
#endif
#ifdef GL_ARB_clear_buffer_object
#endif
#ifdef GL_ARB_compute_shader
	lua_pushenumuration(L, "GL_COMPUTE_SHADER", 0x91B9);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_UNIFORM_BLOCKS", 0x91BB);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS", 0x91BC);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_IMAGE_UNIFORMS", 0x91BD);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_SHARED_MEMORY_SIZE", 0x8262);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_UNIFORM_COMPONENTS", 0x8263);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS", 0x8264);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_ATOMIC_COUNTERS", 0x8265);
	lua_pushenumuration(L, "GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS", 0x8266);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_LOCAL_INVOCATIONS", 0x90EB);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_WORK_GROUP_COUNT", 0x91BE);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_WORK_GROUP_SIZE", 0x91BF);
	lua_pushenumuration(L, "GL_COMPUTE_LOCAL_WORK_SIZE", 0x8267);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER", 0x90EC);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER", 0x90ED);
	lua_pushenumuration(L, "GL_DISPATCH_INDIRECT_BUFFER", 0x90EE);
	lua_pushenumuration(L, "GL_DISPATCH_INDIRECT_BUFFER_BINDING", 0x90EF);
	lua_pushenumuration(L, "GL_COMPUTE_SHADER_BIT", 0x00000020);
#endif
#ifdef GL_ARB_copy_image
#endif
#ifdef GL_ARB_texture_view
	lua_pushenumuration(L, "GL_TEXTURE_VIEW_MIN_LEVEL", 0x82DB);
	lua_pushenumuration(L, "GL_TEXTURE_VIEW_NUM_LEVELS", 0x82DC);
	lua_pushenumuration(L, "GL_TEXTURE_VIEW_MIN_LAYER", 0x82DD);
	lua_pushenumuration(L, "GL_TEXTURE_VIEW_NUM_LAYERS", 0x82DE);
	lua_pushenumuration(L, "GL_TEXTURE_IMMUTABLE_LEVELS", 0x82DF);
#endif
#ifdef GL_ARB_vertex_attrib_binding
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_BINDING", 0x82D4);
	lua_pushenumuration(L, "GL_VERTEX_ATTRIB_RELATIVE_OFFSET", 0x82D5);
	lua_pushenumuration(L, "GL_VERTEX_BINDING_DIVISOR", 0x82D6);
	lua_pushenumuration(L, "GL_VERTEX_BINDING_OFFSET", 0x82D7);
	lua_pushenumuration(L, "GL_VERTEX_BINDING_STRIDE", 0x82D8);
	lua_pushenumuration(L, "GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET", 0x82D9);
	lua_pushenumuration(L, "GL_MAX_VERTEX_ATTRIB_BINDINGS", 0x82DA);
#endif
#ifdef GL_ARB_robustness_isolation
#endif
#ifdef GL_ARB_ES3_compatibility
	lua_pushenumuration(L, "GL_COMPRESSED_RGB8_ETC2", 0x9274);
	lua_pushenumuration(L, "GL_COMPRESSED_SRGB8_ETC2", 0x9275);
	lua_pushenumuration(L, "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2", 0x9276);
	lua_pushenumuration(L, "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2", 0x9277);
	lua_pushenumuration(L, "GL_COMPRESSED_RGBA8_ETC2_EAC", 0x9278);
	lua_pushenumuration(L, "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC", 0x9279);
	lua_pushenumuration(L, "GL_COMPRESSED_R11_EAC", 0x9270);
	lua_pushenumuration(L, "GL_COMPRESSED_SIGNED_R11_EAC", 0x9271);
	lua_pushenumuration(L, "GL_COMPRESSED_RG11_EAC", 0x9272);
	lua_pushenumuration(L, "GL_COMPRESSED_SIGNED_RG11_EAC", 0x9273);
	lua_pushenumuration(L, "GL_PRIMITIVE_RESTART_FIXED_INDEX", 0x8D69);
	lua_pushenumuration(L, "GL_ANY_SAMPLES_PASSED_CONSERVATIVE", 0x8D6A);
	lua_pushenumuration(L, "GL_MAX_ELEMENT_INDEX", 0x8D6B);
#endif
#ifdef GL_ARB_explicit_uniform_location
	lua_pushenumuration(L, "GL_MAX_UNIFORM_LOCATIONS", 0x826E);
#endif
#ifdef GL_ARB_fragment_layer_viewport
#endif
#ifdef GL_ARB_framebuffer_no_attachments
	lua_pushenumuration(L, "GL_FRAMEBUFFER_DEFAULT_WIDTH", 0x9310);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_DEFAULT_HEIGHT", 0x9311);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_DEFAULT_LAYERS", 0x9312);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_DEFAULT_SAMPLES", 0x9313);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS", 0x9314);
	lua_pushenumuration(L, "GL_MAX_FRAMEBUFFER_WIDTH", 0x9315);
	lua_pushenumuration(L, "GL_MAX_FRAMEBUFFER_HEIGHT", 0x9316);
	lua_pushenumuration(L, "GL_MAX_FRAMEBUFFER_LAYERS", 0x9317);
	lua_pushenumuration(L, "GL_MAX_FRAMEBUFFER_SAMPLES", 0x9318);
#endif
#ifdef GL_ARB_internalformat_query2
	lua_pushenumuration(L, "GL_INTERNALFORMAT_SUPPORTED", 0x826F);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_PREFERRED", 0x8270);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_RED_SIZE", 0x8271);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_GREEN_SIZE", 0x8272);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_BLUE_SIZE", 0x8273);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_ALPHA_SIZE", 0x8274);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_DEPTH_SIZE", 0x8275);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_STENCIL_SIZE", 0x8276);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_SHARED_SIZE", 0x8277);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_RED_TYPE", 0x8278);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_GREEN_TYPE", 0x8279);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_BLUE_TYPE", 0x827A);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_ALPHA_TYPE", 0x827B);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_DEPTH_TYPE", 0x827C);
	lua_pushenumuration(L, "GL_INTERNALFORMAT_STENCIL_TYPE", 0x827D);
	lua_pushenumuration(L, "GL_MAX_WIDTH", 0x827E);
	lua_pushenumuration(L, "GL_MAX_HEIGHT", 0x827F);
	lua_pushenumuration(L, "GL_MAX_DEPTH", 0x8280);
	lua_pushenumuration(L, "GL_MAX_LAYERS", 0x8281);
	lua_pushenumuration(L, "GL_MAX_COMBINED_DIMENSIONS", 0x8282);
	lua_pushenumuration(L, "GL_COLOR_COMPONENTS", 0x8283);
	lua_pushenumuration(L, "GL_DEPTH_COMPONENTS", 0x8284);
	lua_pushenumuration(L, "GL_STENCIL_COMPONENTS", 0x8285);
	lua_pushenumuration(L, "GL_COLOR_RENDERABLE", 0x8286);
	lua_pushenumuration(L, "GL_DEPTH_RENDERABLE", 0x8287);
	lua_pushenumuration(L, "GL_STENCIL_RENDERABLE", 0x8288);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_RENDERABLE", 0x8289);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_RENDERABLE_LAYERED", 0x828A);
	lua_pushenumuration(L, "GL_FRAMEBUFFER_BLEND", 0x828B);
	lua_pushenumuration(L, "GL_READ_PIXELS", 0x828C);
	lua_pushenumuration(L, "GL_READ_PIXELS_FORMAT", 0x828D);
	lua_pushenumuration(L, "GL_READ_PIXELS_TYPE", 0x828E);
	lua_pushenumuration(L, "GL_TEXTURE_IMAGE_FORMAT", 0x828F);
	lua_pushenumuration(L, "GL_TEXTURE_IMAGE_TYPE", 0x8290);
	lua_pushenumuration(L, "GL_GET_TEXTURE_IMAGE_FORMAT", 0x8291);
	lua_pushenumuration(L, "GL_GET_TEXTURE_IMAGE_TYPE", 0x8292);
	lua_pushenumuration(L, "GL_MIPMAP", 0x8293);
	lua_pushenumuration(L, "GL_MANUAL_GENERATE_MIPMAP", 0x8294);
	lua_pushenumuration(L, "GL_AUTO_GENERATE_MIPMAP", 0x8295);
	lua_pushenumuration(L, "GL_COLOR_ENCODING", 0x8296);
	lua_pushenumuration(L, "GL_SRGB_READ", 0x8297);
	lua_pushenumuration(L, "GL_SRGB_WRITE", 0x8298);
	lua_pushenumuration(L, "GL_SRGB_DECODE_ARB", 0x8299);
	lua_pushenumuration(L, "GL_FILTER", 0x829A);
	lua_pushenumuration(L, "GL_VERTEX_TEXTURE", 0x829B);
	lua_pushenumuration(L, "GL_TESS_CONTROL_TEXTURE", 0x829C);
	lua_pushenumuration(L, "GL_TESS_EVALUATION_TEXTURE", 0x829D);
	lua_pushenumuration(L, "GL_GEOMETRY_TEXTURE", 0x829E);
	lua_pushenumuration(L, "GL_FRAGMENT_TEXTURE", 0x829F);
	lua_pushenumuration(L, "GL_COMPUTE_TEXTURE", 0x82A0);
	lua_pushenumuration(L, "GL_TEXTURE_SHADOW", 0x82A1);
	lua_pushenumuration(L, "GL_TEXTURE_GATHER", 0x82A2);
	lua_pushenumuration(L, "GL_TEXTURE_GATHER_SHADOW", 0x82A3);
	lua_pushenumuration(L, "GL_SHADER_IMAGE_LOAD", 0x82A4);
	lua_pushenumuration(L, "GL_SHADER_IMAGE_STORE", 0x82A5);
	lua_pushenumuration(L, "GL_SHADER_IMAGE_ATOMIC", 0x82A6);
	lua_pushenumuration(L, "GL_IMAGE_TEXEL_SIZE", 0x82A7);
	lua_pushenumuration(L, "GL_IMAGE_COMPATIBILITY_CLASS", 0x82A8);
	lua_pushenumuration(L, "GL_IMAGE_PIXEL_FORMAT", 0x82A9);
	lua_pushenumuration(L, "GL_IMAGE_PIXEL_TYPE", 0x82AA);
	lua_pushenumuration(L, "GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST", 0x82AC);
	lua_pushenumuration(L, "GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST", 0x82AD);
	lua_pushenumuration(L, "GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE", 0x82AE);
	lua_pushenumuration(L, "GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE", 0x82AF);
	lua_pushenumuration(L, "GL_TEXTURE_COMPRESSED_BLOCK_WIDTH", 0x82B1);
	lua_pushenumuration(L, "GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT", 0x82B2);
	lua_pushenumuration(L, "GL_TEXTURE_COMPRESSED_BLOCK_SIZE", 0x82B3);
	lua_pushenumuration(L, "GL_CLEAR_BUFFER", 0x82B4);
	lua_pushenumuration(L, "GL_TEXTURE_VIEW", 0x82B5);
	lua_pushenumuration(L, "GL_VIEW_COMPATIBILITY_CLASS", 0x82B6);
	lua_pushenumuration(L, "GL_FULL_SUPPORT", 0x82B7);
	lua_pushenumuration(L, "GL_CAVEAT_SUPPORT", 0x82B8);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_4_X_32", 0x82B9);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_2_X_32", 0x82BA);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_1_X_32", 0x82BB);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_4_X_16", 0x82BC);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_2_X_16", 0x82BD);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_1_X_16", 0x82BE);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_4_X_8", 0x82BF);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_2_X_8", 0x82C0);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_1_X_8", 0x82C1);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_11_11_10", 0x82C2);
	lua_pushenumuration(L, "GL_IMAGE_CLASS_10_10_10_2", 0x82C3);
	lua_pushenumuration(L, "GL_VIEW_CLASS_128_BITS", 0x82C4);
	lua_pushenumuration(L, "GL_VIEW_CLASS_96_BITS", 0x82C5);
	lua_pushenumuration(L, "GL_VIEW_CLASS_64_BITS", 0x82C6);
	lua_pushenumuration(L, "GL_VIEW_CLASS_48_BITS", 0x82C7);
	lua_pushenumuration(L, "GL_VIEW_CLASS_32_BITS", 0x82C8);
	lua_pushenumuration(L, "GL_VIEW_CLASS_24_BITS", 0x82C9);
	lua_pushenumuration(L, "GL_VIEW_CLASS_16_BITS", 0x82CA);
	lua_pushenumuration(L, "GL_VIEW_CLASS_8_BITS", 0x82CB);
	lua_pushenumuration(L, "GL_VIEW_CLASS_S3TC_DXT1_RGB", 0x82CC);
	lua_pushenumuration(L, "GL_VIEW_CLASS_S3TC_DXT1_RGBA", 0x82CD);
	lua_pushenumuration(L, "GL_VIEW_CLASS_S3TC_DXT3_RGBA", 0x82CE);
	lua_pushenumuration(L, "GL_VIEW_CLASS_S3TC_DXT5_RGBA", 0x82CF);
	lua_pushenumuration(L, "GL_VIEW_CLASS_RGTC1_RED", 0x82D0);
	lua_pushenumuration(L, "GL_VIEW_CLASS_RGTC2_RG", 0x82D1);
	lua_pushenumuration(L, "GL_VIEW_CLASS_BPTC_UNORM", 0x82D2);
	lua_pushenumuration(L, "GL_VIEW_CLASS_BPTC_FLOAT", 0x82D3);
#endif
#ifdef GL_ARB_invalidate_subdata
#endif
#ifdef GL_ARB_multi_draw_indirect
#endif
#ifdef GL_ARB_program_interface_query
	lua_pushenumuration(L, "GL_UNIFORM", 0x92E1);
	lua_pushenumuration(L, "GL_UNIFORM_BLOCK", 0x92E2);
	lua_pushenumuration(L, "GL_PROGRAM_INPUT", 0x92E3);
	lua_pushenumuration(L, "GL_PROGRAM_OUTPUT", 0x92E4);
	lua_pushenumuration(L, "GL_BUFFER_VARIABLE", 0x92E5);
	lua_pushenumuration(L, "GL_SHADER_STORAGE_BLOCK", 0x92E6);
	lua_pushenumuration(L, "GL_VERTEX_SUBROUTINE", 0x92E8);
	lua_pushenumuration(L, "GL_TESS_CONTROL_SUBROUTINE", 0x92E9);
	lua_pushenumuration(L, "GL_TESS_EVALUATION_SUBROUTINE", 0x92EA);
	lua_pushenumuration(L, "GL_GEOMETRY_SUBROUTINE", 0x92EB);
	lua_pushenumuration(L, "GL_FRAGMENT_SUBROUTINE", 0x92EC);
	lua_pushenumuration(L, "GL_COMPUTE_SUBROUTINE", 0x92ED);
	lua_pushenumuration(L, "GL_VERTEX_SUBROUTINE_UNIFORM", 0x92EE);
	lua_pushenumuration(L, "GL_TESS_CONTROL_SUBROUTINE_UNIFORM", 0x92EF);
	lua_pushenumuration(L, "GL_TESS_EVALUATION_SUBROUTINE_UNIFORM", 0x92F0);
	lua_pushenumuration(L, "GL_GEOMETRY_SUBROUTINE_UNIFORM", 0x92F1);
	lua_pushenumuration(L, "GL_FRAGMENT_SUBROUTINE_UNIFORM", 0x92F2);
	lua_pushenumuration(L, "GL_COMPUTE_SUBROUTINE_UNIFORM", 0x92F3);
	lua_pushenumuration(L, "GL_TRANSFORM_FEEDBACK_VARYING", 0x92F4);
	lua_pushenumuration(L, "GL_ACTIVE_RESOURCES", 0x92F5);
	lua_pushenumuration(L, "GL_MAX_NAME_LENGTH", 0x92F6);
	lua_pushenumuration(L, "GL_MAX_NUM_ACTIVE_VARIABLES", 0x92F7);
	lua_pushenumuration(L, "GL_MAX_NUM_COMPATIBLE_SUBROUTINES", 0x92F8);
	lua_pushenumuration(L, "GL_NAME_LENGTH", 0x92F9);
	lua_pushenumuration(L, "GL_TYPE", 0x92FA);
	lua_pushenumuration(L, "GL_ARRAY_SIZE", 0x92FB);
	lua_pushenumuration(L, "GL_OFFSET", 0x92FC);
	lua_pushenumuration(L, "GL_BLOCK_INDEX", 0x92FD);
	lua_pushenumuration(L, "GL_ARRAY_STRIDE", 0x92FE);
	lua_pushenumuration(L, "GL_MATRIX_STRIDE", 0x92FF);
	lua_pushenumuration(L, "GL_IS_ROW_MAJOR", 0x9300);
	lua_pushenumuration(L, "GL_ATOMIC_COUNTER_BUFFER_INDEX", 0x9301);
	lua_pushenumuration(L, "GL_BUFFER_BINDING", 0x9302);
	lua_pushenumuration(L, "GL_BUFFER_DATA_SIZE", 0x9303);
	lua_pushenumuration(L, "GL_NUM_ACTIVE_VARIABLES", 0x9304);
	lua_pushenumuration(L, "GL_ACTIVE_VARIABLES", 0x9305);
	lua_pushenumuration(L, "GL_REFERENCED_BY_VERTEX_SHADER", 0x9306);
	lua_pushenumuration(L, "GL_REFERENCED_BY_TESS_CONTROL_SHADER", 0x9307);
	lua_pushenumuration(L, "GL_REFERENCED_BY_TESS_EVALUATION_SHADER", 0x9308);
	lua_pushenumuration(L, "GL_REFERENCED_BY_GEOMETRY_SHADER", 0x9309);
	lua_pushenumuration(L, "GL_REFERENCED_BY_FRAGMENT_SHADER", 0x930A);
	lua_pushenumuration(L, "GL_REFERENCED_BY_COMPUTE_SHADER", 0x930B);
	lua_pushenumuration(L, "GL_TOP_LEVEL_ARRAY_SIZE", 0x930C);
	lua_pushenumuration(L, "GL_TOP_LEVEL_ARRAY_STRIDE", 0x930D);
	lua_pushenumuration(L, "GL_LOCATION", 0x930E);
	lua_pushenumuration(L, "GL_LOCATION_INDEX", 0x930F);
	lua_pushenumuration(L, "GL_IS_PER_PATCH", 0x92E7);
#endif
#ifdef GL_ARB_robust_buffer_access_behavior
#endif
#ifdef GL_ARB_shader_image_size
#endif
#ifdef GL_ARB_shader_storage_buffer_object
	lua_pushenumuration(L, "GL_SHADER_STORAGE_BUFFER", 0x90D2);
	lua_pushenumuration(L, "GL_SHADER_STORAGE_BUFFER_BINDING", 0x90D3);
	lua_pushenumuration(L, "GL_SHADER_STORAGE_BUFFER_START", 0x90D4);
	lua_pushenumuration(L, "GL_SHADER_STORAGE_BUFFER_SIZE", 0x90D5);
	lua_pushenumuration(L, "GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS", 0x90D6);
	lua_pushenumuration(L, "GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS", 0x90D7);
	lua_pushenumuration(L, "GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS", 0x90D8);
	lua_pushenumuration(L, "GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS", 0x90D9);
	lua_pushenumuration(L, "GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS", 0x90DA);
	lua_pushenumuration(L, "GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS", 0x90DB);
	lua_pushenumuration(L, "GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS", 0x90DC);
	lua_pushenumuration(L, "GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS", 0x90DD);
	lua_pushenumuration(L, "GL_MAX_SHADER_STORAGE_BLOCK_SIZE", 0x90DE);
	lua_pushenumuration(L, "GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT", 0x90DF);
	lua_pushenumuration(L, "GL_SHADER_STORAGE_BARRIER_BIT", 0x2000);
	lua_pushenumuration(L, "GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES", GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS);
#endif
#ifdef GL_ARB_stencil_texturing
	lua_pushenumuration(L, "GL_DEPTH_STENCIL_TEXTURE_MODE", 0x90EA);
#endif
#ifdef GL_ARB_texture_buffer_range
	lua_pushenumuration(L, "GL_TEXTURE_BUFFER_OFFSET", 0x919D);
	lua_pushenumuration(L, "GL_TEXTURE_BUFFER_SIZE", 0x919E);
	lua_pushenumuration(L, "GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT", 0x919F);
#endif
#ifdef GL_ARB_texture_query_levels
#endif
#ifdef GL_ARB_texture_storage_multisample
#endif

	return 1;
}

