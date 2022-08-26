#include "../headerFIle/Shape.h"

float cube_tri_ver[] = {
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	-0.1f,  0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,

	-0.1f, -0.1f,  0.1f,
	 0.1f, -0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f, -0.1f,  0.1f,

	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,

	 0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,

	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,

	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f
};

float cube_line_ver[] = {
	-0.1f,	-0.1f,	-0.1f,
	-0.1f,	 0.1f,	-0.1f,
	-0.1f,	 0.1f,	 0.1f,
	-0.1f,	-0.1f,	 0.1f,

	 0.1f,	 0.1f,	 0.1f,
	 0.1f,	-0.1f,	 0.1f,
	 0.1f,	-0.1f,	-0.1f,
	 0.1f,	 0.1f,	-0.1f,

	 0.1f,	-0.1f,	-0.1f,
	-0.1f,	-0.1f,	-0.1f,
	-0.1f,	-0.1f,	 0.1f,
	 0.1f,	-0.1f,	 0.1f,

	-0.1f,	 0.1f,	 0.1f,
	 0.1f,	 0.1f,	 0.1f,
	 0.1f,	 0.1f,	-0.1f,
	-0.1f,	 0.1f,	-0.1f,
};

unsigned int cube_tri_VAO, cube_tri_VBO, cube_line_VAO, cube_line_VBO;
extern glm::mat4 projection, view, model;

void prepare_cube()
{
#ifndef P_CUBE
#define P_CUBE
#endif
	//triangle
	glGenBuffers(1, &cube_tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, cube_tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_tri_ver), cube_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &cube_tri_VAO);
	glBindVertexArray(cube_tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//line
	glGenBuffers(1, &cube_line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, cube_line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_line_ver), cube_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &cube_line_VAO);
	glBindVertexArray(cube_line_VAO);

	// position atlinebute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void draw_cube(Shader sh)
{
	glm::mat4 shapeModel;

	sh.use();
	shapeModel = model;
	shapeModel = glm::scale(shapeModel, glm::vec3(1.0f, 1.0f, 1.0f));
	sh.setMat4("model", shapeModel);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setVec3("ObjectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(cube_tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(cube_line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);
	sh.unuse();
}