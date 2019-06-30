#define STB_IMAGE_IMPLEMENTATION

#include<iostream>
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "skybox.h"
#include "quad.h"
#include "framebuffer.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
// settings
int nScreenWidth = 1200;
int nScreenHeight = 800;

const unsigned int SCR_WIDTH = nScreenWidth;
const unsigned int SCR_HEIGHT = nScreenHeight;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
int rend_type = 0;

int main()
{
	cout << "hello world" << endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//glEnable(GL_DEPTH_TEST);
	Quad quad;
	Shader testShader("..//shader//testShader.vs", "..//shader//testShader.fs","..//shader//testShader.gs");
	Model child("..//object//test//obj.obj");
	Shader childShader("..//shader//childShader.vs", "..//shader//childShader.fs", "..//shader//childShader.gs");
	Shader girlShader("..//shader//girlShader.vs", "..//shader//girlShader.fs", "..//shader//girlShader.gs");
	EXFrameBuffer my_Frame;
	Shader frameShader("..//shader//frameShader.vs", "..//shader//frameShader.fs");
	Tem_Texture girlTex("..//object//test_1//000.jpg");
	Model girl("..//object//test_1//000.obj");
	float v = 0.0;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PROGRAM_POINT_SIZE);
	//glEnable(GL_CULL_FACE);
	while (!glfwWindowShouldClose(window))
	{
	
		glBindFramebuffer(GL_FRAMEBUFFER,my_Frame.framebuffer);
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput(window);
		glm::mat4 model(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		//testShader.use();
		//testShader.setMat4("model", model);
		//testShader.setMat4("view", view);
		//testShader.setMat4("projection", projection);
		//quad.Draw();

		childShader.use();
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
		childShader.setMat4("model", model);
		childShader.setMat4("view", view);
		childShader.setMat4("projection", projection);
		childShader.setFloat("time", 10.0*sin(lastFrame*0.1));
		childShader.setVec3("ViewPos", camera.GetLocation());
		childShader.setVec3("LightPos", camera.GetLocation());
		v= -1.1f+25.0*sin(lastFrame*0.1);
		//v = -10.0;
		childShader.setFloat("h", v);
		child.Draw(childShader);


		//girlShader.use();
		//model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
		//model = glm::translate(model, glm::vec3(0.0, 0.0, -5.0));
		//girlShader.setMat4("model", model);
		//girlShader.setMat4("view", view);
		//girlShader.setMat4("projection", projection);
		//girlShader.setFloat("time", 10.0*sin(lastFrame*0.1));
		//girlShader.setVec3("ViewPos", camera.GetLocation());
		//girlShader.setVec3("LightPos", camera.GetLocation());
		//girlShader.setFloat("h", v*3.0);
		//girlTex.use();
		//girl.Draw(girlShader);



		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		frameShader.use();
		frameShader.setInt("T_pos", 1);
		frameShader.setInt("T_normal", 2);
		frameShader.setInt("T_texcoords", 3);
		frameShader.setInt("T_res", 0);
		frameShader.setInt("num", rend_type);
		frameShader.setVec3("ViewPos", camera.GetLocation());
		frameShader.setVec3("LightPos", camera.GetLocation());
		glDepthMask(GL_FALSE);
		my_Frame.Draw();
		glDepthMask(GL_TRUE);
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow *window)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		rend_type = (rend_type + 1) % 5;
		glEnable(GL_CULL_FACE);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		rend_type = (rend_type - 1);
		if (rend_type == -1)
		{
			rend_type = 4;
			glDisable(GL_CULL_FACE);
		}
	}
}