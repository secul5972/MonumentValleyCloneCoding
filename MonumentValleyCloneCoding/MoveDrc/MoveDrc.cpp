#include "../headerFile/MoveDrc.h"

MoveDrc::MoveDrc(int face_cnt)
{
	face_drc_flag_ = new int[face_cnt];
}

MoveDrc::~MoveDrc()
{
	delete[] face_drc_flag_;
}

int		MoveDrc::GetFaceDrcFlag(int idx)
{
	return face_drc_flag_[idx];
}