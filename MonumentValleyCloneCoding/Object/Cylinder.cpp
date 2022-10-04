#include "../headerFile/Ornament.h"

GLuint Cylinder::line_VAO_, Cylinder::line_VBO_;

extern float* circle_ver;
extern int circle_ver_cnt;

Cylinder::Cylinder() : Ornament(CYLINDER, false) {};

void Cylinder::MakeBuffer()
{
	float* cylinder_line_ver = new float[(circle_ver_cnt - 1) * 6 * 2];

	for (int i = 0; i < circle_ver_cnt - 1; i++)
	{
		glm::vec3 tmp;

		cylinder_line_ver[i * 12] = circle_ver[(i + 1) * 6];
		cylinder_line_ver[i * 12 + 1] = circle_ver[(i + 1) * 6 + 1];
		cylinder_line_ver[i * 12 + 2] = circle_ver[(i + 1) * 6 + 2];
		
		tmp = glm::normalize(glm::vec3(0.0f, circle_ver[(i + 1) * 6 + 1], circle_ver[(i + 1) * 6 + 2]));
		cylinder_line_ver[i * 12 + 3] = tmp.x;
		cylinder_line_ver[i * 12 + 4] = tmp.y;
		cylinder_line_ver[i * 12 + 5] = tmp.z;

		cylinder_line_ver[i * 12 + 6] = circle_ver[(i + 1) * 6] + 0.1f;
		cylinder_line_ver[i * 12 + 7] = circle_ver[(i + 1) * 6 + 1];
		cylinder_line_ver[i * 12 + 8] = circle_ver[(i + 1) * 6 + 2];
		cylinder_line_ver[i * 12 + 9] = tmp.x;
		cylinder_line_ver[i * 12 + 10] = tmp.y;
		cylinder_line_ver[i * 12 + 11] = tmp.z;
	}

	glGenBuffers(1, &line_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (circle_ver_cnt - 1) * 6 * 2, cylinder_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO_);
	glBindVertexArray(line_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	delete[] cylinder_line_ver;
}

void Cylinder::Draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	shapeModel = model;
	circle.SetObjColor(obj_color_);
	circle.Draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.1f, 0.0f, 0.0f));
	circle.Draw(shapeModel);

	def_shader->use();

	shapeModel = model;
	def_shader->setMat4("model", shapeModel);
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setVec3("objectColor", obj_color_);

	glBindVertexArray(line_VAO_);
	glDrawArrays(GL_LINES, 0, (circle_ver_cnt - 1) * 2);
	def_shader->unuse();
}