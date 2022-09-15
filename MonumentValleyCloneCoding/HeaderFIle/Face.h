#ifndef FACE_H
#define FACE_H

#define GLM_FORCE_SWIZZLE

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Face
{
protected:
	enum FaceType {
		NONE,
		BACK,
		BOTTOM,
		RIGHT,
		FRONT,
		UP,
		LEFT
	};

	static const int kFaceTypeCnt = 7;

	//face normal vector
	static const glm::vec3 kFaceAxes[];
	//remove vec3 factor
	static const glm::vec3 kFaceFactor[];

public:
	bool OnFace(glm::vec2 point, float* face, GLuint face_vertex_cnt);
	bool InPolygon(glm::vec2 point, float* face, GLuint face_vertex_cnt, FaceType ft);
};


#endif