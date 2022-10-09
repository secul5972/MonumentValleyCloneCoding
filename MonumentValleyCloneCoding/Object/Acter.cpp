#include "../headerFile/Ornament.h"

Acter::Acter() : Ornament(ACTER, false) {}

void Acter::Draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	model = glm::rotate(model, glm::radians(acter_rotate_angle_), glm::vec3(0.0f, 1.0f, 0.0f));
	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, 0.35f, 0.0f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(5)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, -0.2f, 0.0f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(90)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.6f, 0.85f, 0.85f));
	corn.SetObjColor(glm::vec3(1.0f, 1.0f, 1.0f));
	corn.Draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.02f, 0.5f, 0.0f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(150)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::translate(shapeModel, glm::vec3(0.02f, 0.0f, 0.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.8f, 0.6f, 0.6f));
	corn.SetObjColor(glm::vec3(1.0f, 1.0f, 1.0f));
	corn.Draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, 0.0f, 0.04f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(90)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.5f, 0.1f, 0.1f));
	cylinder.SetObjColor(glm::vec3(1.0f, 1.0f, 1.0f));
	cylinder.Draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, 0.0f, -0.04f));
	shapeModel = glm::rotate(shapeModel, glm::radians(float(90)), glm::vec3(0.0f, 0.0f, 1.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.5f, 0.1f, 0.1f));
	cylinder.SetObjColor(glm::vec3(1.0f, 1.0f, 1.0f));
	cylinder.Draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.02f, 0.5f, 0.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(0.6f, 0.6f, 0.6f));
	sphere.SetObjColor(glm::vec3(1.0f, 0.85f, 0.72f));
	sphere.Draw(shapeModel);
}

void	Acter::SetActerRotateAngle(float acter_rotate_angle) { acter_rotate_angle_ = acter_rotate_angle; }