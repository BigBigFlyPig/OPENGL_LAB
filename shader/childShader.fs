#version 330 core

layout(location =0) out vec4 T_res;
layout(location =1) out vec4 T_pos;
layout(location =2) out vec4 T_normal;
layout(location =3) out vec4 T_texcoords;


in vec3 Pos;
in vec3 Nor;
in vec2 Tex;

uniform vec3 ViewPos;
uniform vec3 LightPos;

void main()
{
	T_pos = vec4(Pos,1.0f);
	T_normal = vec4(Nor,1.0f);
	T_texcoords = vec4(Tex,0.0,1.0);

	float env = 0.1;
	vec3 dir = normalize(LightPos - Pos);
	vec3 normal = normalize(Nor);
	float power = max(dot(dir,normal),0.0);
	
	float specularStrength = 0.5;
	vec3 viewDir = normalize(ViewPos - Pos);
	vec3 reflectDir = reflect(-dir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32)*specularStrength;
	T_res = vec4(vec3(power+env+spec),1.0);
}