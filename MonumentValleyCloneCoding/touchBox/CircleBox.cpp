#include "../headerFile/TouchBox.h"

CircleBox::CircleBox(): radius(0.1f) {}

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
