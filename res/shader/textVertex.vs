#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 uv;

uniform mat4 _ProjView;
uniform mat4 _Model;

out VsOut
{
	vec3 position;
    vec2 uv;
} vsOut;

void main()
{
	vec4 aPos = vec4(position.x, position.y, position.z, 1);
    gl_Position =_ProjView * _Model * aPos;
	
	vsOut.position = (_Model * aPos).xyz;
	vsOut.uv = uv;
};		