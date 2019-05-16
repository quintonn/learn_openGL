#ifndef TEXTITEM_H
#define TEXTITEM_H

#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include "drawable.h"

#include <map>
#include "Character.cpp"
#include <ft2build.h>
#include FT_FREETYPE_H
class textItem : public drawable
{
public:
	textItem();
	~textItem();

	void cleanup();
	void setup();
	void processInput(GLFWwindow* window);
	void draw(glm::mat4& currentModel, glm::mat4& currentProjection, glm::mat4& currentView);

protected:
	void reloadBuffers();

private:

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	std::map<GLchar, Character> Characters;
	float previousTime;
	int frameCount;
	std::string text;
};

#endif