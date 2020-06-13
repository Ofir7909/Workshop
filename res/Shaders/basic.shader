#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 VertexColor;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    VertexColor = aColor;
}

#shader fragment
#version 330 core

in vec3 VertexColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(VertexColor, 1.0f);
}