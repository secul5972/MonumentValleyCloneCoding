#include "../headerFile/Level.h"

void level1_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void level1_mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

double rotateStartTime = 0;
double rotateEndTime = -1;
double rotateCurrTime = 0;
double l_shape_angle = 0;
int shape = 0;

extern Shader *aa;
CircleBox *circle_box;
glm::mat4 circle_box_model;
bool l_shape_rotate_flag = false;
bool l_shape_moving_flag = false;

extern bool left_mouse_button_down;
extern glm::vec2 prev_mouse_pos;

Level1::Level1()
{
	circle_box = new CircleBox;
}

void Level1::draw(Shader sh)
{
	glm::mat4 commonModel;
	glm::mat4 model;

	glfwSetMouseButtonCallback(window, level1_mouse_button_callback);
	glfwSetCursorPosCallback(window, level1_mouse_cursor_pos_callback);

	commonModel = glm::mat4(1.0f);
	commonModel = glm::translate(commonModel, glm::vec3(0.0f, -0.4f, 1.2f));

	model = commonModel;
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	l_shape[0].draw(sh, model);

	model = commonModel;
	model = glm::translate(model, glm::vec3(1.8f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	l_shape[1].draw(sh, model);

	model = commonModel;
	model = glm::translate(model, glm::vec3(1.91f, 1.91f, 0.0f));
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	circle_box_model = model;
	circle.draw(sh, model);

	//if (l_shape_rotate_flag && (rotateEndTime < 0))
	//{
	//	rotateStartTime = glfwGetTime();
	//	rotateEndTime = glfwGetTime() + 1;
	//	l_shape_moving_flag = true;
	//}

	//if (l_shape_rotate_flag && (glfwGetTime() < rotateEndTime))
	//{
	//	rotateCurrTime = glfwGetTime();
	//	l_shape_angle = (rotateCurrTime - rotateStartTime) * 90;
	//	if (shape == 0)
	//		l_shape_angle *= -1;
	//	else
	//		l_shape_angle = -90 + l_shape_angle;
	//}
	//else if (l_shape_rotate_flag && (glfwGetTime() > rotateEndTime))
	//{
	//	rotateStartTime = 0;
	//	rotateEndTime = -1;
	//	if (shape == 0)
	//		l_shape_angle = -90;
	//	else
	//		l_shape_angle = 0;
	//	shape = !shape;
	//	l_shape_rotate_flag = false;
	//	l_shape_moving_flag = false;
	//}
	if (225 < l_shape_angle && l_shape_angle < 315)
		commonModel = glm::translate(commonModel, glm::vec3(-1.8f, -1.8f, -1.8f));

	model = commonModel;
	model = glm::translate(model, glm::vec3(1.8f, 1.8f, 0.0f));
	model = glm::rotate(model, glm::radians(float(-90 + l_shape_angle)), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	l_shape[2].draw(sh, model);

	model = commonModel;
	model = glm::translate(model, glm::vec3(0.4f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.25f, 1.0f, 1.0f));
	cuboid.draw(sh, model);

	model = commonModel;
	model = glm::translate(model, glm::vec3(0.0f, 2.0f, -0.2f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	slope.draw(sh, model);

	model = commonModel;
	model = glm::translate(model, glm::vec3(0.0f, 2.3f, -1.1f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	goal.draw(sh, model);
}

Level1::~Level1()
{
	if (circle_box)
		delete circle_box;
}

void level1_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		left_mouse_button_down = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		left_mouse_button_down = false;
}

void level1_mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (left_mouse_button_down)
	{
		l_shape_angle += circle_box->CheckClickAndRotateInBox((float)xpos, (float)(SCR_HEIGHT - ypos), circle_box_model);
		l_shape_angle = fmod(l_shape_angle + 360, (double)360);
	}
}