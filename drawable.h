#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <iostream>
#include <vector>
#include "shader.cpp"

#pragma once
class drawable
{
public:

	drawable(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = nullptr);
	~drawable();

	virtual void cleanup() = 0;

	virtual void setup() = 0;

	virtual void processInput(GLFWwindow* window) = 0;

	virtual void draw(glm::mat4& currentModel, glm::mat4& currentProjection, glm::mat4& currentView) = 0;

protected:
	GLenum drawType;
	GLuint* VAO;
	GLuint* VBO;
	GLuint* EBO;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Shader ourShader;

	virtual void reloadBuffers() = 0;
	bool isPressed(GLFWwindow* window, int key);
	bool isReleased(GLFWwindow* window, int key);
};

#endif