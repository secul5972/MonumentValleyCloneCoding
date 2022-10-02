#include "../headerFile/Shape.h"

GLuint Slope::tri_VAO_, Slope::tri_VBO_, Slope::line_VAO_, Slope::line_VBO_;
float* slope_face_ver;
int slope_face_ver_cnt;

Slope::Slope() : Shape(SLOPE, true, true) {};

void Slope::MakeBuffer()
{
	float* slope_tri_ver;

	slope_tri_ver = new float[216];
	slope_face_ver = new float[48];

	glm::mat4 shapeModel(1.0f);
	shapeModel = glm::shearY3D(shapeModel, 2.0f, 0.0f);
	shapeModel = glm::translate(shapeModel, glm::vec3(0.2f, 0.1f, 0.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(1.0f, 2.0f, 1.0f));

	for (int i = 0; i < 36; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_tri_ver[i * 6];
		tmp.y = cube_tri_ver[i * 6 + 1];
		tmp.z = cube_tri_ver[i * 6 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		slope_tri_ver[i * 6] = ret.x;
		slope_tri_ver[i * 6 + 1] = ret.y;
		slope_tri_ver[i * 6 + 2] = ret.z;

		tmp.x = cube_tri_ver[i * 6 + 3];
		tmp.y = cube_tri_ver[i * 6 + 4];
		tmp.z = cube_tri_ver[i * 6 + 5];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		slope_tri_ver[i * 6 + 3] = ret.x;
		slope_tri_ver[i * 6 + 4] = ret.y;
		slope_tri_ver[i * 6 + 5] = ret.z;
	}

	for (int i = 0; i < 16; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_face_ver[i * 3];
		tmp.y = cube_face_ver[i * 3 + 1];
		tmp.z = cube_face_ver[i * 3 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		slope_face_ver[i * 3] = ret.x;
		slope_face_ver[i * 3 + 1] = ret.y;
		slope_face_ver[i * 3 + 2] = ret.z;
	}

	//triangle
	glGenBuffers(1, &tri_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 216, slope_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO_);
	glBindVertexArray(tri_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//line
	glGenBuffers(1, &line_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 48, slope_face_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO_);
	glBindVertexArray(line_VAO_);

	// position atlinebute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	slope_face_ver_cnt = 48;
	delete[] slope_tri_ver;
}

void Slope::FreeVertex()
{
	if (slope_face_ver)
		free(slope_face_ver);
}

void Slope::Draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	def_shader->use();
	shapeModel = model;
	def_shader->setMat4("model", shapeModel);
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(tri_VAO_);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	def_shader->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(line_VAO_);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);
	def_shader->unuse();
}