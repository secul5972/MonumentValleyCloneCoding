#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include "headerFile/Shader.h"
#include "headerFile/camera.h"
#include "headerFile/Shape.h"
#include "headerFile/Level.h"
#include "headerFile/ClickArea.h"
#include "headerFile/AdditionalMathFunction.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void processInput(GLFWwindow* window);
void MakeViewportMatrix();
void PrepareShapeBuffer();

// settings
const GLuint SCR_WIDTH = 1200;
const GLuint SCR_HEIGHT = 1200;

// window
GLFWwindow* window;

// camera
Camera camera(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), -90.0f, 0.0f);

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// matrix
glm::mat4 viewport, projection, view, worldModel;
glm::mat4 vpvp_mat;
glm::mat4 inv_vp, inv_vpvp;
// light
glm::vec3 lightPos, lightColor;

// shader
Shader* def_shader;
Shader* line_shader;

bool left_mouse_button_down = false;

Level* level;

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// glfw window creation
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MonumentVallyCloneCoding", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// tell GLFW to capture our mouse
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile shaders
	def_shader = new Shader("shader/default.vert", "shader/default.frag");
	line_shader = new Shader("shader/line.vert", "shader/line.frag");

	//-- Prepare
	// viewport matrix
	MakeViewportMatrix();
	PrepareShapeBuffer();

	Axes axes;

	level = new Level(12, 2);

	// light setting
	lightPos = glm::vec3(0.0f, 10.0f, 0.0f);
	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	def_shader->use();
	def_shader->setVec3("lightPos", lightPos);
	def_shader->setVec3("lightColor", lightColor);
	def_shader->unuse();

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);
	Slope s;
	s.MakeBuffer();
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		float currentFrame = float(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// render
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// view/projection transformations
		// projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		projection = glm::ortho(-2.0f,2.0f, -2.0f, 2.0f, 0.0f, 100.0f);
		view = camera.GetViewMatrix();

		// base translate
		worldModel = glm::mat4(1.0f);
		worldModel = glm::translate(worldModel, glm::vec3(0.0f, -0.4f, 1.2f));

		vpvp_mat = viewport * projection * view;
		inv_vp = glm::inverse(viewport);
		inv_vpvp = glm::inverse(vpvp_mat);

		// draw_shapes
		axes.Draw(worldModel);
		//s.Draw(worldModel);
		//s.Draw(glm::rotate(worldModel, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f)));
		glfwSetMouseButtonCallback(window, &Level::mouse_button_callback);
		glfwSetCursorPosCallback(window, &Level::mouse_cursor_pos_callback);
		level->Draw(worldModel);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete def_shader;
	delete line_shader;

	//slope.FreeVertex();
	//circle.FreeVertex();
	//sphere.FreeVertex();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void MakeViewportMatrix()
{
	viewport = glm::mat4(1.0f);

	viewport[0][0] = SCR_WIDTH / 2;
	viewport[3][0] = SCR_WIDTH / 2;
	viewport[1][1] = SCR_HEIGHT / 2;
	viewport[3][1] = SCR_HEIGHT / 2;
	viewport[2][2] = 0.5f;
	viewport[3][2] = 0.5f;
}

void PrepareShapeBuffer()
{
	Cube::MakeBuffer();
	Cuboid::MakeBuffer();
	Goal::MakeBuffer();
	Slope::MakeBuffer();
	Circle::MakeBuffer();
	Cylinder::MakeBuffer();
	Corn::MakeBuffer();
	Sphere::MakeBuffer();
}