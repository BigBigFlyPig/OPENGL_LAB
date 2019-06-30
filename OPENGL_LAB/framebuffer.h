#pragma once
#ifndef __FRAMEBUFFER__
#define __FRAMBUFFER__

#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include <iostream>


class FrameBuffer {
public:
	int nScreenWidth = 1200;
	int nScreenHeight = 800;
	const unsigned int SCR_WIDTH = nScreenWidth;
	const unsigned int SCR_HEIGHT = nScreenHeight;
	float points[30] = {
	-1.0f,  1.0f, 0.0,  0.0f, 1.0f,
	-1.0f, -1.0f, 0.0,  0.0f, 0.0f,
	 1.0f, -1.0f, 0.0,  1.0f, 0.0f,

	-1.0f,  1.0f, 0.0, 0.0f, 1.0f,
	 1.0f, -1.0f, 0.0, 1.0f, 0.0f,
	 1.0f,  1.0f, 0.0, 1.0f, 1.0f
	};
	unsigned int quadVAO, quadVBO;
	unsigned int framebuffer;
	GLuint textureColorbuffer[2];
	unsigned int rbo;
	GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	FrameBuffer()
	{
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glGenTextures(2, textureColorbuffer);
		for (int i = 0; i < 2; i++)
		{

			glBindTexture(GL_TEXTURE_2D, textureColorbuffer[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureColorbuffer[i], 0);
		}

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
			getchar();
		}
		glDrawBuffers(2, attachments);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(0);

	}
	void Draw()
	{
		glBindVertexArray(quadVAO);
		for (int i = 0; i < 2; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureColorbuffer[i]);
		}
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};


class EXFrameBuffer {
public:

	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	float points[30] = {
	-1.0f,  1.0f, 0.0,  0.0f, 1.0f,
	-1.0f, -1.0f, 0.0,  0.0f, 0.0f,
	 1.0f, -1.0f, 0.0,  1.0f, 0.0f,

	-1.0f,  1.0f, 0.0, 0.0f, 1.0f,
	 1.0f, -1.0f, 0.0, 1.0f, 0.0f,
	 1.0f,  1.0f, 0.0, 1.0f, 1.0f
	};
	unsigned int quadVAO, quadVBO;
	unsigned int framebuffer;

	GLuint textureColorbuffer[5];
	unsigned int rbo;
	GLuint attachments[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3,GL_COLOR_ATTACHMENT4};
	EXFrameBuffer(unsigned int SCR_W = 1200,unsigned int SCR_H = 800)
	{
		this->SCR_HEIGHT = 800;
		this->SCR_WIDTH = 1200;
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glGenTextures(4, textureColorbuffer);
		for (int i = 0; i < 5; i++)
		{
			glBindTexture(GL_TEXTURE_2D, textureColorbuffer[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureColorbuffer[i], 0);
		}
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
			getchar();
		}
		glDrawBuffers(5, attachments);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(0);
	}
	void UseFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
	}
	void Draw()
	{
		glBindVertexArray(quadVAO);
		for (int i = 0; i < 5; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureColorbuffer[i]);
		}
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}//0 pos 1 normal 3 
};


#endif // !__FRAMEBUFFER__
