#ifndef WORLDTILE_H
#define WORLDTILE_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include "drawable.h"

#pragma once
class worldTile : public drawable
{
public:
	worldTile();
	~worldTile();
	
	void cleanup();
	void setup();
	void processInput(GLFWwindow* window);
	void draw(glm::mat4& currentModel, glm::mat4& currentProjection, glm::mat4& currentView);

protected:
	void reloadBuffers();
	std::vector<glm::mat4> modelMatrices;
	std::vector<glm::vec3> colors;
	unsigned int matrixBuffer;
	glm::mat4 baseModel;
};

#endif