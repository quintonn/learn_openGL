#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.cpp"
#include <iostream>
#include "camera.cpp"
#include "textItem.h"

#include "cube.h"
#include "worldTile.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
bool isPressed(GLFWwindow* window, int key);
bool isReleased(GLFWwindow* window, int key);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int PAN_SPEED = 25;

const bool ENABLE_MOUSE = false;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float zoom = -10.0f;
float xPos = 0.0f;
float yPos = 0.0f;

float zoomAmount = 0.055f; //todo: i think this is related to projection ratio

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	
	// Put the window in the middle of the screen
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int window_width = mode->width;
	int window_height = mode->height;
	glfwSetWindowPos(window, (window_width / 2) - (SCR_WIDTH / 2), (window_height / 2) - (SCR_HEIGHT / 2));

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (ENABLE_MOUSE)
	{
		glfwSetCursorPosCallback(window, mouse_callback); // mouse movement
	}
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	if (ENABLE_MOUSE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	// for fonts
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Cube sample = Cube();
	sample.setup();
	worldTile tileBlock = worldTile();
	tileBlock.setup();
	textItem textSample = textItem();
	textSample.setup();

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f); // change the 100 to be able to see more
	//glm::mat4 projection = glm::ortho(5.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
	    // --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// input
		// -----
		processInput(window);
		tileBlock.processInput(window);
		sample.processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind Texture
		//glBindTexture(GL_TEXTURE_2D, texture);

		// pass projection matrix to shader (note that in this case it could change every frame)
		//glm::mat4 projection = glm::mat4(1.0f);

		glm::mat4 view;
		// camera/view transformation
		if (ENABLE_MOUSE)
		{
			view = camera.GetViewMatrix();
		}
		else
		{
			view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(xPos, yPos, zoom));
		}

		// model
		glm::mat4 model = glm::mat4(1.0f);
		// Rotate first to get isometric view
		
		tileBlock.draw(model, projection, view);
		sample.draw(model, projection, view);
		textSample.draw(model, projection, view);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	sample.cleanup();
	tileBlock.cleanup();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (ENABLE_MOUSE)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	if (isPressed(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (isPressed(window, GLFW_KEY_B))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (isPressed(window, GLFW_KEY_C))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (ENABLE_MOUSE == false)
	{
		if (isPressed(window, GLFW_KEY_A))
		{
			xPos += (deltaTime * PAN_SPEED);
		}
		else if (isPressed(window, GLFW_KEY_D))
		{
			xPos -= (deltaTime * PAN_SPEED);
		}

		if (isPressed(window, GLFW_KEY_W))
		{
			yPos -= (deltaTime * PAN_SPEED);
			zoom += zoomAmount;
		}
		else if (isPressed(window, GLFW_KEY_S))
		{
			yPos += (deltaTime * PAN_SPEED);
			zoom -= zoomAmount;
		}
	}

	if (isPressed(window, GLFW_KEY_O))
	{
		zoom += 1;
	}
	else if (isPressed(window, GLFW_KEY_P))
	{
		zoom -= 1;
	}
}

bool isPressed(GLFWwindow* window, int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isReleased(GLFWwindow* window, int key)
{
	return glfwGetKey(window, key) == GLFW_RELEASE;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// I think i can use this function to do right click drag.
	//TODO

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (ENABLE_MOUSE)
	{
		camera.ProcessMouseScroll(yoffset);
	}
	else
	{
		zoom += (yoffset * 1);
	}
}
