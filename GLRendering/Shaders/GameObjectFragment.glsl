#version 430 core

in vec2 f_textureCoordinates;

out vec4 color;

uniform sampler2D textureSampler;


void main()
{
	vec4 textureColor = texture(textureSampler, f_textureCoordinates);
	color = vec4(1.0f, 1.0f, 1.0f, 1.0f) * textureColor;
}