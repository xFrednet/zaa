#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normals;

out vec2 fragTextureCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
//uniform vec3 lightPosition;

void main(void) {

	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * worldPosition;
	fragTextureCoords = textureCoords;
}