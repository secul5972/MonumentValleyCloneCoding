#include "../headerFile/Ornament.h"

GLuint Corn::tri_VAO_, Corn::tri_VBO_;

extern float* circle_ver;
extern int circle_ver_cnt;

Corn::Corn() : Ornament(CORN, false) {};

void Corn::MakeBuffer()
{
	float* corn_ver = new float[circle_ver_cnt * 6];

	for (int i = 0; i < circle_ver_cnt; i++)
	{
		corn_ver[i * 6] = circle_ver[i * 6];
		corn_ver[i * 6 + 1] = circle_ver[i * 6 + 1];
		corn_ver[i * 6 + 2] = circle_ver[i * 6 + 2];

		glm::vec3 tmp = glm::normalize(glm::vec3(0.04f, 0.8 * circle_ver[i * 6 + 1], 0.8 * circle_ver[i * 6 + 2]));
		corn_ver[i * 6 + 3] = tmp.x;
		corn_ver[i * 6 + 4] = tmp.y;
		corn_ver[i * 6 + 5] = tmp.z;
	}
	corn_ver[0] = 0.2f;

	glGenBuffers(1, &tri_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * circle_ver_cnt * 6, corn_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO_);
	glBindVertexArray(tri_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Corn::Draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	circle.Draw(model);

	def_shader->use();
	shapeModel = model;
	def_shader->setMat4("model", shapeModel);
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setVec3("objectColor", obj_color_);

	glBindVertexArray(tri_VAO_);
	glDrawArrays(GL_TRIANGLE_FAN, 0, circle_ver_cnt);
	def_shader->unuse();
}