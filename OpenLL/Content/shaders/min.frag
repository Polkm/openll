#version 150 core

// Inputnick
in vec3 pass_normal;
in vec4 pass_color;

// Output
out vec4 out_color;

// Constants
const vec3 uniformAmbient = vec3(0.4, 0.4, 0.5);
const vec3 materialAmbient = vec3(0.0, 0.0, 0.0);

const float specSharpness = 2;
const float specPower = 0.0;

const vec3 lightLocation = vec3(150.0, 100.0, 120.0);
const vec3 lightVecNormalized = normalize(lightLocation);
const vec3 lightColor = vec3(1.0, 0.89, 0.69);

// //vec3 SpecularLighting() {
// 	//vec3 reflect = reflect(-normalize(lightLocation - cammeraPos), normalize(pass_normal * pass_normalMatrix));
// 	//return materialSpecular * lightColor * pow(max(dot(reflect, normalize(-cammeraPos)), 0.0), specSharpness) * specPower;
// //}

//vec4 ApplyTexture(vec4 color) {
	//if (textureEnabled == 1) {
		//vec4 texture = (texture2D(texture0, pass_TextureCords.xy));
		//return color * texture;
	//}
	//return color;
//}

// vec4 ApplyGammaCorrection(vec4 color) {
// 	return pow(color, vec4(1.0 / 2.0));
// }

vec3 ambient(vec3 color) {
	return (materialAmbient * color) + (uniformAmbient * color);
}

vec3 diffuse(vec3 color) {
	float dotNorm = max(dot(pass_normal, lightVecNormalized), 0.0);
	return lightColor * color * dotNorm;
}

vec4 lighting(vec4 color) {
	// color.xyz = diffuse(color.xyz);
	//vec3 intensitySpecular = SpecularLighting();

	//return vec4((intensityAmbient + intensityDiffuse + intensitySpecular).xyz, color.w);
	return vec4(ambient(color.xyz) + diffuse(color.xyz), color.w);
}

void main(void) {
	vec4 fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);

	//fragmentColor = ApplyTexture(fragmentColor);
	fragmentColor = lighting(fragmentColor);
	//fragmentColor = ApplyGammaCorrection(fragmentColor);

	out_color = fragmentColor;
}