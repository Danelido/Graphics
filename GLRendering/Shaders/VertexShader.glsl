#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoords;

out vec3 FragmentColor;
out vec2 FragmentTexCoords;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

uniform vec3 overrideColor;

void main()
{
	FragmentColor = vec3(0.5, 0.2, 0.7);
	FragmentTexCoords = texCoords;
	gl_Position = modelTransform * vec4(position, 1.0);
}