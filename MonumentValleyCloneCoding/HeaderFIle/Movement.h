#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
using namespace std;

class Movement
{
protected:
	int *face_dir_flag_;
public:
	Movement(int cnt);
	~Movement();
	virtual void	MakeFaceDirFlag();
	int				GetFaceDirFlag(int);
};

#endif