#include "../headerFile/Shape.h"

float cube_tri_ver[] = {
	-0.1f, -0.1f, -0.1f,  0.0f,  0.0f, -1.0f,
	 0.1f, -0.1f, -0.1f,  0.0f,  0.0f, -1.0f,
	 0.1f,  0.1f, -0.1f,  0.0f,  0.0f, -1.0f,
	 0.1f,  0.1f, -0.1f,  0.0f,  0.0f, -1.0f,
	-0.1f,  0.1f, -0.1f,  0.0f,  0.0f, -1.0f,
	-0.1f, -0.1f, -0.1f,  0.0f,  0.0f, -1.0f,

	-0.1f, -0.1f,  0.1f,  0.0f,  0.0f, 1.0f,
	 0.1f, -0.1f,  0.1f,  0.0f,  0.0f, 1.0f,
	 0.1f,  0.1f,  0.1f,  0.0f,  0.0f, 1.0f,
	 0.1f,  0.1f,  0.1f,  0.0f,  0.0f, 1.0f,
	-0.1f,  0.1f,  0.1f,  0.0f,  0.0f, 1.0f,
	-0.1f, -0.1f,  0.1f,  0.0f,  0.0f, 1.0f,

	-0.1f,  0.1f,  0.1f, -1.0f,  0.0f,  0.0f,
	-0.1f,  0.1f, -0.1f, -1.0f,  0.0f,  0.0f,
	-0.1f, -0.1f, -0.1f, -1.0f,  0.0f,  0.0f,
	-0.1f, -0.1f, -0.1f, -1.0f,  0.0f,  0.0f,
	-0.1f, -0.1f,  0.1f, -1.0f,  0.0f,  0.0f,
	-0.1f,  0.1f,  0.1f, -1.0f,  0.0f,  0.0f,

	 0.1f,  0.1f,  0.1f,  1.0f,  0.0f,  0.0f,
	 0.1f,  0.1f, -0.1f,  1.0f,  0.0f,  0.0f,
	 0.1f, -0.1f, -0.1f,  1.0f,  0.0f,  0.0f,
	 0.1f, -0.1f, -0.1f,  1.0f,  0.0f,  0.0f,
	 0.1f, -0.1f,  0.1f,  1.0f,  0.0f,  0.0f,
	 0.1f,  0.1f,  0.1f,  1.0f,  0.0f,  0.0f,

	-0.1f, -0.1f, -0.1f,  0.0f, -1.0f,  0.0f,
	 0.1f, -0.1f, -0.1f,  0.0f, -1.0f,  0.0f,
	 0.1f, -0.1f,  0.1f,  0.0f, -1.0f,  0.0f,
	 0.1f, -0.1f,  0.1f,  0.0f, -1.0f,  0.0f,
	-0.1f, -0.1f,  0.1f,  0.0f, -1.0f,  0.0f,
	-0.1f, -0.1f, -0.1f,  0.0f, -1.0f,  0.0f,

	-0.1f,  0.1f, -0.1f,  0.0f,  1.0f,  0.0f,
	 0.1f,  0.1f, -0.1f,  0.0f,  1.0f,  0.0f,
	 0.1f,  0.1f,  0.1f,  0.0f,  1.0f,  0.0f,
	 0.1f,  0.1f,  0.1f,  0.0f,  1.0f,  0.0f,
	-0.1f,  0.1f,  0.1f,  0.0f,  1.0f,  0.0f,
	-0.1f,  0.1f, -0.1f,  0.0f,  1.0f,  0.0f
};


float cube_side_ver[] = {
	-0.1f, -0.1f, -0.1f,
	-0.1f,  0.1f, -0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f, -0.1f,  0.1f,

	 0.1f,  0.1f,  0.1f,
	 0.1f, -0.1f,  0.1f, 
	 0.1f, -0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,

	 0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f,  0.1f,
	 0.1f, -0.1f,  0.1f,

	-0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f, -0.1f,
	-0.1f,  0.1f, -0.1f
};

GLuint Cube::tri_VAO, Cube::tri_VBO, Cube::line_VAO, Cube::line_VBO;

Cube::Cube()
{
	//triangle
	glGenBuffers(1, &tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_tri_ver), cube_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO);
	glBindVertexArray(tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//line
	glGenBuffers(1, &line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_side_ver), cube_side_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	def_shader->use();
	shapeModel = model;
	def_shader->setMat4("model", shapeModel);
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	def_shader->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);
	def_shader->unuse();
}