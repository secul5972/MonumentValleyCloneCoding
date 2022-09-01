#include "../headerFile/Shape.h"

unsigned int Point::point_VAO, Point::point_VBO;

Point::Point()
{
	if (circle_vertex == 0)
		MakeCircleVertex();

	glGenBuffers(1, &point_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, point_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2172, circle_vertex, GL_STATIC_DRAW);

	glGenVertexArrays(1, &point_VAO);
	glBindVertexArray(point_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Point::draw(Shader sh, glm::mat4 model, glm::vec3 pos)
{
	glm::mat4 shapeModel;

	sh.use();

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, pos);
	//shapeModel = glm::scale(shapeModel, glm::vec3(0.1f, 0.1f, 0.1f));
	sh.setMat4("model", glm::mat4(1.0f));
	sh.setMat4("projection", glm::mat4(1.0f));
	sh.setMat4("view", glm::mat4(1.0f));
	sh.setVec3("objectColor", glm::vec3(0.5f, 1.0f, 1.0f));
	glBindVertexArray(point_VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 362);

	sh.unuse();
}