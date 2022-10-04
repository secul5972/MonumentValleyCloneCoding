#ifndef MOVEDRC_H
#define MOVEDRC_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class MoveDrc
{
protected:
	// 0 : center
	// 1 : use 0, 1 idx
	// 2 : use 1, 2 idx
	int *face_drc_flag_;
public:
	MoveDrc(int cnt);
	~MoveDrc();
	virtual void	MakeFaceDrcFlag() = 0;
	int				GetFaceDrcFlag(int);
};

#endif