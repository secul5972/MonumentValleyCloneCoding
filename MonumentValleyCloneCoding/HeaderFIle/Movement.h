#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
using namespace std;

class Movement
{
protected:
	// 0 : don't move
	// 1 : use 0, 1 idx
	// 2 : use 1, 2 idx
	int *face_dir_flag_;
public:
	Movement(int cnt);
	~Movement();
	virtual void	MakeFaceDirFlag() = 0;
	int				GetFaceDirFlag(int);
};

#endif