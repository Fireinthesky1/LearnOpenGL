#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BasicShader.h"

#include <iostream>


//declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);



//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{
	//initialize and configure glfw
	glfwInit();												
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	//glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	//build and compile shaders
	Shader ourShader("shaders/shader.vert", "shaders/shader.frag");



	//vertex data
	float vertices1[] =	//first triangle
	{
		//positions			//colors
		-0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f,	//bottom left
		 0.0f,  0.5f, 0.0f,  0.0f,  1.0f,  0.0f,	//top
		 0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  1.0f,	//bottom right
	};
	


	float vertices2[] =	//second triangle
	{
		 0.0f,  0.0f, 0.0f,
		 0.5f,  1.0f, 0.0f,
		 1.0f,  0.0f, 0.0f
	};



	//index data
	unsigned int indices[] =
	{
		0, 1, 2	//used for both triangles
	};



	//creating Vertex Array Object, binding
	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);
	

	
	//create a vertex buffer object
	unsigned int VBO1;
	glGenBuffers(1, &VBO1);
	



	//creating Element Buffer Objects, Binding
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	 
	

	//binding and attaching correct VAO VBO and EBO's for the first triangle
	glBindVertexArray(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	//querying the number of vertex attributes liited by the hardware
	int numAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributes);
	std::cout << "Maximum number of vertex attributes supported: " << numAttributes << std::endl;



	//Linking vertex attributes for the first triangle
	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		ourShader.setFloat("x", sin(glfwGetTime()) / 2);
		ourShader.setFloat("y", cos(glfwGetTime()) / 2);
		glBindVertexArray(VAO1);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	//cleanup
	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO1);
	glfwTerminate();
	return 0;
}



//glfw: If the user presses the escape key the window will close
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}



//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}