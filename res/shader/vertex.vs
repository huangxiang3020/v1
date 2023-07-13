#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

uniform mat4 _ProjView;
uniform mat4 _Model;

out vec2 vsOutUV;

void main()
{
	gl_Position = _ProjView * _Model * vec4(pos.x, pos.y, pos.z, 1.0);
	vsOutUV = uv;
};		