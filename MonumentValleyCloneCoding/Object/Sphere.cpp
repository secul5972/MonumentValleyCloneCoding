#include "../headerFile/Shape.h"

GLuint Sphere::tri_VAO_, Sphere::tri_VBO_;

float* sphere_ver;
int sphere_ver_cnt;
int circle_cnt;

Sphere::Sphere() : Shape(SPHERE, false, true) {};

void Sphere::MakeBuffer()
{
	sphere_ver = new float[180 * 360 * 6];

	float radius;

	for (int i = 0; i < 180; i++)
	{
		radius = 0.1f * cos(glm::radians(float(i - 90)));

		for (int j = 0; j < 360; j++)
		{
			sphere_ver[i * 360 * 6 + j * 6] = radius * sin(glm::radians(float(j)));
			sphere_ver[i * 360 * 6 + j * 6 + 1] = 0.1f * sin(glm::radians(float(i - 90)));
			sphere_ver[i * 360 * 6 + j * 6 + 2] = radius * cos(glm::radians(float(j)));
			sphere_ver[i * 360 * 6 + j * 6 + 3] = 1.0f;
			sphere_ver[i * 360 * 6 + j * 6 + 4] = 1.0f;
			sphere_ver[i * 360 * 6 + j * 6 + 5] = 1.0f;
		}
	}

	sphere_ver_cnt = 360 * 180;
	circle_cnt = 180;

	glGenBuffers(1, &tri_VBO_);

	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sphere_ver_cnt * 6, sphere_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO_);
	glBindVertexArray(tri_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
} 

void Sphere::FreeVertex()
{
	if (sphere_ver)
		delete sphere_ver;
}

void Sphere::Draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	def_shader->use();
	shapeModel = model;
	def_shader->setMat4("model", shapeModel);
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(tri_VAO_);
	for (int i = 0; i < circle_cnt; i++)
		glDrawArrays(GL_LINE_STRIP, i * 360, sphere_ver_cnt / circle_cnt);
	def_shader->unuse();
}