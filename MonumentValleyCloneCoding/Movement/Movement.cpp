#include "../headerFile/Movement.h"

Movement::Movement(int face_cnt)
{
	face_dir_flag_ = new int[face_cnt];
}

Movement::~Movement()
{
	delete[] face_dir_flag_;
}

void	Movement::MakeFaceDirFlag() { cout << "error\n"; }

int		Movement::GetFaceDirFlag(int idx)
{
	return face_dir_flag_[idx];
}