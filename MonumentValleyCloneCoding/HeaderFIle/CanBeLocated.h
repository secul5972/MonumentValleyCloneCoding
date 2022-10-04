#ifndef CANBELOCATED_H
#define CANBELOCATED_H

#include <glm/glm.hpp>

class CanBeLocated 
{
protected:
	//current face vertex position
	float*				curr_face_ver_ = 0;
	float*				curr_nrm_vec_ = 0;
	const int			kNrmVecSize = 18;

public:
	// can_be_located = true
	virtual float*		IsInObj(glm::vec2, int*, int*) = 0;
	virtual int			GetFaceVerCnt() = 0;
	virtual int			GetFaceCnt() = 0;

	float*				GetCurrFaceVer();
	glm::vec3			GetNormalVec(int);
};

#endif