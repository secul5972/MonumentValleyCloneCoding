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


float cube_line_ver[] = {
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

float cube_face_ver[] = {
	// back
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,

	// bottom
	 0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,

	//right
	 0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,

	// front
	 0.1f, -0.1f,  0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f,
	 
	// up
	 0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f

	 // left
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	-0.1f,  0.1f, -0.1f,


};

//size of cube_face_ver
const GLuint cube_face_ver_size = 72;
//count of cube face(rectangle) vertex
const GLuint cube_face_ver_cnt = 4;

GLuint Cube::tri_VAO, Cube::tri_VBO, Cube::line_VAO, Cube::line_VBO;

Cube::Cube() : Shape(CUBE, true, true) {};

void Cube::MakeBuffer()
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_line_ver), cube_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	base_face_vertex_ = cube_face_ver;
	curr_face_vertex_ = new float[cube_face_ver_size];

	for (int i = 0; i < cube_face_ver_size; i++)
		curr_face_vertex_[i] = cube_face_ver[i];
}

void Cube::Draw(glm::mat4 model)
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

float* Cube::IsOnShape(glm::vec3 point)
{
	if (isfixed_ == false && isdirty_ == true)
	{
		//update curr_face_vertex
		isdirty_ = false;
	}

	int size = cube_face_ver_size / (cube_face_ver_cnt * 3);
	for (int i = 0; i < cube_face_ver_size; i++)
	{
		//면이 평행한지 검사 필요

		if (IsOnFace(point, curr_face_vertex_ + i * 4, cube_face_ver_cnt))
			return curr_face_vertex_ + i * 4;
	}

	//fail to find
	return (0);
}