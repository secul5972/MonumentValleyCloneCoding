#include "../headerFIle/Shape.h"

unsigned int cuboid_tri_VAO, cuboid_tri_VBO, cuboid_line_VAO, cuboid_line_VBO;
extern glm::mat4 projection, view, worldModel;
extern float cube_tri_ver[], cube_line_ver[];


bool prepare_cuboid()
{
#ifndef P_CUBOID
#define P_CUBOID
#endif
	float* cuboid_tri_ver, * cuboid_line_ver;

	if ((cuboid_tri_ver = (float *)malloc(sizeof(float) * 108)) == NULL)
		return (1);
	if ((cuboid_line_ver = (float *)malloc(sizeof(float) * 48)) == NULL)
		return (1);

	glm::mat4 shearing(1.0f);
	shearing = glm::scale(shearing, glm::vec3(4.0f, 1.0f, 1.0f));
	int cnt = 36;
	for (int i = 0; i < cnt; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_tri_ver[i * 3];
		tmp.y = cube_tri_ver[i * 3 + 1];
		tmp.z = cube_tri_ver[i * 3 + 2];
		ret = glm::vec3(shearing * glm::vec4(tmp, 1.0f));
		cuboid_tri_ver[i * 3] = ret.x;
		cuboid_tri_ver[i * 3 + 1] = ret.y;
		cuboid_tri_ver[i * 3 + 2] = ret.z;
	}

	cnt = 16;
	for (int i = 0; i < cnt; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_line_ver[i * 3];
		tmp.y = cube_line_ver[i * 3 + 1];
		tmp.z = cube_line_ver[i * 3 + 2];
		ret = glm::vec3(shearing * glm::vec4(tmp, 1.0f));
		cuboid_line_ver[i * 3] = ret.x;
		cuboid_line_ver[i * 3 + 1] = ret.y;
		cuboid_line_ver[i * 3 + 2] = ret.z;
	}

	//triangle
	glGenBuffers(1, &cuboid_tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, cuboid_tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 108, cuboid_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &cuboid_tri_VAO);
	glBindVertexArray(cuboid_tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//line
	glGenBuffers(1, &cuboid_line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, cuboid_line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 48, cuboid_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &cuboid_line_VAO);
	glBindVertexArray(cuboid_line_VAO);

	// position atlinebute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	free(cuboid_tri_ver);
	free(cuboid_line_ver);

	return (0);
}

void draw_cuboid(Shader sh)
{
	glm::mat4 shapeModel;

	sh.use();

	shapeModel = worldModel;
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