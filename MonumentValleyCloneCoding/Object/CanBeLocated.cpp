#include "../headerFile/CanBeLocated.h"

float* CanBeLocated::GetCurrFaceVer() { return curr_face_vertex_; };

glm::vec3 CanBeLocated::GetNormalVec(int idx)
{
	return glm::vec3(curr_normal_vec_[idx * 3], curr_normal_vec_[idx * 3 + 1], curr_normal_vec_[idx * 3 + 2]);
}