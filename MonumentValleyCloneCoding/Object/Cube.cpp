#include "../headerFile/ActerCanGoObject.h"

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

float cube_normal_vec[] = {
	-1.0f,  0.0f,  0.0f,
	 0.0f, -1.0f,  0.0f,
	 0.0f,  0.0f, -1.0f,
	 1.0f,  0.0f,  0.0f,
	 0.0f,  1.0f,  0.0f,
	 0.0f,  0.0f,  1.0f
};

const int cube_tri_ver_cnt = 216;
const int cube_line_ver_cnt = 48;

GLuint Cube::tri_VAO_, Cube::tri_VBO_, Cube::line_VAO_, Cube::line_VBO_;

float* Cube::base_face_vertex_;
float* Cube::base_normal_vec_;

Cube::Cube() : ActerCanGoObject(CUBE, true), MoveDrc(kFaceCnt)
{
	curr_face_vertex_ = new float[kFaceVerSize];
	curr_normal_vec_ = new float[kNrmVecSize];
	disable_face_ = new bool[kFaceCnt];
	fill(disable_face_, disable_face_ + kFaceCnt, false);
	MakeFaceDrcFlag();
};

Cube::~Cube()
{
	delete[] curr_face_vertex_;
	delete[] curr_normal_vec_;
	delete[] disable_face_;
}

void Cube::MakeBuffer()
{
	//triangle
	glGenBuffers(1, &tri_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_tri_ver), cube_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO_);
	glBindVertexArray(tri_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//line
	glGenBuffers(1, &line_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_line_ver), cube_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO_);
	glBindVertexArray(line_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	base_face_vertex_ = cube_face_ver;
	base_normal_vec_ = cube_normal_vec;
}

void Cube::Draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	def_shader->use();
	shapeModel = model;
	def_shader->setMat4("model", shapeModel);
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setVec3("objectColor", obj_color_);
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

float* Cube::MouseInObj(glm::vec2 point, int* dir, int* idx)
{
	float* face = 0;
	int curr_dir = -1;

	for (int i = 0; i < kFaceCnt; i++)
	{
		if (OnFace(point, curr_face_vertex_ + i * kFaceVerCnt * 3, kFaceVerCnt))
		{
			face = curr_face_vertex_ + i * kFaceVerCnt * 3;
			curr_dir = GetFaceDrcFlag(i);
			*idx = i;
			break;
		}
	}

	//if face == 0, point is not in shape
	if (!face)
		return 0;

	*dir = curr_dir;
	return face;
}

void Cube::UpdateObjData(glm::mat4 model)
{
	if (isfixed_ && issaved_) return;
	if (!isfixed_ && !isdirty_) return;
	model_ = model;

	glm::vec3 prev, curr;
	glm::mat4 matrix = vpvp_mat * model_;
	
	for (int i = 0; i < kFaceVerSize / 3; i++)
	{
		prev = glm::vec3(base_face_vertex_[i * 3], base_face_vertex_[i * 3 + 1], base_face_vertex_[i * 3 + 2]);
		curr = matrix * glm::vec4(prev, 1.0f);
		curr_face_vertex_[i * 3] = curr.x;
		curr_face_vertex_[i * 3 + 1] = curr.y;
		curr_face_vertex_[i * 3 + 2] = curr.z;
	}

	for (int i = 0; i < kFaceCnt; i++)
	{
		prev = glm::vec3(base_normal_vec_[i * 3], base_normal_vec_[i * 3 + 1], base_normal_vec_[i * 3 + 2]);
		curr = model * glm::vec4(prev, 0.0f);
		curr_normal_vec_[i * 3] = float(curr.x > 0 ? int(curr.x + 0.5) : int(curr.x - 0.5));
		curr_normal_vec_[i * 3 + 1] = float(curr.y > 0 ? int(curr.y + 0.5) : int(curr.y - 0.5));
		curr_normal_vec_[i * 3 + 2] = float(curr.z > 0 ? int(curr.z + 0.5) : int(curr.z - 0.5));
	}

	if (isfixed_)
		issaved_ = true;
	else
		isdirty_ = false;
}

int Cube::GetFaceVerCnt()
{
	return kFaceVerCnt;
}

int Cube::GetFaceCnt()
{
	return kFaceCnt;
}

void Cube::MakeFaceDrcFlag()
{
	for (int i = 0; i < kFaceCnt; i++)
		face_drc_flag_[i] = 0;
}

int Cube::WGetFaceDrcFlag(int idx)
{
	return GetFaceDrcFlag(idx);
}