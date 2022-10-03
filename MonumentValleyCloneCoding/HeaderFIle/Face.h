#ifndef FACE_H
#define FACE_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

bool OnFace(glm::vec2 point, float* face, int face_vertex_cnt);
bool InPolygon(glm::vec2 point, float* face, int face_vertex_cnt);

#endif