#include"opengltask.h"
#include <stdio.h>
#include <stdlib.h>
#include"tool.h"
#include <GL/glew.h>
#include<iostream>
using namespace std;
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
using namespace glm;
#include"vertexdata.h"
#include<common/shader.hpp>
#include<cstdlib>
#include<ctime>
#define Random() rand()/double(RAND_MAX)
#define SPEED 1000
bool OpenglTask :: Run() {
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
	window = glfwCreateWindow(1024, 768, "Playground", NULL, NULL);
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
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	//// Accept fragment if it closer to the camera than the former one
	//glDepthFunc(GL_LESS);
	//VAO����׼��
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("Custom.vertexshader", "Custom.fragmentshader");
	
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint IID = glGetUniformLocation(programID, "i");
	//ͶӰ����
	mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	cout << "ͶӰ����" << endl;
	PrintMat4(Projection);
	//��ͼ����
	mat4 View = lookAt(
		vec3(4, 3, 3),   //Camera����������
		vec3(0,0, 0),   //Camera�����ĸ���
		vec3(0, 1, 0)    //(0,1,0)�����Ͽ���(0,-1,0)�����¿�
	);
	cout << "��ͼ����" << endl;
	PrintMat4(View);
	//ģ�;���
	mat4 Model = mat4(1.0f);
	cout << "ģ�;���" << endl;
	PrintMat4(Model);
	//MVP����
	mat4 MVP = Projection * View * Model;
	cout << "MVP����"<<endl;
	PrintMat4(MVP);

	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	
	GLuint texture = loadBMP_custom("uvtemplate.bmp");
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	GLuint textureID = glGetUniformLocation(programID, "myTextureSampler");

	do {
		// Draw nothing, see you in tutorial 2 !
		//ʹ��shader
		glUseProgram(programID);
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniform1f(IID, 0.50f);
		//bind the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		glUniform1i(textureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		//��vertexbuffer�󶨵�������buffer object
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//��֪OpenGL����ô�����������������
		glVertexAttribPointer(
			0,            // attribute. No particular reason for 0, but must match the layout in the shader.
			3,            // size
			GL_FLOAT,     // type
			GL_FALSE,     // normalized?
			0,            // stride�����ݼ��϶
			(void*)0      // array buffer offset��buffer object�е�����ƫ������0��ʾ�ӿ�ʼ����
		);
		//����ǽӴ���ǰ���ݶ������buffer object�İ�
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,            //attribute.No particular reason for 0, but must match the layout in the shader.
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12*3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
	//�����ڴ�����
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return false;
}