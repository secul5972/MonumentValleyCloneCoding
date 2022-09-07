#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include "headerFile/shader.h"
#include "headerFile/camera.h"
#include "headerFile/model.h"
//shape
#include "headerFile/Shape.h"
#include "headerFile/Level.h"
//ClickArea
#include "headerFile/ClickArea.h"

#include "headerFile/AdditionalMathFunction.h"
//#include <stb/stb_image.h>
//#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void MakeViewportMatrixWithoutDepth();

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1200;

//window
GLFWwindow* window;

// camera
Camera camera(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), -90.0f, 0.0f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::mat4 projection, view, worldModel;
glm::mat4 viewport;
glm::vec3 lightPos, lightColor;

bool left_mouse_button_down = false;
///////////////////////////////////////////////////////////////
Shader* aa;
///////////////////////////////////////////////////////////////
int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MonumentVallyCloneCoding", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader defaultShader("shader/default.vert", "shader/default.frag");
	aa = new Shader("shader/test.vert", "shader/test.frag");
	// load models
	// -----------
	//Model ourModel("objects/backpack/backpack.obj");

	// viewport matrix
	// ---------------
	MakeViewportMatrixWithoutDepth();

	// prepare_shapes
	// ---------------
	prepare_axes();
	//MakeCircleVertex();
	Cube a;
	Cuboid b;
	Goal c;
	L_shape d;
	Slope e;
	Level1 l;
	Circle f;
	Cylinder g;
	Rotary_Knob h;
	//light
	// ----
	lightPos = glm::vec3(0.0f, 10.0f, 0.0f);
	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	defaultShader.use();
	defaultShader.setVec3("lightPos", lightPos);
	defaultShader.setVec3("lightColor", lightColor);
	defaultShader.unuse();
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// view/projection transformations
		//projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		projection = glm::ortho(-2.0f,2.0f, -2.0f, 2.0f, 0.0f, 100.0f);
		view = camera.GetViewMatrix();

		//draw_shapes
		worldModel = glm::mat4(1.0f);
		worldModel = glm::translate(worldModel, glm::vec3(0.0f, -0.4f, 1.2f));
		draw_axes(defaultShader);
		//a.draw(defaultShader, worldModel);
		//b.draw(defaultShader, worldModel);
		//c.draw(defaultShader, worldModel);
		//d.draw(defaultShader, worldModel);
		//e.draw(defaultShader, worldModel);
		//f.draw(defaultShader, worldModel);
		//g.draw(defaultShader, worldModel);
		l.draw(defaultShader);
		//h.draw(defaultShader, worldModel);
		 
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

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
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void MakeViewportMatrixWithoutDepth()
{
	glm::mat4 viewport_matrix(1.0f);

	viewport_matrix[0][0] = SCR_WIDTH / 2;
	viewport_matrix[3][0] = SCR_WIDTH / 2;
	viewport_matrix[1][1] = SCR_HEIGHT / 2;
	viewport_matrix[3][1] = SCR_HEIGHT / 2;
	viewport_matrix[2][2] = 0.5f;
	viewport_matrix[3][2] = 0.5f;

	viewport = viewport_matrix;
}