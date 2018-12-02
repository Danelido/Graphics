#version 430 core

in vec3 f_textureCoordinates;
out vec4 pixelColor;

uniform samplerCube skyBox;
uniform vec3 fogColor;

const float lowerLimit = 0.0f;
const float upperLimit = 0.35f;


void main()
{
	vec4 finalColor = texture(skyBox, f_textureCoordinates);

	float factor = (f_textureCoordinates.y - lowerLimit) / (upperLimit - lowerLimit);
	factor = clamp(factor, 0.0f, 1.0f);
	pixelColor = mix(vec4(fogColor, 1.0), finalColor, factor);

}