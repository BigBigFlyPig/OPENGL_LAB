#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_sampler;

void main()
{
	FragColor = vec4(0.0,1.0,0.0,1.0f);
	//FragColor = texture(texture_sampler,TexCoords);
}