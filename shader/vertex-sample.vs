#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 Pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	Normal = mat3(transpose(inverse(model)))*aNormal;
    TexCoords = aTexCoords;
	vec4 temPos = model*vec4(aPos,1.0f);
	Pos = temPos.xyz;
    gl_Position = projection * view * model * vec4(aPos, 1.0f); 
}