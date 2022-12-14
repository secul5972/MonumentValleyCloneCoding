#include "../headerFile/Face.h"

// Check if a point is on a face
bool OnFace(glm::vec2 point, float* face, int face_vertex_cnt)
{
	glm::vec3 vecA(face[0], face[1], 0.0f);
	glm::vec3 vecB(face[3], face[4], 0.0f);
	glm::vec3 vecC(face[6], face[7], 0.0f);
	glm::vec3 normal = glm::cross(vecB - vecA, vecC - vecA);

	//normal mean screan normal
	if (normal.z < 0)
		return 0;

	if (!InPolygon(point, face, face_vertex_cnt))
		return 0;

	return 1;
}


bool InPolygon(glm::vec2 point, float* face, int face_vertex_cnt) {

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

