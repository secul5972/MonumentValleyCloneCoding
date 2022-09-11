#include "../headerFile/Shape.h"

Rotary_Knob::Rotary_Knob() {}

void Rotary_Knob::draw(glm::mat4 model)
{
	//cuboid
	glm::mat4 shapeModel;

	shapeModel = model;
	shapeModel = glm::scale(shapeModel, glm::vec3(1.0f, 0.25f, 0.25f));
	shapeModel = glm::translate(shapeModel, glm::vec3(0.1f, 0.0f, 0.0f));
	cube.draw(shapeModel);

	//cylinder
	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.2f, 0.0f, 0.0f));
	cylinder.draw(shapeModel);

	for (int i = 0; i < 4; i++)
	{
		shapeModel = model;

		shapeModel = glm::translate(shapeModel, glm::vec3(0.25f, 0.0f, 0.0f));
		shapeModel = glm::rotate(shapeModel, glm::radians((float)90) * i, glm::vec3(1.0f, 0.0f, 0.0f));
		shapeModel = glm::rotate(shapeModel, glm::radians((float)90), glm::vec3(0.0f, 0.0f, 1.0f));
		shapeModel = glm::translate(shapeModel, glm::vec3(0.1f, 0.0f, 0.0f));
		shapeModel = glm::scale(shapeModel, glm::vec3(1.5f, 0.25f, 0.25f));
		cylinder.draw(shapeModel);
	}

	for (int i = 0; i < 4; i++)
	{
		shapeModel = model;

		shapeModel = glm::translate(shapeModel, glm::vec3(0.25f, 0.0f, 0.0f));
		shapeModel = glm::rotate(shapeModel, glm::radians((float)90) * i, glm::vec3(1.0f, 0.0f, 0.0f));
		shapeModel = glm::rotate(shapeModel, glm::radians((float)90), glm::vec3(0.0f, 0.0f, 1.0f));
		shapeModel = glm::translate(shapeModel, glm::vec3(0.25f, 0.0f, 0.0f));
		shapeModel = glm::scale(shapeModel, glm::vec3(0.4f, 0.4f, 0.4f));
		cylinder.draw(shapeModel);
	}
}