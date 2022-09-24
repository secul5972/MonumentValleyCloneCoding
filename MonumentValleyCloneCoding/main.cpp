#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include "headerFile/Shader.h"
#include "headerFile/camera.h"
#include "headerFile/model.h"
#include "headerFile/Shape.h"
#include "headerFile/Level.h"
#include "headerFile/ClickArea.h"
#include "headerFile/AdditionalMathFunction.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void MakeViewportMatrix();

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

// light
glm::vec3 lightPos, lightColor;

// shader
Shader* def_shader;
Shader* test_shader;

bool left_mouse_button_down = false;

Level1* level1;

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

	// tell GLFW to capture our mouse
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	// build and compile shaders
	def_shader = new Shader("shader/default.vert", "shader/default.frag");
	test_shader = new Shader("shader/test.vert", "shader/test.frag");

	// viewport matrix
	MakeViewportMatrix();

	// prepare_shapes
	Axes axes;
	Cube cube;
	Cuboid cuboid;
	Goal goal;
	Slope slope;
	Circle circle;
	L_shape l_shape;

	Cylinder cylinder;
	Rotary_Knob rotary_knob;
	Corn corn;
	Character character;
	Sphere sphere;

	level1 = new Level1;

	cube.MakeBuffer();
	cuboid.MakeBuffer();
	goal.MakeBuffer();
	slope.MakeBuffer();
	circle.MakeBuffer();
	cylinder.MakeBuffer();
	corn.MakeBuffer();
	sphere.MakeBuffer();

	l_shape.MakeFaceVertex();

	// light setting
	lightPos = glm::vec3(0.0f, 10.0f, 0.0f);
	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	def_shader->use();
	def_shader->setVec3("lightPos", lightPos);
	def_shader->setVec3("lightColor", lightColor);
	def_shader->unuse();

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		float currentFrame = static_cast<float>(glfwGetTime());
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

		// draw_shapes
		axes.Draw(worldModel);
		//cube.Draw(worldModel);
		//goal.Draw(worldModel);
		//slope.Draw(worldModel);
		//circle.Draw(worldModel);
		//e.Draw(defaultShader, worldModel);
		//f.Draw(defaultShader, worldModel);
		//g.Draw(defaultShader, worldModel);
		glfwSetMouseButtonCallback(window, &Level1::mouse_button_callback);
		glfwSetCursorPosCallback(window, &Level1::mouse_cursor_pos_callback);
		level1->Draw(worldModel);
		//h.Draw(defaultShader, worldModel);
		//m.Draw(defaultShader, worldModel);
		//n.Draw(defaultShader, worldModel);
		//o.Draw(defaultShader, worldModel);
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	if (def_shader)
		delete def_shader;

	slope.FreeVertex();
	circle.FreeVertex();
	sphere.FreeVertex();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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