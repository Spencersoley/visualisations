#version 330 core
layout (location = 0) out vec4 FragColour;
layout (location = 1) out vec4 BrightColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	// LIGHTING: Specular, Diffuse, Ambient lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specular = specularStrength * spec * lightColour;
	
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = diff * lightColour;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;
	
	vec3 result = (ambient + diffuse + specular) * objectColour;
    FragColour = vec4(result, 1.0);
	
    // check whether result is higher than some threshold, if so, output as bloom threshold color
    float brightness = dot(result, vec3(0.3126, 0.3152, 0.3722));
    if(brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}
