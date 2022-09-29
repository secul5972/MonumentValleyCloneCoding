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
	
	
};
bool OnFace(glm::vec2 point, float* face, GLuint face_vertex_cnt);
bool InPolygon(glm::vec2 point, float* face, GLuint face_vertex_cnt);
#endif