#version 330 core

in vec3 FragmentColor;
in vec2 FragmentTexCoords;

out vec4 color;

uniform sampler2D grassTexture;
uniform sampler2D bearTexture;

void main()
{
	vec4 grassTex = texture(grassTexture, FragmentTexCoords);
	vec4 bearTex = texture(bearTexture, FragmentTexCoords);

	color = vec4(1.0f, 0.5f, 1.0f, 1.0) * mix(grassTex,bearTex, 0.5);
}