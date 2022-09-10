#include "../headerFile/Shape.h"

Character::Character() {}

void Character::draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, 0.35f, 0.0f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(5)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, -0.2f, 0.0f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(90)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.6f, 0.85f, 0.85f));
	corn.draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.02f, 0.5f, 0.0f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(30)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::translate(shapeModel, glm::vec3(0.06f, 0.0f, 0.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.8f, 0.6f, 0.6f));
	corn.draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, 0.0f, 0.04f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(90)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.5f, 0.1f, 0.1f));
	cylinder.draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, 0.0f, -0.04f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(90)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.5f, 0.1f, 0.1f));
	cylinder.draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.02f, 0.5f, 0.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(0.6f, 0.6f, 0.6f));
	sphere.draw(shapeModel);
}