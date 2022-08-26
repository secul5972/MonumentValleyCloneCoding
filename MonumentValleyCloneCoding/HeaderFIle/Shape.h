#ifndef SHAPE_H
#define SHAPE_H

#include "shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
using namespace std;

bool prepare_cuboid();
void draw_cuboid(Shader sh);

void prepare_cube();
void draw_cube(Shader sh);

void prepare_L_shape();
void draw_L_shape(Shader sh);

#endif
