#include "../headerFile/Shape.h"

L_shape::L_shape() {}

void L_shape::draw(Shader sh, glm::mat4 model)
{
	//cube
	glm::mat4 shapeModel;

	shapeModel = model;
	cube.draw(sh, shapeModel);

	//cuboid
	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.5f, 0.0f, 0.0f));
	cuboid.draw(sh, shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, 0.0f, 0.5f));
	shapeModel = glm::rotate(shapeModel, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	cuboid.draw(sh, shapeModel);
}