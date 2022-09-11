#include "../headerFile/Shape.h"

GLuint Axes::line_VAO, Axes::line_VBO;

GLfloat axes_vertices[6][3] = {
	{ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }
};
GLfloat axes_color[3][3] = { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } };

Axes::Axes()
{
	glGenBuffers(1, &line_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes_vertices), &axes_vertices[0][0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, line_VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Axes::draw(glm::mat4 model)
{
	def_shader->use();

	glm::mat4 shapeModel;

	shapeModel = model;
	shapeModel = glm::scale(shapeModel, glm::vec3(100.0f, 100.0f, 100.0f));
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setMat4("model", shapeModel);

	glBindVertexArray(line_VAO);
	def_shader->setVec3("objectColor", axes_color[0][0], axes_color[0][1], axes_color[0][2]);
	glDrawArrays(GL_LINES, 0, 2);
	def_shader->setVec3("objectColor", axes_color[1][0], axes_color[1][1], axes_color[1][2]);
	glDrawArrays(GL_LINES, 2, 2);
	def_shader->setVec3("objectColor", axes_color[2][0], axes_color[2][1], axes_color[2][2]);
	glDrawArrays(GL_LINES, 4, 2);
	glBindVertexArray(0);
	def_shader->unuse();
}