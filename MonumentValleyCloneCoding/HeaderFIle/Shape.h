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

extern glm::mat4 projection, view, worldModel;

class Shape
{
public:
	virtual void draw(Shader sh, glm::mat4 model) = 0;
};

class Cube:Shape
{
protected:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Cube();
	virtual void draw(Shader sh, glm::mat4 model);
};

class Cuboid:Shape
{
protected:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Cuboid();
	virtual void draw(Shader sh, glm::mat4 model);
};

class Goal:Shape
{
protected:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Goal();
	virtual void draw(Shader sh, glm::mat4 model);
};

class L_shape:Shape
{
private:
	Cube cube;
	Cuboid cuboid[2];
protected:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	L_shape();
	virtual void draw(Shader sh, glm::mat4 model);
};

void prepare_axes();
void draw_axes(Shader sh);

#endif
