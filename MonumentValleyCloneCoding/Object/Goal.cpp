#include "../headerFile/ActerCanGoObject.h"

GLuint Goal::tri_VAO_, Goal::tri_VBO_, Goal::line_VAO_, Goal::line_VBO_;
float* Goal::base_face_ver_;
float* Goal::base_nrm_vec_;
glm::mat4 Goal::pre_model_;

extern float cube_face_ver[];

Goal::Goal() : ActerCanGoObject(GOAL, true), MoveDrc(kFaceCnt)
{
	curr_face_ver_ = new float[kFaceVerSize];
	curr_nrm_vec_ = new float[kNrmVecSize];
	disable_face_ = new bool[kFaceCnt];
	fill(disable_face_, disable_face_ + kFaceCnt, false);
	MakeFaceDrcFlag();
}

Goal::~Goal()
{
	delete[] curr_face_ver_;
	delete[] curr_nrm_vec_;
	delete[] disable_face_;
}

void Goal::MakeBuffer()
{
	float* goal_tri_ver = new float[cube_tri_ver_cnt];
	float* goal_line_ver = new float[cube_line_ver_cnt];

	glm::mat4 shapeModel(1.0f);
	shapeModel = glm::scale(shapeModel, glm::vec3(1.5f, 0.2f, 1.5f));
	shapeModel = glm::translate(shapeModel, glm::vec3(0.1f, -0.1f, 0.0f));
	pre_model_ = shapeModel;

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
		tmp.x = cube_line_ver[i * 3];
		tmp.y = cube_line_ver[i * 3 + 1];
		tmp.z = cube_line_ver[i * 3 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_line_ver[i * 3] = ret.x;
		goal_line_ver[i * 3 + 1] = ret.y;
		goal_line_ver[i * 3 + 2] = ret.z;
	}

	//triangle
	glGenBuffers(1, &tri_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_tri_ver_cnt, goal_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO_);
	glBindVertexArray(tri_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//line
	glGenBuffers(1, &line_VBO_);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_line_ver_cnt, goal_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO_);
	glBindVertexArray(line_VAO_);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	delete[] goal_tri_ver;
	delete[] goal_line_ver;
	base_face_ver_ = cube_face_ver;
	base_nrm_vec_ = cube_normal_vec;
}

void Goal::Draw(glm::mat4 model)
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

float* Goal::IsInObj(glm::vec2 point, int* dir, int* idx)
{
	float* face = 0;
	int curr_dir = -1;

	for (int i = 0; i < kFaceCnt; i++)
	{
		if (OnFace(point, curr_face_ver_ + i * kFaceVerCnt * 3, kFaceVerCnt))
		{
			face = curr_face_ver_ + i * kFaceVerCnt * 3;
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

void Goal::UpdateObjData(glm::mat4 model)
{
	if (isfixed_ && issaved_) return;
	if (!isfixed_ && !isdirty_) return;
	model_ =  model * pre_model_;

	glm::vec3 prev, curr;
	glm::mat4 matrix = viewport * projection * view * model_;

	for (int i = 0; i < kFaceVerSize / 3; i++)
	{
		prev = glm::vec3(base_face_ver_[i * 3], base_face_ver_[i * 3 + 1], base_face_ver_[i * 3 + 2]);
		curr = matrix * glm::vec4(prev, 1.0f);
		curr_face_ver_[i * 3] = curr.x;
		curr_face_ver_[i * 3 + 1] = curr.y;
		curr_face_ver_[i * 3 + 2] = curr.z;
	}

	for (int i = 0; i < kFaceCnt; i++)
	{
		prev = glm::vec3(base_nrm_vec_[i * 3], base_nrm_vec_[i * 3 + 1], base_nrm_vec_[i * 3 + 2]);
		curr = model * glm::vec4(prev, 0.0f);
		curr_nrm_vec_[i * 3] = float(curr.x > 0 ? int(curr.x + 0.5) : int(curr.x - 0.5));
		curr_nrm_vec_[i * 3 + 1] = float(curr.y > 0 ? int(curr.y + 0.5) : int(curr.y - 0.5));
		curr_nrm_vec_[i * 3 + 2] = float(curr.z > 0 ? int(curr.z + 0.5) : int(curr.z - 0.5));
	}

	if (isfixed_)
		issaved_ = true;
	else
		isdirty_ = false;
}

int Goal::GetFaceVerCnt()
{
	return kFaceVerCnt;
}

int Goal::GetFaceCnt()
{
	return kFaceCnt;
}

void Goal::MakeFaceDrcFlag()
{
	for (int i = 0; i < kFaceCnt; i++)
	{
		face_drc_flag_[i] = 0;
	}
}

int Goal::WGetFaceDrcFlag(int idx)
{
	return GetFaceDrcFlag(idx);
}