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

	//점이 평면 내부인지 검사
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

