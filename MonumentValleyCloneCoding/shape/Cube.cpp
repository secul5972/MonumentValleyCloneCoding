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
	// back, x
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,

	// bottom, y
	 0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,

	//right, z
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
	-0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f, -0.1f,
	-0.1f,  0.1f, -0.1f,

	 // left
	-0.1f, -0.1f,  0.1f,
	 0.1f, -0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f
};

GLuint Cube::tri_VAO, Cube::tri_VBO, Cube::line_VAO, Cube::line_VBO;

float* Cube::base_face_vertex_;

Cube::Cube() : Shape(CUBE, true, true)
{
	curr_face_vertex_ = new float[face_ver_size_];
};

Cube::~Cube()
{
	delete []curr_face_vertex_;
}

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

float* Cube::InShape(glm::vec2 point)
{
	int size = face_ver_size_ / (face_ver_cnt_ * 3);
	float* face = 0;

	for (int i = 0; i < size; i++)
	{
		//check per face
		if (OnFace(point, curr_face_vertex_ + i * face_ver_cnt_ * 3, face_ver_cnt_))
		{
			face = curr_face_vertex_ + i * Cube::face_ver_cnt_ * 3;
			break;
		}
	}

	//if face == 0, point is not in shape
	if (!face)
		return 0;

	return face;
}

void Cube::SaveModelData(glm::mat4 model)
{
	if (isfixed_ && issaved_) return;
	if (!isfixed_ && !isdirty_) return;
	model_ = model;

	glm::mat4 matrix = viewport * projection * view * model;
	for (int i = 0; i < face_ver_size_ / 3; i++)
	{
		glm::vec3 prev, curr;
		prev = glm::vec3(base_face_vertex_[i * 3], base_face_vertex_[i * 3 + 1], base_face_vertex_[i * 3 + 2]);
		curr = matrix * glm::vec4(prev, 1.0f);
		curr_face_vertex_[i * 3] = curr.x;
		curr_face_vertex_[i * 3 + 1] = curr.y;
		curr_face_vertex_[i * 3 + 2] = curr.z;
	}
}

const int Cube::GetFaceVerCnt()
{
	return face_ver_cnt_;
}