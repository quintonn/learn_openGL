#include "worldTile.h"

worldTile::worldTile() : drawable("instance.shader.vs", "instance.shader.fs")
{
	drawType = GL_STATIC_DRAW;
	
	baseModel = glm::mat4(1.0f);
	baseModel = glm::rotate(baseModel, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	baseModel = glm::rotate(baseModel, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	baseModel = glm::rotate(baseModel, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

worldTile::~worldTile()
{
	cleanup();
}

void worldTile::cleanup()
{

}

void worldTile::setup()
{
	float blockSize = 0.81f;
	int worldSize = 2; 
	// 50 gives 15-16fps using drawElements
	// 50 gives 480fps using drawElementsInstanced
	// 50 gives 380fps using matrix drawElementsInstanced 

	for (int i = 0; i < worldSize; i++)
	{
		for (int j = 0; j < worldSize; j++)
		{
			float xPos = i * blockSize;
			float yPos = j * blockSize;

			glm::mat4 model = baseModel;
			model = glm::translate(baseModel, glm::vec3(xPos, yPos, 0.0f));
			modelMatrices.push_back(model);

			if (i != 0)
			{
				model = glm::translate(baseModel, glm::vec3(-xPos, yPos, 0.0f));
				modelMatrices.push_back(model);
			}
			if (j != 0)
			{
				model = glm::translate(baseModel, glm::vec3(xPos, -yPos, 0.0f));
				modelMatrices.push_back(model);
			}
			if (i != 0 && j != 0)
			{
				model = glm::translate(baseModel, glm::vec3(-xPos, -yPos, 0.0f));
				modelMatrices.push_back(model);
			}
		}
	}

	//modelMatrices[0] = glm::translate(modelMatrices[0], glm::vec3(0, 0, 0.2f));

	colors = {
		glm::vec3(0.55f, 0.71f, 0.29f), // 0 top green
		glm::vec3(0.49f, 0.64f, 0.26f), // 1 front green
		glm::vec3(0.45f, 0.59f, 0.24f), // 2 side green
		glm::vec3(0.68f, 0.51f, 0.34f), // 3 brown
		glm::vec3(0.73f, 0.55f, 0.36f), // 4 front brown
		glm::vec3(0.62f, 0.47f, 0.35f), // 5 side brown
	};
	
	vertices = {
	// top face
	-0.4f, -0.4f,  0.1f,     //  0
	 0.4f, -0.4f,  0.1f,
	 0.4f,  0.4f,  0.1f,
	-0.4f,  0.4f,  0.1f,

	// bottom face
	-0.4f, -0.4f, -0.1f,     //  4
	 0.4f, -0.4f, -0.1f,
	 0.4f,  0.4f, -0.1f,
	-0.4f,  0.4f, -0.1f,

	// left face - bottom
	-0.4f,  0.4f,  0.0f,     //  8
	-0.4f,  0.4f, -0.1f,
	-0.4f, -0.4f, -0.1f,
	-0.4f, -0.4f,  0.0f,

	// left face - top
	-0.4f,  0.4f,  0.1f,     //  12
	-0.4f,  0.4f, -0.0f,
	-0.4f, -0.4f, -0.0f,
	-0.4f, -0.4f,  0.1f,

	// right face - bottom
	 0.4f,  0.4f,  0.0f,     //  16
	 0.4f,  0.4f, -0.1f,
	 0.4f, -0.4f, -0.1f,
	 0.4f, -0.4f,  0.0f,

	 // right face - top
	 0.4f,  0.4f,  0.1f,     //  20
	 0.4f,  0.4f, -0.0f,
	 0.4f, -0.4f, -0.0f,
	 0.4f, -0.4f,  0.1f,

	 // left side face - bottom
	-0.4f, -0.4f, -0.1f,     //  24
	 0.4f, -0.4f, -0.1f,
	 0.4f, -0.4f,  0.0f,
	-0.4f, -0.4f,  0.0f,

	// left side face - top
	-0.4f, -0.4f, -0.0f,     //  28
	 0.4f, -0.4f, -0.0f,
	 0.4f, -0.4f,  0.1f,
	-0.4f, -0.4f,  0.1f,

	// back face - bottom
	-0.4f,  0.4f, -0.1f,     // 32
	 0.4f,  0.4f, -0.1f,
	 0.4f,  0.4f,  0.0f,
	-0.4f,  0.4f,  0.0f,

	// back face - top
	-0.4f,  0.4f, -0.0f,     //  36
	 0.4f,  0.4f, -0.0f,
	 0.4f,  0.4f,  0.1f,
	-0.4f,  0.4f,  0.1f,
	};
	indices = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3,   // second Triangle
		
		4, 5, 7,
		5, 6, 7,

		8,9,11,
		9,10,11,

		12,13,15,
		13,14,15,

		16,17,19,
		17,18,19,

		20,21,23,
		21,22,23,

		24,25,27,
		25,26,27,

		28,29,31,
		29,30,31,

		32,33,35,
		33,34,35,

		36,37,39,
		37,38,39,
	};

	std::cout << "world title draw type" << std::endl;

	glGenVertexArrays(1, VAO);
	
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO); // for index drawing

	glGenBuffers(1, &matrixBuffer);
	
	reloadBuffers();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	// color attribute
	//glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
	
	// matrix attribute
	// set attribute pointers for matrix (4 times vec4)
	glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind

	ourShader.use();
	ourShader.setVec3("colors", 6, colors.data());
}

bool mouseDown = false;
glm::mat4 aProjection = glm::mat4(1.0f);
glm::mat4 aView = glm::mat4(1.0f);
void worldTile::processInput(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && mouseDown == true)
	{
		std::cout << "Mouse button released" << std::endl;
		mouseDown = false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && mouseDown == false)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		//ypos = 600 - ypos;

		mouseDown = true;

		unsigned char pixeldata[4];
		GLfloat depth;
		// reading pixel data at current cursor position ...
		glReadBuffer(GL_COLOR_ATTACHMENT1);	// read from second framebuffer layer
		glReadPixels(xpos, 600 - ypos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixeldata);
		glReadPixels(xpos, 600 - ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

		glm::vec4 viewport = glm::vec4(0, 0, 800, 600);
		glm::vec3 wincoord = glm::vec3(xpos, 600 - ypos, depth);
		
		glm::mat4 baseModel = glm::mat4(1.0f);
		baseModel = glm::rotate(baseModel, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::vec3 objcoord = glm::unProject(wincoord, baseModel, aProjection, viewport);
		
		printf("Coordinates in object space: %f, %f, %f\n", objcoord.x, objcoord.y, objcoord.z);

		int modelIndex = 0;
		// TODO: find out which model from modelMatrices was clicked on
		modelMatrices[0] = glm::translate(modelMatrices[0], glm::vec3(0, 0, 0.2f));

		glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::mat4), &modelMatrices.data()[0]);
		//glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), &modelMatrices.data()[0], drawType);

		// convert pixel color back to (int)ID ...
		//unsigned int m_trackedID = (pixeldata[0] << 0) | (pixeldata[1] << 8) | (pixeldata[2] << 16) | (pixeldata[3] << 24);
		// ------------
		//std::cout << "Mouse button pressed: " << xpos << "-" << ypos << " - " << depth << " - " << m_trackedID << std::endl;
	}

	if (isPressed(window, GLFW_KEY_Z))
	{
		for (int i = 0; i < 40; i++)
		{
			int index = i * 4;
			vertices[index] -= 0.01f;

			glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(float), sizeof(float), &vertices[index]);
		}
	}
	else if (isPressed(window, GLFW_KEY_X))
	{
		for (int i = 0; i < 40; i++)
		{
			int index = i * 4;
			vertices[index] += 0.01f;

			glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(float), sizeof(float), &vertices[index]);
		}
	}
}

void worldTile::draw(glm::mat4& currentModel, glm::mat4& currentProjection, glm::mat4& currentView)
{
	ourShader.use();
	ourShader.setMat4("projection", currentProjection);
	ourShader.setMat4("view", currentView);

	aProjection = currentProjection;
	aView = currentView;

	glBindVertexArray(VAO[0]);
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, modelMatrices.size());
}

void worldTile::reloadBuffers()
{
	glBindVertexArray(VAO[0]);

	// load vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), drawType);

	// load index buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), drawType);

	// load matrix buffer
	glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
	glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), &modelMatrices.data()[0], drawType);
}
