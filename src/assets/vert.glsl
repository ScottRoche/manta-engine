#version 460 core

layout (location = 0) in vec3 InPosition;
layout (location = 1) in vec4 InColour;

out vec4 VertColour;

void main()
{
	gl_Position = vec4(InPosition, 1.0);
	VertColour = InColour;

}