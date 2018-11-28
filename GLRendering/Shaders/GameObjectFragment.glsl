#version 430 core
struct s_light
{
	vec3 lightPosition;
	vec3 lightColor;
};

#define MAX_LIGHTS 12
in vec2 f_textureCoordinates;
in vec3 f_normal;
in vec3 f_cameraPosition;
in vec3 f_skyColor;
in vec3 f_objPosition;
flat in int f_numberOfLights;
in s_light f_lights[MAX_LIGHTS];

out vec4 color;

uniform sampler2D textureSampler;
uniform float u_fogStart;
uniform float u_fogEnd;

void main()
{
	vec4 textureColor = texture(textureSampler, f_textureCoordinates);

	/* AMBIENT */
	float ambientStrength = 0.2f;
	vec3 ambient = vec3(1.f,1.f,1.f) * ambientStrength;
	vec4 finalColor = vec4(ambient, 1.0f);

	for(int i = 0; i < f_numberOfLights; i++)
	{
		/* DIFFUSE */
		vec3 toLight = f_lights[i].lightPosition - f_objPosition;
		float factor = dot(normalize(toLight), normalize(f_normal));
		factor = max(factor, 0.0f);
		factor = min(factor, 0.75f);	
		vec3 diffuse = f_lights[i].lightColor * factor;


		/* SPECULAR */
		float specularStrength = 0.5f;
		vec3 toCamera = f_cameraPosition - f_objPosition;
		vec3 reflectDir = reflect(-normalize(toLight), normalize(f_normal));
		float spec = dot(normalize(toCamera), normalize(reflectDir));
		spec = max(spec, 0.0f);
		spec = pow(spec,32);
		
		vec3 specular = specularStrength * spec * f_lights[i].lightColor;

		/* FINAL COLOR */
		finalColor += vec4((diffuse + specular), 0.f);
	}
	// Clamp it
	finalColor = min(finalColor, vec4(1.f, 1.f, 1.f,1.f)) * textureColor;
	
	// Calculate fog
	float dist = length((f_cameraPosition - f_objPosition));
	float fogFactor = 1.f - clamp((u_fogEnd - dist) / (u_fogEnd - u_fogStart), 0.f, 1.f);
	finalColor.xyz = mix(finalColor.xyz, f_skyColor, fogFactor);

	// Output final color
	color = finalColor;
	
}
