#include "../headerFile/Shape.h"

float* L_shape::base_face_vertex_;
const int	L_shape::face_shape_cnt_[3] = { 5, 4, 5 };

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

//float* L_shape::InShape(glm::vec2 point, int* dir, int *in_shape_idx)
//{
//	float*	face = 0;
//	float	depth = 1;
//	int		new_dir = -1;
//	int		idx = -1;
//	float*	face_ver = curr_face_vertex_;
//
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < face_shape_cnt_[i]; j++)
//		{
//			if (OnFace(point, face_ver + j * face_ver_cnt_ * 3, face_ver_cnt_))
//			{
//				float	curr_depth;
//
//				curr_depth = AverDepth(face_ver + j * face_ver_cnt_ * 3, face_ver_cnt_);
//				if (curr_depth > depth)continue;
//				depth = curr_depth;
//				face = face_ver + j * face_ver_cnt_ * 3;
//				new_dir = GetFaceDirFlag(j);
//				idx = i;
//			}
//		}
//		face_ver += face_shape_cnt_[i] * face_ver_cnt_ * 3;
//	}
//	//if face == 0, point is not in shape
//	if (!face)
//		return 0;
//	
//	*dir = new_dir;
//	*in_shape_idx = idx;
//	return face;
//}

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
		glm::vec3 tmp = model_ * glm::vec4(prev, 1.0f);
		curr_face_vertex_[i * 3] = curr.x;
		curr_face_vertex_[i * 3 + 1] = curr.y;
		curr_face_vertex_[i * 3 + 2] = curr.z;
	}
}

int L_shape::GetFaceVerCnt()
{
	return face_ver_cnt_;
}

int L_shape::GetFaceCnt()
{
	return face_cnt_;
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

int L_shape::WGetFaceDirFlag(int idx)
{
	return GetFaceDirFlag(idx);
}

float* L_shape::GetCurrFaceVer(int idx)
{
	float* ret = curr_face_vertex_;
	for (int i = 0; i <= idx; i++)
	{
		ret += face_shape_cnt_[idx] * face_ver_cnt_ * 3;
	}
	return ret;
};