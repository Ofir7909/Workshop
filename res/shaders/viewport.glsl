#shader vertex
#version 330 core

layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aNormal;

uniform mat4 uCameraMatrix;
uniform vec3 uViewPos;

out vec3 vNormal;
out vec3 vFragPos;


void main()
{
	vNormal = aNormal;
	vFragPos = aPosition;
	gl_Position = uCameraMatrix * vec4(aPosition, 1.0);
}

#shader fragment
#version 330 core

in vec3 vNormal;
in vec3 vFragPos;

uniform mat4 uCameraMatrix;
uniform vec3 uViewPos;

struct Material { 
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material uMaterial;

struct DirLight {
    vec3 direction;
    vec3 color;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4  
uniform DirLight uDirLights[NR_POINT_LIGHTS];

uniform vec3 uAmbientLight;

out vec4 color;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);

	float diffImpact = max(dot(vNormal, lightDir), 0);
	vec3 diffuse = light.color * diffImpact * uMaterial.diffuse;

	vec3 reflectDir = reflect(-lightDir, normal);
	float specImpact = pow(max(dot(reflectDir, -viewDir), 0), uMaterial.shininess * 128);
	vec3 spec = light.specular * specImpact * uMaterial.specular;

	return diffuse + spec;
}

void main()
{
	vec3 lights = vec3(0);

	vec3 ambient = uAmbientLight * uMaterial.diffuse;
	lights += ambient;

	vec3 viewDir = normalize(vFragPos - uViewPos);
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		lights += CalcDirLight(uDirLights[i], vNormal, viewDir);

	color = vec4(lights, 1.0);
}
