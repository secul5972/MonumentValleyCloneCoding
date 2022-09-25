#include "../headerFile/Shape.h"

float* L_shape::base_face_vertex_;

L_shape::L_shape() : Shape(L_SHAPE, true, true), Movement(face_cnt_)
{
	curr_face_vertex_ = new float[face_ver_size_];
	MakeFaceDirFlag();
}

L_shape::~L_shape()
{
	delete[] curr_face_vertex_;
}

void L_shape::MakeFaceVertex()
{
	int idx = 0;
	glm::mat4 pre_model;

	base_face_vertex_ = new float[face_ver_size_];

	pre_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
	pre_model = glm::scale(pre_model, glm::vec3(4.0f, 1.0f, 1.0f));

	for (int i = 1; i < 6; i++)
	{
		for (int j = 0; j < 4; j++) {
			glm::vec4 tmp(cube_face_ver[i * 3 * face_ver_cnt_ + j * 3], cube_face_ver[i * 3 * face_ver_cnt_ + j * 3 + 1], cube_face_ver[i * 3 * face_ver_cnt_ + j * 3 + 2], 1.0f);
			tmp = pre_model * tmp;
			base_face_vertex_[idx * 3] = tmp.x;
			base_face_vertex_[idx * 3 + 1] = tmp.y;
			base_face_vertex_[idx * 3 + 2] = tmp.z;
			idx++;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (i == 3 || i == 5) continue;
		for (int j = 0; j < 4; j++) {
			base_face_vertex_[idx * 3] = cube_face_ver[i * 3 * face_ver_cnt_ + j * 3];
			base_face_vertex_[idx * 3 + 1] = cube_face_ver[i * 3 * face_ver_cnt_ + j * 3 + 1];
			base_face_vertex_[idx * 3 + 2] = cube_face_ver[i * 3 * face_ver_cnt_ + j * 3 + 2];
			idx++;
		}
	}

	pre_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.5f));
	pre_model = glm::rotate(pre_model, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	pre_model = glm::scale(pre_model, glm::vec3(4.0f, 1.0f, 1.0f));

	for (int i = 0; i < 6; i++)
	{
		if (i == 3) continue;
		for (int j = 0; j < 4; j++) {
			glm::vec4 tmp(cube_face_ver[i * 3 * face_ver_cnt_ + j * 3], cube_face_ver[i * 3 * face_ver_cnt_ + j * 3 + 1], cube_face_ver[i * 3 * face_ver_cnt_ + j * 3 + 2], 1.0f);
			tmp = pre_model * tmp;
			base_face_vertex_[idx * 3] = tmp.x;
			base_face_vertex_[idx * 3 + 1] = tmp.y;
			base_face_vertex_[idx * 3 + 2] = tmp.z;
			idx++;
		}
	}
}

void L_shape::DelFaceVertex()
{
	delete[] base_face_vertex_;
}

void L_shape::Draw(glm::mat4 model)
{
	//cube
	glm::mat4 shapeModel;

	shapeModel = model;
	cube.Draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.5f, 0.0f, 0.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(4.0f, 1.0f, 1.0f));
	cube.Draw(shapeModel);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, 0.0f, 0.5f));
	shapeModel = glm::rotate(shapeModel, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	shapeModel = glm::scale(shapeModel, glm::vec3(4.0f, 1.0f, 1.0f));
	cube.Draw(shapeModel);
}

float* L_shape::InShape(glm::vec2 point, int* dir)
{
	float*	face = 0;
	float	depth = 1;
	int		new_dir = -1;


	for (int i = 0; i < face_cnt_; i++)
	{
		if (OnFace(point, curr_face_vertex_ + i * face_ver_cnt_ * 3, face_ver_cnt_))
		{
			float	curr_depth;

			curr_depth = AverDepth(curr_face_vertex_ + i * face_ver_cnt_ * 3, face_ver_cnt_);
			if (curr_depth > depth)continue;
			depth = curr_depth;
			face = curr_face_vertex_ + i * face_ver_cnt_ * 3;
			new_dir = GetFaceDirFlag(i);
		}
	}

	//if face == 0, point is not in shape
	if (!face)
		return 0;
	
	*dir = new_dir;
	return face;
}

void L_shape::SaveModelData(glm::mat4 model)
{
	if (isfixed_ && issaved_) return;
	if (!isfixed_ && !isdirty_) return;
	model_ = model;

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

const int L_shape::GetFaceVerCnt()
{
	return face_ver_cnt_;
}

void L_shape::MakeFaceDirFlag()
{	
	// bottom
	face_dir_flag_[0] = 1;
	// right
	face_dir_flag_[1] = 1;
	// front
	face_dir_flag_[2] = 0;
	// up
	face_dir_flag_[3] = 1;
	// left
	face_dir_flag_[4] = 1;
	// back
	face_dir_flag_[5] = 0;
	// bottom
	face_dir_flag_[6] = 0;
	// right
	face_dir_flag_[7] = 0;
	// up
	face_dir_flag_[8] = 0;
	// back
	face_dir_flag_[9] = 0;
	// bottom
	face_dir_flag_[10] = 1;
	// right
	face_dir_flag_[11] = 1;
	// up
	face_dir_flag_[12] = 1;
	// left
	face_dir_flag_[13] = 1;
}