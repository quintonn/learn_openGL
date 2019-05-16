#include "drawable.h"

drawable::drawable(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath) : ourShader(vertexShaderPath, fragmentShaderPath, geometryShaderPath)
{
	VAO = new GLuint;
	VBO = new GLuint;
	EBO = new GLuint;

	drawType = GL_DYNAMIC_DRAW;
	std::cout << "drawable draw type" << std::endl;
}

drawable::~drawable()
{
	//cleanup();
}

bool drawable::isPressed(GLFWwindow* window, int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool drawable::isReleased(GLFWwindow* window, int key)
{
	return glfwGetKey(window, key) == GLFW_RELEASE;
}
