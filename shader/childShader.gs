#version 330 core
layout(triangles) in;
//layout(triangle_strip,max_vertices = 3) out;
layout(points,max_vertices = 1) out;
in vec3 pos[];
in vec3 normal[];
in vec2 texcoords[];
uniform float h;
uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Pos;
out vec3 Nor;
out vec2 Tex;

void main()
{
	mat4 M=projection*view*model; 
	float t_h =0.0;
	vec3 m_nor =vec3(0.0);
	vec3 m_pos = vec3(0.0);
	for(int i=0;i<3;i++)
	{
		m_nor=m_nor+normal[i];
		m_pos = m_pos+gl_in[i].gl_Position.xyz;
	}
	m_nor = m_nor*0.33;
	m_nor = mat3(transpose(inverse(model)))*m_nor;
	m_pos = m_pos*0.33;
	t_h = m_pos.y;
	if(t_h<h)
	{
		vec3 down = -vec3(0.0,0.5*0.50*time*time,0.0);
		gl_Position = M*vec4(gl_in[0].gl_Position.xyz+down+m_nor*time,1.0f);
		gl_PointSize = 1.0;
		Pos = (model*gl_in[0].gl_Position).xyz;
		Nor = m_nor;
		Tex = texcoords[0];
		//EmitVertex();
		//EmitVertex();
		EmitVertex();
		EndPrimitive();	
		gl_Position = M*vec4(gl_in[1].gl_Position.xyz+down+m_nor*time,1.0f);
		Pos = (model*gl_in[1].gl_Position).xyz;
		Nor = m_nor;
		Tex = texcoords[1];
		//EmitVertex();
		//EmitVertex();
		EmitVertex();
		EndPrimitive();	
		gl_Position = M*vec4(gl_in[2].gl_Position.xyz+down+m_nor*time,1.0f);
		Pos = (model*gl_in[2].gl_Position).xyz;
		Nor = m_nor;
		Tex = texcoords[2];
		//EmitVertex();
		//EmitVertex();
		EmitVertex();
		EndPrimitive();	
	}
	else{
		gl_Position = M*gl_in[0].gl_Position;
		Pos = (model*vec4(pos[0],1.0)).xyz;
		Nor = mat3(transpose(inverse(model)))*normal[0];
		Tex = texcoords[0];
		EmitVertex();
		gl_Position = M*gl_in[1].gl_Position;
		Pos = (model*vec4(pos[1],1.0)).xyz;
		Nor = mat3(transpose(inverse(model)))*normal[1];
		Tex = texcoords[1];
		EmitVertex();
		gl_Position = M*gl_in[2].gl_Position;
		Pos = (model*vec4(pos[2],1.0)).xyz;
		Nor = mat3(transpose(inverse(model)))*normal[2];
		Tex = texcoords[2];
		EmitVertex();
		EndPrimitive();
	}
	
}