#include "../headerFIle/level.h"

extern glm::mat4 worldModel;

void draw_level1(Shader sh)
{
	worldModel = glm::mat4(1.0f);
	worldModel = glm::rotate(worldModel, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	draw_L_shape(sh);

	worldModel = glm::mat4(1.0f);
	worldModel = glm::translate(worldModel, glm::vec3(1.8f, 0.0f, 0.0f));
	worldModel = glm::rotate(worldModel, glm::radians(float(90)), glm::vec3(1.0f, 0.0f, 0.0f));
	worldModel = glm::rotate(worldModel, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	draw_L_shape(sh);

	worldModel = glm::mat4(1.0f);
	worldModel = glm::translate(worldModel, glm::vec3(1.8f, 1.8f, 0.0f));
	worldModel = glm::rotate(worldModel, glm::radians(float(-90)), glm::vec3(1.0f, 0.0f, 0.0f));
	worldModel = glm::rotate(worldModel, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	draw_L_shape(sh);

	worldModel = glm::mat4(1.0f);
	worldModel = glm::translate(worldModel, glm::vec3(1.8f, 1.8f, 0.0f));
	worldModel = glm::rotate(worldModel, glm::radians(float(-180)), glm::vec3(1.0f, 0.0f, 0.0f));
	worldModel = glm::rotate(worldModel, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	draw_L_shape(sh);

	worldModel = glm::mat4(1.0f);
	worldModel = glm::translate(worldModel, glm::vec3(0.4f, 1.8f, 0.0f));
	worldModel = glm::scale(worldModel, glm::vec3(1.25f, 1.0f, 1.0f));
	draw_cuboid(sh);

	worldModel = glm::mat4(1.0f);
	worldModel = glm::translate(worldModel, glm::vec3(0.0f, 2.0f, -0.2f));
	worldModel = glm::rotate(worldModel, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	draw_slope(sh);

	worldModel = glm::mat4(1.0f);
	worldModel = glm::translate(worldModel, glm::vec3(0.0f, 2.3f, -1.1f));
	worldModel = glm::rotate(worldModel, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	draw_goal(sh);
}