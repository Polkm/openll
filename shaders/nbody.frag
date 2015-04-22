#version 150

in vec4 pass_position;

out vec4 out_color;

const vec4 starColor = vec4(1.0, 1.0, 1.0, 1.0);

void main() {
	out_color = starColor / (pass_position.w * 4);
}