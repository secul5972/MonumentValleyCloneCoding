#include "../headerFile/Level.h"

void level1_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void level1_mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

double rotateStartTime = 0;
double rotateEndTime = -1;
double rotateCurrTime = 0;
double l_shape_angle = 0;
int shape = 0;

CircleBox *circle_box;
glm::mat4 circle_box_model;
bool l_shape_moving_flag = false;
glm::vec2 prev_mouse_pos_in_model;

Level1::Level1()
{
	circle_box = new CircleBox;
	prev_mouse_pos_in_model.x = -1;
	prev_mouse_pos_in_model.y = -1;
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

	float tmp_angle = fmod(l_shape_angle, 90);
	if (!l_shape_moving_flag)
	{
		if (tmp_angle < 0.5)
			l_shape_angle = int(l_shape_angle / 90) * 90;
		else if (tmp_angle > 90 - 0.5)
			l_shape_angle = (int(l_shape_angle / 90) + 1) % 4 * 90;
		else if (tmp_angle > 45.0f)
			l_shape_angle += deltaTime * 60;
		else
			l_shape_angle -= deltaTime * 60;
	}

	model = commonModel;
	glm::mat4 model2 = commonModel;
	model2 = glm::translate(model2, glm::vec3(1.9f, 1.8f, 0.0f));
	model2 = glm::rotate(model2, glm::radians(float(l_shape_angle)), glm::vec3(1.0f, 0.0f, 0.0f));
	rotary_knob.draw(sh, model2);

	model = glm::translate(model, glm::vec3(2.15f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 3.0f, 3.0f));
	circle_box_model = model;
	circle.draw(sh, model);


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
	{
		left_mouse_button_down = false;
		l_shape_moving_flag = false;
		prev_mouse_pos_in_model.x = -1;
		prev_mouse_pos_in_model.y = -1;
	}
}

void level1_mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (left_mouse_button_down)
	{
		l_shape_angle += circle_box->CheckClickAndRotateInBox((float)xpos, (float)(SCR_HEIGHT - ypos), circle_box_model);
		l_shape_angle = fmod(l_shape_angle + 360, (double)360);
	}
}