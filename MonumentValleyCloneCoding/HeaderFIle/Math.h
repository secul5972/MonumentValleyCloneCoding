#ifndef MATH_H
#define MATH_H

#include <glm/glm.hpp>

float	LinearEquation(glm::vec2 vec, glm::vec2 point, int flag, float val);
float	AverDepth(float* face, int ver_cnt);
float	PlaneEquation(glm::vec3 normal, glm::vec3 point, glm::vec2 val);
#endif