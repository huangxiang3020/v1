#version 330 core
out vec4 FragColor;
in vec2 uv;
uniform vec4 _Color;
uniform sampler2D _MainTex;
void main()
{
	FragColor = texture(_MainTex, uv);
};