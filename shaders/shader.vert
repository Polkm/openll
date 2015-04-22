#version 150 core

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

in vec3 in_position;
in vec3 in_normal;

out vec3 pass_normal;

void main(void) {
	gl_Position = proj * view * model * vec4(in_position, 1.0);
	
	pass_normal = (vec4(in_normal, 1.0) * model).xyz;
}