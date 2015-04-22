#version 150 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float time;

in vec3 in_position;

out vec4 pass_position;

void main() {
	vec3 curPos = in_position;
	gl_Position = proj * view * model * vec4(curPos, 1.0);
	pass_position = gl_Position;
}