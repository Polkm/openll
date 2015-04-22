#version 150

const vec3 ambient = normalize(vec3(0.14, 0.16, 0.19)) * 0.4;

const vec3 light_pos = vec3(50.0, 70.0, 100.0);
const vec3 light_norm = normalize(light_pos);
const vec3 light_amb = vec3(0.0, 0.0, 0.0);
const vec3 light_color = vec3(1.0, 0.89, 0.69);

const vec3 mat_amb = vec3(0.0, 0.0, 0.0);
const vec3 mat_color = vec3(1.0, 1.0, 1.0);
const vec3 mat_spec = vec3(1, 1, 1) * 0.6;

const float specSharpness = 2;
const float specPower = 0.0;


in vec3 pass_normal;


out vec4 out_color;


vec3 AmbientLighting(vec3 color) {
	return (mat_amb * color) + (light_amb * color) + (ambient * color);
}

vec3 DiffuseLighting(vec3 color) {
	return light_color * color * max(dot(pass_normal, light_norm), 0.0);
}

//vec3 SpecularLighting() {
	//vec3 reflect = reflect(-normalize(light_pos - cammeraPos), normalize(pass_normal * pass_normalMatrix));
	//return mat_spec * light_color * pow(max(dot(reflect, normalize(-cammeraPos)), 0.0), specSharpness) * specPower;
//}

vec4 ApplyLighting(vec4 color) {
	vec3 intensityAmbient = AmbientLighting(color.xyz);
	vec3 intensityDiffuse = DiffuseLighting(color.xyz);
	//vec3 intensitySpecular = SpecularLighting();

	//return vec4((intensityAmbient + intensityDiffuse + intensitySpecular).xyz, color.w);
	return vec4((intensityAmbient + intensityDiffuse).xyz, color.w);
}

void main() {
	vec4 fragmentColor = vec4(mat_color, 1.0);

	//fragmentColor = ApplyLighting(fragmentColor);

	out_color = fragmentColor;
}