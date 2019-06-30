#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform float exposure;
uniform sampler2D colorbuffer_1;
uniform sampler2D colorbuffer_2;
uniform bool change;
uniform vec3 camerapos;
uniform mat4 viewmat;
uniform int NUM;

vec2 getLightPos()
{
	vec4 pos = vec4(camerapos,1.0f);
	pos = viewmat*pos;
	vec3 res = pos.xyz/pos.w;
	return res.xy;
}


void main()
{
	vec2 d_size = 1.0/textureSize(colorbuffer_1,0);
	const float gamma = 2.2;
	vec3 c = texture(colorbuffer_1,TexCoords).rgb;
	vec3 c_1 = texture(colorbuffer_2,TexCoords).rgb;
	vec3 mapped = vec3(1.0f) - exp(-c*exposure);
	mapped = pow(mapped,vec3(1.0/gamma));
	if(!change)
	{
			float dis = (TexCoords.x-0.5)*(TexCoords.x-0.5)+(TexCoords.y-0.5)*(TexCoords.y-0.5);
		if(dis<(d_size.x*2.0))
			{
				float k = (TexCoords.x-0.5)/(TexCoords.y-0.5);
				if((k==1.0)||(k==-1.0))
				{
					FragColor = vec4(1.0f);
				}
				else
					FragColor = vec4(mapped,1.0f)*vec4((vec3(1.0,0.0,0.0)*1.0/exp(dis)),1.0);
			}
		else
			FragColor = vec4(mapped,1.0f);
	}
		
	else
	{
		vec2 lightpos = getLightPos();
		vec2 dir = lightpos - TexCoords;
		dir = dir/10;
		vec3 res = vec3(0.0);
		float rt = 1.0;
		float dd = 0.1;
		for(int i=0;i<20;i++)
		{
			res+=rt*texture(colorbuffer_1,TexCoords+dir*i).rgb;
			rt = rt *dd;
		}
		res = vec3(1.0f) - exp(-res*exposure);
		FragColor = vec4(res,1.0f);
	}
	

}