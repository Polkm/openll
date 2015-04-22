#version 150 core

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
//uniform mat3 normalMatrix;

in vec3 in_position;
in vec3 in_normal;

//out vec3 pass_color;
//out vec3 pass_normal;
//out mat3 pass_normalMatrix;

vec3 byteCorrection(vec3 color) {
    return color / 255;
}
void main(void) {
	gl_Position = proj * view * model * vec4(in_position, 1.0);
	//pass_normal = (vec4(in_normal, 1.0) * model).xyz;
	//pass_normalMatrix = normalMatrix;
}