#include "../headerFile/CanBeLocated.h"

float* CanBeLocated::GetCurrFaceVer() { return curr_face_ver_; };

glm::vec3 CanBeLocated::GetNormalVec(int idx)
{
	return glm::vec3(curr_nrm_vec_[idx * 3], curr_nrm_vec_[idx * 3 + 1], curr_nrm_vec_[idx * 3 + 2]);
}