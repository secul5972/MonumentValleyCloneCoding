#include "../headerFile/ClickArea.h"

EllipseArea::EllipseArea() {}

bool EllipseArea::CheckClickInArea(float xpos, float ypos, glm::mat4 model)
{
	glm::mat4 affine = viewport * projection * view * model;

	float model_y, model_z;

	model_y = (affine[2][0] * (ypos - affine[3][1]) + affine[2][1] * (affine[3][0] - xpos))
		/ (affine[2][0] * affine[1][1] - affine[2][1] * affine[1][0]);
	model_z = (xpos - affine[3][0] - affine[1][0] * ypos) / affine[2][0];

	if (model_y * model_y + model_z * model_z < 0.01)
		return (1);
	return (0);
}

float EllipseArea::CheckClickAndRotateInArea(float xpos, float ypos, glm::mat4 model)
{
	glm::mat4 affine = viewport * projection * view * model;
	glm::vec3 modelpos;

	modelpos.y = (affine[2][0] * (ypos - affine[3][1]) + affine[2][1] * (affine[3][0] - xpos))
		/ (affine[2][0] * affine[1][1] - affine[2][1] * affine[1][0]);
	modelpos.z = (xpos - affine[3][0] - affine[1][0] * ypos) / affine[2][0];

	if (modelpos.y * modelpos.y + modelpos.z * modelpos.z < 0.01)
	{
		l_shape_moving_flag = true;
		if (prev_mouse_pos_in_model.x == -1)
		{
			prev_mouse_pos_in_model = glm::normalize(glm::vec2(modelpos.y, modelpos.z));
			return 0;
		}
		else
		{
			glm::vec2 currpos = glm::normalize(glm::vec2(modelpos.y, modelpos.z));
			float angle = glm::degrees(acos(glm::dot(prev_mouse_pos_in_model, currpos)));

			if (isnan(angle))
				angle = 0;

			if (glm::cross(glm::vec3(0.0f, prev_mouse_pos_in_model), glm::vec3(0.0f, currpos)).x < (float)0)
				angle = -angle;

			prev_mouse_pos_in_model = currpos;
			if (!left_mouse_button_down)
				prev_mouse_pos_in_model.x = -1;
			return angle;
		}
	}
	return 0;
}
