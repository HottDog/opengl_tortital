#include "opengltask1.h"
#include<iostream>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"vertexdata.h"
#include <glm/glm.hpp>

bool OpenglTask1::Run() {
	GLFWwindow* window;
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Playground1", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return false;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	//准备数据
	//VAO
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	do {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw nothing, see you in tutorial 2 !
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		//把vertexbuffer绑定到创建的buffer object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer);
		//告知OpenGL该怎么解析传输过来的数据
		glVertexAttribPointer(
			0,            // attribute. No particular reason for 0, but must match the layout in the shader.
			3,            // size
			GL_FLOAT,     // type
			GL_FALSE,     // normalized?
			0,            // stride，数据间间隙
			(void*)0      // array buffer offset，buffer object中的数据偏移量，0表示从开始算起
		);
		//绘制
		glDrawElements(GL_TRIANGLES,2 * 3,GL_UNSIGNED_INT,(void*)0);
		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	//销毁内存数据
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return true;
}