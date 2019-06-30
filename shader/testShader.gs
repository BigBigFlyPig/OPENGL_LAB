#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 Normal[];
in vec2 TexCoords[];
in mat4 trans[];

void build_house(vec4 position,vec3 normal)
{
		gl_Position = trans[0]*(position + vec4(-0.5,0.0,0.0,0.0));
		EmitVertex();   
		gl_Position = trans[0]*(position + vec4(0.0,0.5,0.0,0.0));
		EmitVertex();   
		gl_Position = trans[0]*(position + vec4(0.0,-0.5,0.0,0.0));
		EmitVertex();   
		EndPrimitive();
}


void main() {    
    build_house(gl_in[0].gl_Position,Normal[0]);
}