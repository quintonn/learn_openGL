#include "cube.h"

Cube::Cube() : ourShader("cube.shader.vs", "cube.shader.fs")
{
	VAO = new GLuint;
	VBO = new GLuint;
	EBO = new GLuint;

	//vertices = {};
	vertices = {
	 0.4f-1.0f,  0.4f, 0.0f, 0.5f, 0.5f, 0.5f,  // top right
	 0.4f-1.0f, -0.4f, 0.0f, 0.5f, 0.5f, 0.5f,  // bottom right
	-0.4f-1.0f, -0.4f, 0.0f, 0.5f, 0.5f, 0.5f,  // bottom left
	-0.4f-1.0f,  0.4f, 0.0f, 0.5f, 0.5f, 0.5f   // top left 
	};
	indices = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	//drawType = GL_DYNAMIC_DRAW;
	drawType = GL_STATIC_DRAW;
}

void Cube::cleanup()
{
	glDeleteVertexArrays(1, VAO);
	glDeleteBuffers(1, VBO);
	glDeleteBuffers(1, EBO);
}

void Cube::setup()
{
	glGenVertexArrays(1, VAO);
	//std::cout << "VAO - " << VAO[0] << std::endl;
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO); // for index drawing

	reloadBuffers();
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind
	//glBindVertexArray(0); //unbind
}

void Cube::processInput(GLFWwindow* window)
{

}

void Cube::draw(glm::mat4& currentModel, glm::mat4& currentProjection, glm::mat4& currentView)
{
	ourShader.use();

	glm::mat4 projection = glm::mat4(1.0f);
	ourShader.setMat4("projection", projection);

	glm::mat4 view = glm::mat4(1.0f);
	
	ourShader.setMat4("view", view);
	ourShader.setMat4("model", currentModel);
	glBindVertexArray(VAO[0]);
	//glDrawArrays(GL_TRIANGLES, 0, 12);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//glBindVertexArray(0);
}

void Cube::reloadBuffers()
{
	glBindVertexArray(VAO[0]);
	
	// load vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), drawType);

	// load index buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), drawType);
}