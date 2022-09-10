#include "../headerFile/Shape.h"

unsigned int Goal::tri_VAO, Goal::tri_VBO, Goal::line_VAO, Goal::line_VBO;

Goal::Goal()
{
	float* goal_tri_ver, * goal_line_ver;

	goal_tri_ver = (float*)malloc(sizeof(float) * 216);
	goal_line_ver = (float*)malloc(sizeof(float) * 96);

	glm::mat4 shapeModel(1.0f);
	shapeModel = glm::scale(shapeModel, glm::vec3(1.5f, 0.2f, 1.5f));
	shapeModel = glm::translate(shapeModel, glm::vec3(0.1f, -0.1f, 0.0f));

	for (int i = 0; i < 36; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_tri_ver[i * 6];
		tmp.y = cube_tri_ver[i * 6 + 1];
		tmp.z = cube_tri_ver[i * 6 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_tri_ver[i * 6] = ret.x;
		goal_tri_ver[i * 6 + 1] = ret.y;
		goal_tri_ver[i * 6 + 2] = ret.z;

		tmp.x = cube_tri_ver[i * 6 + 3];
		tmp.y = cube_tri_ver[i * 6 + 4];
		tmp.z = cube_tri_ver[i * 6 + 5];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_tri_ver[i * 6 + 3] = ret.x;
		goal_tri_ver[i * 6 + 4] = ret.y;
		goal_tri_ver[i * 6 + 5] = ret.z;
	}

	for (int i = 0; i < 16; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_line_ver[i * 6];
		tmp.y = cube_line_ver[i * 6 + 1];
		tmp.z = cube_line_ver[i * 6 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_line_ver[i * 6] = ret.x;
		goal_line_ver[i * 6 + 1] = ret.y;
		goal_line_ver[i * 6 + 2] = ret.z;

		tmp.x = cube_line_ver[i * 6 + 3];
		tmp.y = cube_line_ver[i * 6 + 4];
		tmp.z = cube_line_ver[i * 6 + 5];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_line_ver[i * 6 + 3] = ret.x;
		goal_line_ver[i * 6 + 4] = ret.y;
		goal_line_ver[i * 6 + 5] = ret.z;
	}

	//triangle
	glGenBuffers(1, &tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 216, goal_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO);
	glBindVertexArray(tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//line
	glGenBuffers(1, &line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 96, goal_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	// position atlinebute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	free(goal_tri_ver);
	free(goal_line_ver);
}

void Goal::draw(glm::mat4 model)
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