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
private:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Cube();
	void draw(Shader sh, glm::mat4 model);
};

class Cuboid :Shape
{
private:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Cuboid();
	void draw(Shader sh, glm::mat4 model);
};

class Goal :Shape
{
private:
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
private:
	static unsigned int tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Slope();
	void draw(Shader sh, glm::mat4 model);
};

class Circle :Shape
{
private:
	static unsigned int tri_VAO, tri_VBO;
public:
	Circle();
	void draw(Shader sh, glm::mat4 model);
};

class Cylinder :Shape
{
private:
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

class Corn :Shape
{
private:
	static unsigned int tri_VAO, tri_VBO;
	Circle circle;
public:
	Corn();
	void draw(Shader sh, glm::mat4 model);
};
 
class Sphere :Shape
{
private:
	static unsigned int tri_VAO, tri_VBO;
public:
	Sphere();
	void draw(Shader sh, glm::mat4 model);
};

class Character :Shape
{
private:
	static unsigned int tri_VAO, tri_VBO;
	Corn corn;
	Cylinder cylinder;
	Sphere sphere;
public:
	Character();
	void draw(Shader sh, glm::mat4 model);
};

bool MakeCircleVertex();
void prepare_axes();
void draw_axes(Shader sh);

#endif
