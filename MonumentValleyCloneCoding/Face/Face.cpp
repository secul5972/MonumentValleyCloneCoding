#include "../headerFile/Face.h"

bool Face::OnFace(glm::vec2 point, float* face, GLuint face_vertex_cnt)
{
	glm::vec3 vecA(face[0], face[1], 0.0f);
	glm::vec3 vecB(face[3], face[4], 0.0f);
	glm::vec3 vecC(face[6], face[7], 0.0f);
	glm::vec3 normal = glm::cross(vecB - vecA, vecC - vecA);

	//for (int j = 0; j < face_vertex_cnt; j++)
	//	printf("(%f, %f)\n", face[j * 3], face[j * 3 + 1]);
	//printf("\n\n");
	if (normal.z < 0)
		return 0;

	//���� ��� �������� �˻�
	if (!InPolygon(point, face, face_vertex_cnt))
		return 0;

	return 1;
}


bool Face::InPolygon(glm::vec2 point, float* face, GLuint face_vertex_cnt) {

	bool in_poly = false;
	glm::vec2 prev_poly(face[(face_vertex_cnt - 1) * 3], face[(face_vertex_cnt - 1) * 3 + 1]);

	for (int i = 0; i < face_vertex_cnt; i++) {
		glm::vec2 poly = glm::vec2(face[i * 3], face[i * 3 + 1]);

		if ((poly.y < point.y && prev_poly.y >= point.y
			|| prev_poly.y < point.y && poly.y >= point.y)
			&& (poly.x <= point.x || prev_poly.x <= point.x)) {
			in_poly ^= (poly.x + (point.y - poly.y) / (prev_poly.y - poly.y) * (prev_poly.x - poly.x) < point.x);
		}
		prev_poly = poly;
	}
	return in_poly;
}

glm::vec2 AlignPos(float* face, int direction, glm::vec2 point, int face_ver_cnt)
{
	glm::vec2 direc, ortho;

	if (direction == 0)
		return point;

	direc = glm::vec2(face[3] - face[0], face[4] - face[1]);
	ortho = glm::vec2(face[6] - face[3], face[7] - face[4]);
	
	if (direction == 2)
		std::swap(direc, ortho);

	glm::vec2 center(0.0f, 0.0f);

	for (int i = 0; i < face_ver_cnt; i++)
	{
		center.x += face[i * 3];
		center.y += face[i * 3 + 1];
	}
	center.x /= face_ver_cnt;
	center.y /= face_ver_cnt;

	glm::vec2 aligned_pos(0.0f, 0.0f);

	if (direc.x == 0)
	{
		aligned_pos.x = center.x;
		if (ortho.y == 0)
			aligned_pos.y = point.y;
		else
			aligned_pos.y = LinearEquation(ortho, point, 1, aligned_pos.x);
	}
	else if (direc.y == 0)
	{
		aligned_pos.y = center.y;
		if (ortho.x == 0)
			aligned_pos.x = point.x;
		else
			aligned_pos.x = LinearEquation(ortho, point, 0, aligned_pos.y);
	}
	else
	{
		aligned_pos.x = (direc.x * ortho.x * (point.y - center.y) + (direc.y * ortho.x * center.x - ortho.y * direc.x * point.x))
			/ (direc.y * ortho.x - ortho.y * direc.x);
		if (ortho.x == 0)
		{
			aligned_pos.x = point.x;
			aligned_pos.y = LinearEquation(direc, center, 1, aligned_pos.x);
		}
		else if (ortho.y == 0)
		{
			aligned_pos.y = point.y;
			aligned_pos.x = LinearEquation(direc, center, 0, aligned_pos.y);
		}
		else
		{
			aligned_pos.x = (direc.x * ortho.x * (point.y - center.y) + (direc.y * ortho.x * center.x - ortho.y * direc.x * point.x))
				/ (direc.y * ortho.x - ortho.y * direc.x);
			aligned_pos.y = LinearEquation(ortho, point, 1, aligned_pos.x);
		}
	}
	return aligned_pos;
}