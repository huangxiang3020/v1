#version 330 core

uniform sampler2D _MainTex;
uniform vec3 _LightDirection;
uniform vec4 _LightColor;
uniform vec4 _AmbientColor;

in VsOut
{
	vec3 position;
	vec3 normal;
    vec2 uv;
} vsIn;

out vec4 FragColor;

void main()
{	
	vec3 lightDir = normalize(-_LightDirection);
	vec3 normal = normalize(vsIn.normal);
	float diffuse = max(dot(normal, lightDir), 0.0);
	
	vec4 diffuseColor = texture(_MainTex, vsIn.uv);
	
    FragColor = _LightColor * (diffuseColor * _AmbientColor + diffuseColor * diffuse);
}
