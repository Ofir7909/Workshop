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

uniform vec3 uSolidColor;
uniform float uShininess;

struct DirLight {
    vec3 direction;
    vec3 color;
    vec3 specular;
};  
uniform DirLight uDirLight;

uniform float uAmbientStrength;

out vec4 color;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(light.direction);

	vec3 ambient = uDirLight.color * uAmbientStrength;

	float diffImpact = max(dot(-vNormal, lightDir), 0);
	vec3 diffuse = uDirLight.color * diffImpact;

	vec3 reflectDir = reflect(lightDir, normal);
	float spec = pow(max(dot(reflectDir, -viewDir), 0), uShininess);

	return ambient + diffuse + spec;
}

void main()
{
	vec3 viewDir = normalize(vFragPos - uViewPos);
	color = vec4(CalcDirLight(uDirLight, vNormal, viewDir) * uSolidColor, 1.0);
}
