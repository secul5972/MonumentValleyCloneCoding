#include "../headerFile/Shape.h"

GLuint Line::line_VAO, Line::line_VBO;

GLfloat line_vertices[2][3] = {
	{0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}
};

extern Shader* test_shader;
Line::Line() : Shape(DEFAULT, false, true)
{
	glGenBuffers(1, &line_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_vertices), &line_vertices[0][0], GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, line_VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Line::Draw(glm::mat4 model)
{
	test_shader->use();
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(line_vertices), &line_vertices[0][0]);
	glBindVertexArray(line_VAO);
	def_shader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	test_shader->unuse();
}