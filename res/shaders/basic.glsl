#shader vertex
#version 330 core

layout(location=0) in vec4 aPosition;
layout(location=1) in vec4 aColor;

uniform mat4 uCameraMatrix;

out vec4 vColor;

void main()
{
	vColor = aColor;
	gl_Position = uCameraMatrix * aPosition;
}

#shader fragment
#version 330 core

in vec4 vColor;

out vec4 color;

void main()
{
	color = vColor;
}
