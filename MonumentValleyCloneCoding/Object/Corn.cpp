#include "../headerFile/Ornament.h"

GLuint Corn::tri_VAO_, Corn::tri_VBO_;

extern float* circle_ver;
extern int circle_ver_cnt;

Corn::Corn() : Ornament(CORN, false) {};

void Corn::MakeBuffer()
{
	circle_ver[0] = 0.2f;

	glGenBuffers(1, &tri_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * circle_ver_cnt * 6, circle_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO_);
	glBindVertexArray(tri_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	circle_ver[0] = 0.0f;
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
	def_shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.2f));

	glBindVertexArray(tri_VAO_);
	glDrawArrays(GL_TRIANGLE_FAN, 0, circle_ver_cnt);
	def_shader->unuse();
}