#include "../headerFile/Shape.h"

unsigned int Circle::tri_VAO, Circle::tri_VBO;
float* circle_vertex;
int circle_vertex_cnt;

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

	circle_vertex_cnt = 362;

	return (0);

}

Circle::Circle()
{
	if (circle_vertex == 0)
		MakeCircleVertex();

	glGenBuffers(1, &tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * circle_vertex_cnt * 6, circle_vertex, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO);
	glBindVertexArray(tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Circle::draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

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