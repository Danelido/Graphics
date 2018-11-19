#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordinates;
layout(location = 2) in vec3 normals;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 f_textureCoordinates;

void main()
{
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position,1.0);
	f_textureCoordinates = textureCoordinates;
}