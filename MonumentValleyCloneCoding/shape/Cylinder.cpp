#include "../headerFile/Shape.h"

unsigned int Cylinder::line_VAO, Cylinder::line_VBO;

extern float* circle_vertex;
extern int circle_vertex_cnt;

Cylinder::Cylinder()
{

	float* cylinder_line_ver;

	cylinder_line_ver = (float*)malloc(sizeof(float) * (circle_vertex_cnt - 1) * 6 * 2);
	for (int i = 0; i < circle_vertex_cnt - 1; i++)
	{
		cylinder_line_ver[i * 12] = circle_vertex[(i + 1) * 6];
		cylinder_line_ver[i * 12 + 1] = circle_vertex[(i + 1) * 6 + 1];
		cylinder_line_ver[i * 12 + 2] = circle_vertex[(i + 1) * 6 + 2];
		cylinder_line_ver[i * 12 + 3] = circle_vertex[(i + 1) * 6 + 3];
		cylinder_line_ver[i * 12 + 4] = circle_vertex[(i + 1) * 6 + 4];
		cylinder_line_ver[i * 12 + 5] = circle_vertex[(i + 1) * 6 + 5];

		cylinder_line_ver[i * 12 + 6] = circle_vertex[(i + 1) * 6] + 0.1f;
		cylinder_line_ver[i * 12 + 7] = circle_vertex[(i + 1) * 6 + 1];
		cylinder_line_ver[i * 12 + 8] = circle_vertex[(i + 1) * 6 + 2];
		cylinder_line_ver[i * 12 + 9] = circle_vertex[(i + 1) * 6 + 3];
		cylinder_line_ver[i * 12 + 10] = circle_vertex[(i + 1) * 6 + 4];
		cylinder_line_ver[i * 12 + 11] = circle_vertex[(i + 1) * 6 + 5];
	}

	glGenBuffers(1, &line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (circle_vertex_cnt - 1) * 6 * 2, cylinder_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	free(cylinder_line_ver);
}

void Cylinder::draw(Shader sh, glm::mat4 model)
{
	glm::mat4 shapeModel;

	shapeModel = model;
	circle.draw(sh, shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.1f, 0.0f, 0.0f));
	circle.draw(sh, shapeModel);

	sh.use();

	shapeModel = model;
	sh.setMat4("model", shapeModel);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.2f));

	glBindVertexArray(line_VAO);
	glDrawArrays(GL_LINES, 0, (circle_vertex_cnt - 1) * 2);
	sh.unuse();
}