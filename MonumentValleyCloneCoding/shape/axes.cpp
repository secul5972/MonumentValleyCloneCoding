#include "../headerFile/Shape.h"

extern glm::mat4 projection, view, worldModel;

GLuint axes_VBO, axes_VAO;
GLfloat axes_vertices[6][3] = {
	{ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }
};
GLfloat axes_color[3][3] = { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } };

void prepare_axes(void) { // draw coordinate axes
	// initialize vertex buffer object
	glGenBuffers(1, &axes_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, axes_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes_vertices), &axes_vertices[0][0], GL_STATIC_DRAW);

	// initialize vertex array object
	glGenVertexArrays(1, &axes_VAO);
	glBindVertexArray(axes_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, axes_VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_axes(Shader sh) {
	// assume ShaderProgram_simple is used
	sh.use();

	glm::mat4 shapeModel;
	shapeModel = worldModel;
	shapeModel = glm::scale(shapeModel, glm::vec3(100.0f, 100.0f, 100.0f));
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setMat4("model", shapeModel);

	glBindVertexArray(axes_VAO);
	sh.setVec3("objectColor", axes_color[0][0], axes_color[0][1], axes_color[0][2]);
	glDrawArrays(GL_LINES, 0, 2);
	sh.setVec3("objectColor", axes_color[1][0], axes_color[1][1], axes_color[1][2]);
	glDrawArrays(GL_LINES, 2, 2);
	sh.setVec3("objectColor", axes_color[2][0], axes_color[2][1], axes_color[2][2]);
	glDrawArrays(GL_LINES, 4, 2);
	glBindVertexArray(0);
	sh.unuse();
}