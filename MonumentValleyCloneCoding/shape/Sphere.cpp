#include "../headerFile/Shape.h"

GLuint Sphere::tri_VAO, Sphere::tri_VBO;

float* sphere_vertex;
int sphere_vertex_cnt;
int circle_cnt;

Sphere::Sphere() {};

void Sphere::MakeBuffer()
{
	sphere_vertex = (float*)malloc(sizeof(float) * 180 * 360 * 6);

	float radius;

	for (int i = 0; i < 180; i++)
	{
		radius = 0.1 * cos(glm::radians(float(i - 90)));

		for (int j = 0; j < 360; j++)
		{
			sphere_vertex[i * 360 * 6 + j * 6] = radius * sin(glm::radians(float(j)));
			sphere_vertex[i * 360 * 6 + j * 6 + 1] = 0.1 * sin(glm::radians(float(i - 90)));
			sphere_vertex[i * 360 * 6 + j * 6 + 2] = radius * cos(glm::radians(float(j)));
			sphere_vertex[i * 360 * 6 + j * 6 + 3] = 1.0f;
			sphere_vertex[i * 360 * 6 + j * 6 + 4] = 1.0f;
			sphere_vertex[i * 360 * 6 + j * 6 + 5] = 1.0f;
		}
	}

	sphere_vertex_cnt = 360 * 180;
	circle_cnt = 180;

	glGenBuffers(1, &tri_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sphere_vertex_cnt * 6, sphere_vertex, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO);
	glBindVertexArray(tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
} 

void Sphere::FreeVertex()
{
	if (sphere_vertex)
		delete sphere_vertex;
}

void Sphere::draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	def_shader->use();
	shapeModel = model;
	def_shader->setMat4("model", shapeModel);
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(tri_VAO);
	for (int i = 0; i < circle_cnt; i++)
		glDrawArrays(GL_LINE_STRIP, i * 360, sphere_vertex_cnt / circle_cnt);
	def_shader->unuse();
}