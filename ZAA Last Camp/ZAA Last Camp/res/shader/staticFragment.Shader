#version 330 core

in vec2 fragTextureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;

uniform sampler2D texSampler;
uniform vec3 lightColor;

void main() {

	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDotl = dot(unitNormal, unitLightVector);
	float brightness = max(nDotl, 0.0) + 0.5;
	vec3 diffuse = brightness * lightColor;

	gl_FragColor = vec4(diffuse, 1.0) * texture(texSampler, fragTextureCoords);
}