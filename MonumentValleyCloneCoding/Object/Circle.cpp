#include "../headerFile/Ornament.h"

GLuint Circle::tri_VAO_, Circle::tri_VBO_;
float* circle_ver;
int circle_ver_cnt;

Circle::Circle() : Ornament(CIRCLE, false) {};

void Circle::MakeBuffer()
{
	circle_ver = new float[362 * 6];

	circle_ver[0] = 0.0f;
	circle_ver[1] = 0.0f;
	circle_ver[2] = 0.0f;
	circle_ver[3] = 1.0f;
	circle_ver[4] = 0.0f;
	circle_ver[5] = 0.0f;

	for (int i = 1; i < 362; i++)
	{
		circle_ver[i * 6] = 0.0f;
		circle_ver[i * 6 + 1] = 0.1f * sin(glm::radians(float(i - 1)));
		circle_ver[i * 6 + 2] = 0.1f * cos(glm::radians(float(i - 1)));
		circle_ver[i * 6 + 3] = 1.0f;
		circle_ver[i * 6 + 4] = 0.0f;
		circle_ver[i * 6 + 5] = 0.0f;
	}

	circle_ver_cnt = 362;

	glGenBuffers(1, &tri_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * circle_ver_cnt * 6, circle_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO_);
	glBindVertexArray(tri_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Circle::FreeVertex()
{
	if (circle_ver)
		delete[] circle_ver;
}

void Circle::Draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

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