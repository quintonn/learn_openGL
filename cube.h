#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4

#include <iostream>
#include <vector>
#include "shader.cpp"

class Cube
{
public:

	Cube();

	void cleanup();

	void setup();

	void processInput(GLFWwindow* window);

	void draw(glm::mat4& currentModel, glm::mat4& currentProjection, glm::mat4& currentView);

private:
	GLenum drawType;
	GLuint* VAO;
	GLuint* VBO;
	GLuint* EBO;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Shader ourShader;

	void reloadBuffers();
};

#endif