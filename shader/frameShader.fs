#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D T_res;
uniform sampler2D T_pos;
uniform sampler2D T_normal;
uniform sampler2D T_texcoords;

uniform vec3 ViewPos;
uniform vec3 LightPos;
uniform int num;

void main()
{
		//FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
	if(num == 0)
		FragColor = texture(T_res,TexCoords);
	else if(num == 1)
		FragColor = texture(T_pos,TexCoords);
	else if(num == 2)
		FragColor = texture(T_normal,TexCoords);
	else if(num == 3)
		FragColor = texture(T_texcoords,TexCoords);
	else{
		vec3 pos = texture(T_pos,TexCoords).rgb;
		vec3 normal = normalize(texture(T_normal,TexCoords).rgb);
		vec3 dir = normalize(LightPos - pos);
		float power = max(dot(dir,normal),0.0);
		float env = 0.1f;
		float specularStrength = 0.5;
		vec3 viewDir = normalize(ViewPos - pos);
		vec3 reflectDir = reflect(-dir, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32)*specularStrength;
		FragColor = vec4(vec3(power+env+spec),0.1f);
	}
}
