#version 150 core

// Uniforms
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform mat3 u_normal;

uniform vec4 u_color = vec4(1.0, 1.0, 1.0, 1.0);

// Inputnick
in vec3 in_position;
in vec3 in_normal;
// in vec4 in_color;

// Output
out vec3 pass_normal;
out vec4 pass_color;

void main(void) {
	gl_Position = u_projection * u_view * u_model * vec4(in_position, 1.0);
	pass_normal = normalize(u_model * vec4(in_normal, 0.0)).xyz;
	pass_color = u_color;
}