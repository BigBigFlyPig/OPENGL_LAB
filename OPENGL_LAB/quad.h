#pragma once
#ifndef __QUAD__
#define __QUAD__


#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Quad {
public:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	float vertices[24] = {
	-0.5,0.0,0.5,0.0,1.0,0.0,
	0.5,0.0,0.5,0.0,1.0,0.0,
	-0.5,0.0,-0.5,0.0,1.0,0.0,
	0.5,0.0,-0.5,0.0,1.0,0.0
	};
	unsigned int ind[6] = {
	0,1,2,1,2,3
	};
	Quad(){
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), &ind[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glBindVertexArray(0);
	}
	void Draw()
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};



#endif // !__QUAD__
