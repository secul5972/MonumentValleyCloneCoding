#include "../headerFIle/level.h"

extern bool l_shape_rotate_flag;

double rotateStartTime = 0;
double rotateEndTime = -1;
double rotateCurrTime = 0;
double angle = 0;
int shape = 0;

Level1::Level1()
{

}

void Level1::draw(Shader sh)
{
	glm::mat4 commonModel;
	glm::mat4 model;

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

	if (l_shape_rotate_flag && (rotateEndTime < 0))
	{
		rotateStartTime = glfwGetTime();
		rotateEndTime = glfwGetTime() + 1;
	}

	if (l_shape_rotate_flag && (glfwGetTime() < rotateEndTime))
	{
		rotateCurrTime = glfwGetTime();
		angle = (rotateCurrTime - rotateStartTime) * 90;
		if (shape == 0)
			angle *= -1;
		else
			angle = -90 + angle;
	}
	else if (l_shape_rotate_flag && (glfwGetTime() > rotateEndTime))
	{
		l_shape_rotate_flag = false;
		rotateStartTime = 0;
		rotateEndTime = -1;
		if (shape == 0)
			angle = -90;
		else
			angle = 0;
		shape = !shape;
	}
	if (angle < -45)
		commonModel = glm::translate(commonModel, glm::vec3(-1.8f, -1.8f, -1.8f));

	model = commonModel;
	model = glm::translate(model, glm::vec3(1.8f, 1.8f, 0.0f));
	model = glm::rotate(model, glm::radians(float(-90 + angle)), glm::vec3(1.0f, 0.0f, 0.0f));
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