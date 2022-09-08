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

extern glm::mat4 projection, view;
extern float cube_tri_ver[];
extern float cube_line_ver[];

class Shape
{
public:
	virtual void draw(Shader sh, glm::mat4 model) = 0;
};

class Cube :Shape
{
protected:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Cube();
	void draw(Shader sh, glm::mat4 model);
};

class Cuboid :Shape
{
protected:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Cuboid();
	void draw(Shader sh, glm::mat4 model);
};

class Goal :Shape
{
protected:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Goal();
	void draw(Shader sh, glm::mat4 model);
};

class L_shape :Shape
{
private:
	Cube cube;
	Cuboid cuboid;
public:
	L_shape();
	void draw(Shader sh, glm::mat4 model);
};

class Slope :Shape
{
protected:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Slope();
	void draw(Shader sh, glm::mat4 model);
};

class Circle :Shape
{
protected:
	static unsigned int tri_VAO, tri_VBO;
public:
	Circle();
	void draw(Shader sh, glm::mat4 model);
};

class Cylinder :Shape
{
protected:
	static unsigned int line_VAO, line_VBO;
	Circle circle;
public:
	Cylinder();
	void draw(Shader sh, glm::mat4 model);
};

class Rotary_Knob :Shape
{
private:
	Cylinder cylinder;
	Cube cube;
public:
	Rotary_Knob();
	void draw(Shader sh, glm::mat4 model);
};

bool MakeCircleVertex();
void prepare_axes();
void draw_axes(Shader sh);

#endif
