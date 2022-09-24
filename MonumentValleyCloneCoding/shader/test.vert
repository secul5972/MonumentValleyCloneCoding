#version 330 core

layout (location = 0) in vec2 aPos;
//layout (location = 1) in vec3 aNormal;

uniform vec3 aa;

void main()
{
	gl_Position = vec4(aa, 1.0);
}