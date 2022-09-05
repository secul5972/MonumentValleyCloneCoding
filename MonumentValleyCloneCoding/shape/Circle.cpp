#include "../headerFile/Shape.h"

unsigned int Circle::line_VAO, Circle::line_VBO;

bool MakeCircleVertex()
{
	if (!(circle_vertex = (float*)malloc(sizeof(float) * 362 * 6)))
		return (1);

	circle_vertex[0] = 0.0f;
	circle_vertex[1] = 0.0f;
	circle_vertex[2] = 0.0f;
	circle_vertex[3] = 1.0f;
	circle_vertex[4] = 1.0f;
	circle_vertex[5] = 1.0f;

	for (int i = 1; i < 362; i++)
	{
		circle_vertex[i * 6] = 0.0f;
		circle_vertex[i * 6 + 1] = 0.1 * sin(glm::radians(float(i - 1)));
		circle_vertex[i * 6 + 2] = 0.1 * cos(glm::radians(float(i - 1)));
		circle_vertex[i * 6 + 3] = 1.0f;
		circle_vertex[i * 6 + 4] = 1.0f;
		circle_vertex[i * 6 + 5] = 1.0f;
	}
	//circle_vertex[361 * 6] = 0.0f;
	//circle_vertex[361 * 6 + 1] = 0.0f;
	//circle_vertex[361 * 6 + 2] = 0.0f;
	//circle_vertex[361 * 6 + 3] = 1.0f;
	//circle_vertex[361 * 6 + 4] = 1.0f;
	//circle_vertex[361 * 6 + 5] = 1.0f;

	return (0);

}

Circle::Circle()
{
	if (circle_vertex == 0)
		MakeCircleVertex();

	glGenBuffers(1, &line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2172, circle_vertex, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Circle::draw(Shader sh, glm::mat4 model)
{
	glm::mat4 shapeModel;

	sh.use();

	shapeModel = model;
	sh.setMat4("model", shapeModel);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(line_VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 362);

	sh.unuse();
}