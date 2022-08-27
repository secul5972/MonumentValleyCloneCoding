#ifndef SHAPE_H
#define SHAPE_H

#include "shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>

#include <iostream>
using namespace std;

static float cube_tri_ver[] = {
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	-0.1f,  0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,

	-0.1f, -0.1f,  0.1f,
	 0.1f, -0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f, -0.1f,  0.1f,

	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,

	 0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,

	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,

	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f,
	 0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f
};

static float cube_line_ver[] = {
	-0.1f,	-0.1f,	-0.1f,
	-0.1f,	 0.1f,	-0.1f,
	-0.1f,	 0.1f,	 0.1f,
	-0.1f,	-0.1f,	 0.1f,

	 0.1f,	 0.1f,	 0.1f,
	 0.1f,	-0.1f,	 0.1f,
	 0.1f,	-0.1f,	-0.1f,
	 0.1f,	 0.1f,	-0.1f,

	 0.1f,	-0.1f,	-0.1f,
	-0.1f,	-0.1f,	-0.1f,
	-0.1f,	-0.1f,	 0.1f,
	 0.1f,	-0.1f,	 0.1f,

	-0.1f,	 0.1f,	 0.1f,
	 0.1f,	 0.1f,	 0.1f,
	 0.1f,	 0.1f,	-0.1f,
	-0.1f,	 0.1f,	-0.1f,
};

class Shape
{
protected:
	unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	virtual bool prepare() = 0;
	virtual void draw(Shader sh) = 0;
};

class axes :Shape
{

};

class Cube:Shape
{
public:
	virtual bool prepare();
	virtual void draw(Shader sh);
};

extern glm::mat4 projection, view, worldModel;

#endif
