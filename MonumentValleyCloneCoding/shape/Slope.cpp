#include "../headerFIle/Shape.h"

unsigned int Slope::tri_VAO, Slope::tri_VBO, Slope::line_VAO, Slope::line_VBO;

Slope::Slope()
{
	float* slope_tri_ver, * slope_line_ver;

	slope_tri_ver = (float*)malloc(sizeof(float) * 108);
	slope_line_ver = (float*)malloc(sizeof(float) * 48);

	glm::mat4 shapeModel(1.0f);
	shapeModel = glm::shearY3D(shapeModel, 2.0f, 0.0f);
	shapeModel = glm::translate(shapeModel, glm::vec3(0.2f, 0.1f, 0.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.0f, 2.0f, 1.0f));

	int cnt = 36;
	for (int i = 0; i < cnt; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_tri_ver[i * 3];
		tmp.y = cube_tri_ver[i * 3 + 1];
		tmp.z = cube_tri_ver[i * 3 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		slope_tri_ver[i * 3] = ret.x;
		slope_tri_ver[i * 3 + 1] = ret.y;
		slope_tri_ver[i * 3 + 2] = ret.z;
	}

	cnt = 16;
	for (int i = 0; i < cnt; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_line_ver[i * 3];
		tmp.y = cube_line_ver[i * 3 + 1];
		tmp.z = cube_line_ver[i * 3 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		slope_line_ver[i * 3] = ret.x;
		slope_line_ver[i * 3 + 1] = ret.y;
		slope_line_ver[i * 3 + 2] = ret.z;
	}

	//triangle
	glGenBuffers(1, &tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 108, slope_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO);
	glBindVertexArray(tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//line
	glGenBuffers(1, &line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 48, slope_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	// position atlinebute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	free(slope_tri_ver);
	free(slope_line_ver);
}

void Slope::draw(Shader sh, glm::mat4 model)
{
	glm::mat4 shapeModel;

	sh.use();

	shapeModel = model;
	sh.setMat4("model", shapeModel);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setVec3("ObjectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);
	sh.unuse();
}