#include "../headerFile/Math.h"

float LinearEquation(glm::vec2 vec, glm::vec2 point, int flag, float val)
{

	if (flag == 1)
	{
		//find y
		return (val - point.x) * vec.y / vec.x + point.y;
	}
	else
	{
		//find x
		return (val - point.y) * vec.x / vec.y + point.x;
	}
}

float AverDepth(float* face, int ver_cnt)
{
	float ret = 0;

	for (int i = 0; i < ver_cnt; i++)
	{
		ret += face[i * 3 + 2];
	}
	return ret / ver_cnt;
}