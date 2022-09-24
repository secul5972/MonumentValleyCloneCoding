#include "../headerFile/Shape.h"

GLuint Cuboid::tri_VAO, Cuboid::tri_VBO, Cuboid::line_VAO, Cuboid::line_VBO;
float* Cuboid::base_face_vertex_;
glm::mat4 Cuboid::pre_model_;

Cuboid::Cuboid() : Shape(CUBOID, true, true), Movement(face_cnt_)
{
	curr_face_vertex_ = new float[face_ver_size_];
	MakeFaceDirFlag();
};

Cuboid::~Cuboid()
{
	delete[] curr_face_vertex_;
}

void Cuboid::MakeBuffer()
{
	float* cuboid_tri_ver = new float[cube_tri_ver_cnt];
	float* cuboid_line_ver = new float[cube_line_ver_cnt];

	glm::mat4 shapeModel(1.0f);
	shapeModel = glm::scale(shapeModel, glm::vec3(4.0f, 1.0f, 1.0f));
	pre_model_ = shapeModel;

	for (int i = 0; i < 36; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_tri_ver[i * 6];
		tmp.y = cube_tri_ver[i * 6 + 1];
		tmp.z = cube_tri_ver[i * 6 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		cuboid_tri_ver[i * 6] = ret.x;
		cuboid_tri_ver[i * 6 + 1] = ret.y;
		cuboid_tri_ver[i * 6 + 2] = ret.z;

		tmp.x = cube_tri_ver[i * 6 + 3];
		tmp.y = cube_tri_ver[i * 6 + 4];
		tmp.z = cube_tri_ver[i * 6 + 5];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		cuboid_tri_ver[i * 6 + 3] = ret.x;
		cuboid_tri_ver[i * 6 + 4] = ret.y;
		cuboid_tri_ver[i * 6 + 5] = ret.z;
	}

	for (int i = 0; i < 16; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_line_ver[i * 3];
		tmp.y = cube_line_ver[i * 3 + 1];
		tmp.z = cube_line_ver[i * 3 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		cuboid_line_ver[i * 3] = ret.x;
		cuboid_line_ver[i * 3 + 1] = ret.y;
		cuboid_line_ver[i * 3 + 2] = ret.z;
	}


	//triangle
	glGenBuffers(1, &tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, cube_tri_ver_cnt * sizeof(float), cuboid_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO);
	glBindVertexArray(tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//line
	glGenBuffers(1, &line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferData(GL_ARRAY_BUFFER, cube_line_ver_cnt * sizeof(float), cuboid_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] cuboid_tri_ver;
	delete[] cuboid_line_ver;
	base_face_vertex_ = cube_face_ver;
}

void Cuboid::Draw(glm::mat4 model)
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

float* Cuboid::InShape(glm::vec2 point, int* dir)
{
	float* face = 0;
	int curr_dir = -1;

	for (int i = 0; i < face_cnt_; i++)
	{
		if (OnFace(point, curr_face_vertex_ + i * face_ver_cnt_ * 3, face_ver_cnt_))
		{
			face = curr_face_vertex_ + i * face_ver_cnt_ * 3;
			curr_dir = GetFaceDirFlag(i);
			break;
		}
	}

	//if face == 0, point is not in shape
	if (!face)
		return 0;

	*dir = curr_dir;
	return face;
}

void Cuboid::SaveModelData(glm::mat4 model)
{
	if (isfixed_ && issaved_) return;
	if (!isfixed_ && !isdirty_) return;
	model_ = model * pre_model_;

	glm::mat4 matrix = viewport * projection * view * model_;
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

const int Cuboid::GetFaceVerCnt()
{
	return face_ver_cnt_;
}

void Cuboid::MakeFaceDirFlag()
{
	face_dir_flag_[0] = 0;
	face_dir_flag_[1] = 1;
	face_dir_flag_[2] = 1;
	face_dir_flag_[3] = 0;
	face_dir_flag_[4] = 1;
	face_dir_flag_[5] = 1;
}