#version 430 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoordinates;
layout(location = 2) in vec3 normals;

#define MAX_LIGHTS 12
struct s_light
{
	vec3 lightPosition;
	vec3 lightColor;
};

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 cameraPosition;
uniform vec3 skyColor;
uniform int numberOfLights;
uniform s_light lights[MAX_LIGHTS];


out vec2 f_textureCoordinates;
out vec3 f_normal;
out vec3 f_cameraPosition;
out vec3 f_skyColor;
out vec3 f_objPosition;
flat out int f_numberOfLights;
out s_light f_lights[MAX_LIGHTS];

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position,1.0);
	f_objPosition = vec3(modelMatrix * vec4(position, 1.0));
	f_textureCoordinates = textureCoordinates;
	f_normal = mat3(transpose(inverse(modelMatrix))) * normals;
	f_cameraPosition = cameraPosition;
	f_skyColor = skyColor;
	f_numberOfLights = numberOfLights;

	for(int i = 0; i < MAX_LIGHTS; i++)
	{
		f_lights[i] = lights[i];
	}

}