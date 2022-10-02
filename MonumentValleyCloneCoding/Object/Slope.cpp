#include "../headerFile/ActerCanGoObject.h"

GLuint Slope::tri_VAO_, Slope::tri_VBO_, Slope::line_VAO_, Slope::line_VBO_;
float* Slope::base_face_vertex_;
float* Slope::base_normal_vec_;
glm::mat4 Slope::pre_model_;

Slope::Slope() : ActerCanGoObject(SLOPE, true), MoveDrc(kFaceCnt)
{
	curr_face_vertex_ = new float[kFaceVerSize];
	curr_normal_vec_ = new float[kNrmVecSize];
	MakeFaceDrcFlag();
}

Slope::~Slope()
{
	delete[] curr_face_vertex_;
	delete[] curr_normal_vec_;
}

void Slope::MakeBuffer()
{
	float* slope_tri_ver = new float[cube_tri_ver_cnt];
	float* slope_line_ver = new float[cube_line_ver_cnt];

	glm::mat4 shapeModel(1.0f);
	shapeModel = glm::translate(shapeModel, glm::vec3(0.4f, 0.2f, 0.0f));
	shapeModel = glm::shearX3D(shapeModel, 2.0f, 1.0f);
	shapeModel = glm::scale(shapeModel, glm::vec3(2.0f, 1.0f, 1.0f));
	pre_model_ = shapeModel;

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
		tmp.x = cube_line_ver[i * 3];
		tmp.y = cube_line_ver[i * 3 + 1];
		tmp.z = cube_line_ver[i * 3 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		slope_line_ver[i * 3] = ret.x;
		slope_line_ver[i * 3 + 1] = ret.y;
		slope_line_ver[i * 3 + 2] = ret.z;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_line_ver_cnt, slope_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO_);
	glBindVertexArray(line_VAO_);

	// position atlinebute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	
	delete[] slope_tri_ver;
	delete[] slope_line_ver;
	base_face_vertex_ = cube_face_ver;
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

float* Slope::InShape(glm::vec2 point, int* dir, int* idx)
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

void Slope::SaveModelData(glm::mat4 model)
{
	if (isfixed_ && issaved_) return;
	if (!isfixed_ && !isdirty_) return;
	model_ = model * pre_model_;

	glm::vec3 prev, curr;
	glm::mat4 matrix = viewport * projection * view * model_;

	for (int i = 0; i < kFaceVerSize / 3; i++)
	{
		prev = glm::vec3(base_face_vertex_[i * 3], base_face_vertex_[i * 3 + 1], base_face_vertex_[i * 3 + 2]);
		curr = matrix * glm::vec4(prev, 1.0f);
		curr_face_vertex_[i * 3] = curr.x;
		curr_face_vertex_[i * 3 + 1] = curr.y;
		curr_face_vertex_[i * 3 + 2] = curr.z;
	}

	if (isfixed_)
		issaved_ = true;
	else
		isdirty_ = false;
}

int Slope::GetFaceVerCnt()
{
	return kFaceVerCnt;
}

int Slope::GetFaceCnt()
{
	return kFaceCnt;
}

void Slope::MakeFaceDrcFlag()
{
	face_drc_flag_[0] = 0;
	face_drc_flag_[1] = 1;
	face_drc_flag_[2] = 1;
	face_drc_flag_[3] = 0;
	face_drc_flag_[4] = 1;
	face_drc_flag_[5] = 1;
}

int Slope::WGetFaceDrcFlag(int idx)
{
	return GetFaceDrcFlag(idx);
}