#include "../headerFIle/Shape.h"

float cuboid_tri_ver[] = {
	-0.4f, -0.1f, -0.1f,
	 0.4f, -0.1f, -0.1f,
	 0.4f,  0.1f, -0.1f,
	 0.4f,  0.1f, -0.1f,
	-0.4f,  0.1f, -0.1f,
	-0.4f, -0.1f, -0.1f,

	-0.4f, -0.1f,  0.1f,
	 0.4f, -0.1f,  0.1f,
	 0.4f,  0.1f,  0.1f,
	 0.4f,  0.1f,  0.1f,
	-0.4f,  0.1f,  0.1f,
	-0.4f, -0.1f,  0.1f,

	-0.4f,  0.1f,  0.1f,
	-0.4f,  0.1f, -0.1f,
	-0.4f, -0.1f, -0.1f,
	-0.4f, -0.1f, -0.1f,
	-0.4f, -0.1f,  0.1f,
	-0.4f,  0.1f,  0.1f,

	 0.4f,  0.1f,  0.1f,
	 0.4f,  0.1f, -0.1f,
	 0.4f, -0.1f, -0.1f,
	 0.4f, -0.1f, -0.1f,
	 0.4f, -0.1f,  0.1f,
	 0.4f,  0.1f,  0.1f,

	-0.4f, -0.1f, -0.1f,
	 0.4f, -0.1f, -0.1f,
	 0.4f, -0.1f,  0.1f,
	 0.4f, -0.1f,  0.1f,
	-0.4f, -0.1f,  0.1f,
	-0.4f, -0.1f, -0.1f,

	-0.4f,  0.1f, -0.1f,
	 0.4f,  0.1f, -0.1f,
	 0.4f,  0.1f,  0.1f,
	 0.4f,  0.1f,  0.1f,
	-0.4f,  0.1f,  0.1f,
	-0.4f,  0.1f, -0.1f
};

float cuboid_line_ver[] = {
	-0.4f,	-0.1f,	-0.1f,
	-0.4f,	 0.1f,	-0.1f,
	-0.4f,	 0.1f,	 0.1f,
	-0.4f,	-0.1f,	 0.1f,

	 0.4f,	 0.1f,	 0.1f,
	 0.4f,	-0.1f,	 0.1f,
	 0.4f,	-0.1f,	-0.1f,
	 0.4f,	 0.1f,	-0.1f,

	 0.4f,	-0.1f,	-0.1f,
	-0.4f,	-0.1f,	-0.1f,
	-0.4f,	-0.1f,	 0.1f,
	 0.4f,	-0.1f,	 0.1f,

	-0.4f,	 0.1f,	 0.1f,
	 0.4f,	 0.1f,	 0.1f,
	 0.4f,	 0.1f,	-0.1f,
	-0.4f,	 0.1f,	-0.1f,
};

unsigned int cuboid_tri_VAO, cuboid_tri_VBO, cuboid_line_VAO, cuboid_line_VBO;
extern glm::mat4 projection, view, worldModel;

void prepare_cuboid()
{
#ifndef P_CUBOID
#define P_CUBOID
#endif
	//triangle
	glGenBuffers(1, &cuboid_tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, cuboid_tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cuboid_tri_ver), cuboid_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &cuboid_tri_VAO);
	glBindVertexArray(cuboid_tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//line
	glGenBuffers(1, &cuboid_line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, cuboid_line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cuboid_line_ver), cuboid_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &cuboid_line_VAO);
	glBindVertexArray(cuboid_line_VAO);

	// position atlinebute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void draw_cuboid(Shader sh)
{
	glm::mat4 shapeModel;

	sh.use();
	shapeModel = worldModel;
	shapeModel = glm::scale(shapeModel, glm::vec3(1.0f, 1.0f, 1.0f));
	sh.setMat4("model", shapeModel);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setVec3("ObjectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(cuboid_tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(cuboid_line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);
	sh.unuse();
}