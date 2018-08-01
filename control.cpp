#include"control.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

extern GLFWwindow* window;

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getProjectionMatrix()
{
	return ProjectionMatrix;
}
glm::mat4 getViewMatrix()
{
	return ViewMatrix;
}

glm::vec3 position = glm::vec3(0, 0, 5);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initFov = 45.0f;

float speed = 3.0f;
float mouseSpeed = 0.005f;
void computeMatricesFromInputs() {
	int xPos, yPos;
	//glfwGetMousePos(&xPos, &yPos);
}