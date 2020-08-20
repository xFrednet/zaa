#version 330 core

in vec2 fragTextureCoords;

uniform sampler2D texSampler;
//uniform vec3 lightColor;

void main() {

	gl_FragColor = texture(texSampler, fragTextureCoords);
}