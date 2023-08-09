#version 330 core

uniform sampler2D _MainTex;
uniform vec4 _Color;

in VsOut
{
	vec3 position;
    vec2 uv;
} vsIn;

out vec4 FragColor;

void main()
{	
	vec4 textColor = texture(_MainTex, vsIn.uv);
    FragColor = vec4(textColor.r, textColor.r, textColor.r, textColor.r) * _Color;
}
