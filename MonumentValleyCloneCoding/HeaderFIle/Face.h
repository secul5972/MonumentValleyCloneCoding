#ifndef FACE_H
#define FACE_H

#define GLM_FORCE_SWIZZLE

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <algorithm>
#include <queue>
#include <vector>

#include "Math.h"

class Face
{
protected:

public:
	bool OnFace(glm::vec2 point, float* face, GLuint face_vertex_cnt);
	bool InPolygon(glm::vec2 point, float* face, GLuint face_vertex_cnt);
};

glm::vec3			AlignPos(float* face, int direction, glm::vec2 point, int ver_cnt);
std::vector<int>	FindPath(int start, int end, int size);

#endif