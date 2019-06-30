#version 330 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 Pos;
uniform float Cloud;
uniform vec3 LightPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_height1;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightvector = normalize(LightPos - Pos);
	float fracolor = max(dot(lightvector,norm),0.0);
    	vec4 temcolor = mix(texture(texture_diffuse1, TexCoords),texture(texture_specular1, TexCoords),Cloud);
	float R = temcolor.x;
	temcolor = vec4(R,R,R,1.0);
	vec4 t_c = texture(texture_height1, TexCoords);
	FragColor = (t_c+temcolor)*fracolor+t_c*0.01;

	float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
	if(1.0<brightness)
		BrightColor = vec4(FragColor.rgb,1.0f);
	else
		BrightColor = vec4(vec3(0.0f),1.0f);
	  

}