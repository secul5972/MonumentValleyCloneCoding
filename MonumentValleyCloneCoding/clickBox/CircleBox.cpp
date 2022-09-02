#include "../headerFile/ClickBox.h"

CircleBox::CircleBox(): radius(0.1f)
{
	prev_mouse_pos_in_model.x = -1;
	prev_mouse_pos_in_model.y = -1;
	click_and_rotate_angle = 0;
}

bool CircleBox::CheckClickInBox(float xpos, float ypos, glm::mat4 model)
{
	float		zpos;
	glm::vec4	modelpos;
	glm::vec4	mousepos;

	glReadPixels((int)xpos, (int)ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zpos);
	mousepos = glm::vec4(xpos, ypos, zpos, 1.0f);
	modelpos = glm::inverse(viewport * projection * view * model) * mousepos;

	if (glm::distance(modelpos, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) < radius)
		return (1);
	return (0);
}

float CircleBox::CheckClickAndRotateInBox(float xpos, float ypos, glm::mat4 model)
{
	float		zpos;
	glm::vec4	modelpos;
	glm::vec4	mousepos;

	glReadPixels((int)xpos, (int)ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zpos);
	mousepos = glm::vec4(xpos, ypos, zpos, 1.0f);
	modelpos = glm::inverse(viewport * projection * view * model) * mousepos;

	if (glm::distance(modelpos, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) < radius)
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
				return 0;

			if (glm::cross(glm::vec3(0.0f, prev_mouse_pos_in_model), glm::vec3(0.0f, currpos)).x < (float)0)
				angle = -angle;

			prev_mouse_pos_in_model = currpos;
			return angle;
		}
	}
	return 0;
}
