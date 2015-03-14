#version 150 core

const vec3 materialAmbient = vec3(0.0, 0.0, 0.0);
const vec3 materialSpecular = vec3(1, 1, 1) * 0.6;
const float specSharpness = 2;
const float specPower = 0.0;

const vec3 lightLocation = vec3(150.0, 100.0, 120.0);
const vec3 lightVecNormalized = -normalize(lightLocation);
const vec3 lightColor = vec3(1.0, 0.89, 0.69);
const vec3 lightAmbient = vec3(0.0, 0.0, 0.0);

const vec3 ambient = normalize(vec3(0.14, 0.16, 0.19)) * 0.4;

uniform vec3 cammeraPos;

//in vec3 pass_normal;

out vec4 out_color;

vec3 AmbientLighting(vec3 color) {
	return (materialAmbient * color) + (lightAmbient * color) + (ambient * color);
}

vec3 DiffuseLighting(vec3 color) {
	//float dotNorm = max(dot(pass_normal, lightVecNormalized), 0.0);
	//return lightColor * color * dotNorm;
	return lightColor * color;
}

//vec3 SpecularLighting() {
	//vec3 reflect = reflect(-normalize(lightLocation - cammeraPos), normalize(pass_normal * pass_normalMatrix));
	//return materialSpecular * lightColor * pow(max(dot(reflect, normalize(-cammeraPos)), 0.0), specSharpness) * specPower;
//}

vec4 ApplyLighting(vec4 input) {
	vec3 intensityAmbient = AmbientLighting(input.xyz);
	vec3 intensityDiffuse = DiffuseLighting(input.xyz);
	//vec3 intensitySpecular = SpecularLighting();

	//return vec4((intensityAmbient + intensityDiffuse + intensitySpecular).xyz, input.w);
	return vec4((intensityAmbient + intensityDiffuse).xyz, input.w);
}

//vec4 ApplyTexture(vec4 input) {
	//if (textureEnabled == 1) {
		//vec4 texture = (texture2D(texture0, pass_TextureCords.xy));
		//return input * texture;
	//}
	//return input;
//}

vec4 ApplyGammaCorrection(vec4 input) {
	return pow(input, vec4(1.0 / 2.0));
}

void main(void) {
	vec4 fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);

	//fragmentColor = ApplyTexture(fragmentColor);
	//fragmentColor = ApplyLighting(fragmentColor);
	//fragmentColor = ApplyGammaCorrection(fragmentColor);

	//out_color = fragmentColor;

	out_color = vec4(1.0, 1.0, 1.0, 1.0);
}