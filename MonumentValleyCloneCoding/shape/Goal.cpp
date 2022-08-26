#include "../headerFIle/Shape.h"

unsigned int goal_tri_VAO, goal_tri_VBO, goal_line_VAO, goal_line_VBO;
extern glm::mat4 projection, view, worldModel;
extern float cube_tri_ver[], cube_line_ver[];

bool prepare_goal()
{
#ifndef P_GOAL
#define P_GOAL
#endif
	float* goal_tri_ver, * goal_line_ver;

	if ((goal_tri_ver = (float*)malloc(sizeof(float) * 108)) == NULL)
		return (1);
	if ((goal_line_ver = (float*)malloc(sizeof(float) * 48)) == NULL)
		return (1);

	glm::mat4 shapeModel(1.0f);
	shapeModel = glm::scale(shapeModel, glm::vec3(1.5f, 0.2f, 1.5f));
	shapeModel = glm::translate(shapeModel, glm::vec3(0.1f, -0.1f, 0.0f));
	int cnt = 36;
	for (int i = 0; i < cnt; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_tri_ver[i * 3];
		tmp.y = cube_tri_ver[i * 3 + 1];
		tmp.z = cube_tri_ver[i * 3 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_tri_ver[i * 3] = ret.x;
		goal_tri_ver[i * 3 + 1] = ret.y;
		goal_tri_ver[i * 3 + 2] = ret.z;
	}

	cnt = 16;
	for (int i = 0; i < cnt; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_line_ver[i * 3];
		tmp.y = cube_line_ver[i * 3 + 1];
		tmp.z = cube_line_ver[i * 3 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_line_ver[i * 3] = ret.x;
		goal_line_ver[i * 3 + 1] = ret.y;
		goal_line_ver[i * 3 + 2] = ret.z;
		printf("%f %f %f\n", ret.x, ret.y, ret.z);
	}

	//triangle
	glGenBuffers(1, &goal_tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, goal_tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 108, goal_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &goal_tri_VAO);
	glBindVertexArray(goal_tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//line
	glGenBuffers(1, &goal_line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, goal_line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 48, goal_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &goal_line_VAO);
	glBindVertexArray(goal_line_VAO);

	// position atlinebute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	free(goal_tri_ver);
	free(goal_line_ver);

	return (0);
}

void draw_goal(Shader sh)
{
	glm::mat4 shapeModel;

	sh.use();

	shapeModel = worldModel;
	sh.setMat4("model", shapeModel);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setVec3("ObjectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(goal_tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(goal_line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);
	sh.unuse();
}