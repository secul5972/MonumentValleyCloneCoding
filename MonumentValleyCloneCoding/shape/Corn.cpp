#include "../headerFile/Shape.h"

unsigned int Corn::tri_VAO, Corn::tri_VBO;

extern float* circle_vertex;
extern int circle_vertex_cnt;

Corn::Corn()
{
	if (circle_vertex == 0)
		MakeCircleVertex();

	circle_vertex[0] = 0.2f;

	glGenBuffers(1, &tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * circle_vertex_cnt * 6, circle_vertex, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO);
	glBindVertexArray(tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	circle_vertex[0] = 0.0f;
}

void Corn::draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	circle.draw(model);

	def_shader->use();

	shapeModel = model;
	def_shader->setMat4("model", shapeModel);
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.2f));

	glBindVertexArray(tri_VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, circle_vertex_cnt);
	def_shader->unuse();
}