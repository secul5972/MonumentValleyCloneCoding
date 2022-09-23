#include "../headerFile/Shape.h"

float* L_shape::base_face_vertex_;

L_shape::L_shape() : Shape(L_SHAPE, true, true)
{
	base_face_vertex_ = new float[l_shape_face_ver_size];
	curr_face_vertex_ = new float[l_shape_face_ver_size];
}

L_shape::~L_shape()
{
	if (base_face_vertex_)
		delete[] base_face_vertex_;
	if (curr_face_vertex_)
		delete[] curr_face_vertex_;
}

void L_shape::MakeFaceVertex()
{
	int idx = 0;
	glm::mat4 pre_model;

	pre_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
	pre_model = glm::scale(pre_model, glm::vec3(4.0f, 1.0f, 1.0f));

	for (int i = 1; i < 6; i++)
	{
		for (int j = 0; j < 4; j++) {
			glm::vec4 tmp(cube_face_ver[i * 3 * l_shape_face_ver_cnt + j * 3], cube_face_ver[i * 3 * l_shape_face_ver_cnt + j * 3 + 1], cube_face_ver[i * 3 * l_shape_face_ver_cnt + j * 3 + 2], 1.0f);
			tmp = pre_model * tmp;
			base_face_vertex_[idx * 3] = tmp.x;
			base_face_vertex_[idx * 3 + 1] = tmp.y;
			base_face_vertex_[idx * 3 + 2] = tmp.z;
			idx++;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (i == 3 || i == 5)
			continue;
		for (int j = 0; j < 4; j++) {
			base_face_vertex_[idx * 3] = cube_face_ver[i * 3 * l_shape_face_ver_cnt + j * 3];
			base_face_vertex_[idx * 3 + 1] = cube_face_ver[i * 3 * l_shape_face_ver_cnt + j * 3 + 1];
			base_face_vertex_[idx * 3 + 2] = cube_face_ver[i * 3 * l_shape_face_ver_cnt + j * 3 + 2];
			idx++;
		}
	}

	pre_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.5f));
	pre_model = glm::rotate(pre_model, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	pre_model = glm::scale(pre_model, glm::vec3(4.0f, 1.0f, 1.0f));

	for (int i = 1; i < 6; i++)
	{
		for (int j = 0; j < 4; j++) {
			glm::vec4 tmp(cube_face_ver[i * 3 * l_shape_face_ver_cnt + j * 3], cube_face_ver[i * 3 * l_shape_face_ver_cnt + j * 3 + 1], cube_face_ver[i * 3 * l_shape_face_ver_cnt + j * 3 + 2], 1.0f);
			tmp = pre_model * tmp;
			base_face_vertex_[idx * 3] = tmp.x;
			base_face_vertex_[idx * 3 + 1] = tmp.y;
			base_face_vertex_[idx * 3 + 2] = tmp.z;
			idx++;
		}
	}
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

float* L_shape::InShape(glm::vec2 point)
{
	int size = l_shape_face_ver_size / (l_shape_face_ver_cnt * 3);
	float* face = 0;

	for (int i = 0; i < size; i++)
	{
		//check per face
	//	printf("\nL_shape\n");
		if (OnFace(point, curr_face_vertex_ + i * l_shape_face_ver_cnt * 3, l_shape_face_ver_cnt))
		{
			face = curr_face_vertex_ + i * l_shape_face_ver_cnt * 3;
			break;
		}
	}

	//if face == 0, point is not in shape
	if (!face)
		return 0;
	
	return face;
}

void L_shape::SaveModelData(glm::mat4 model)
{
	if (isfixed_ && issaved_) return;
	if (!isfixed_ && !isdirty_) return;
	model_ = model;

	glm::mat4 matrix = viewport * projection * view * model_;
	for (int i = 0; i < l_shape_face_ver_size / 3; i++)
	{
		glm::vec3 prev, curr;
		prev = glm::vec3(base_face_vertex_[i * 3], base_face_vertex_[i * 3 + 1], base_face_vertex_[i * 3 + 2]);
		curr = matrix * glm::vec4(prev, 1.0f);
		curr_face_vertex_[i * 3] = curr.x;
		curr_face_vertex_[i * 3 + 1] = curr.y;
		curr_face_vertex_[i * 3 + 2] = curr.z;
	}
}