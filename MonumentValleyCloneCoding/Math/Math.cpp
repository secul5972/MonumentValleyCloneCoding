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

float	PlaneEquation(glm::vec3 normal, glm::vec3 point, glm::vec2 val)
{
	return -(normal.x * (val.x - point.x) + normal.y * (val.y - point.y)) / normal.z + point.z;
}

glm::vec3 FindCenterPos(float *face, int face_ver_cnt)
{
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < face_ver_cnt; i++)
	{
		center.x += face[i * 3];
		center.y += face[i * 3 + 1];
		center.z += face[i * 3 + 2];
	}
	center.x /= face_ver_cnt;
	center.y /= face_ver_cnt;
	center.z /= face_ver_cnt;

	return center;
}