#ifndef SHAPE_H
#define SHAPE_H

#include "Shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>

#include <iostream>
using namespace std;

extern glm::mat4 projection, view;
extern float cube_tri_ver[];
extern float cube_side_ver[];
extern Shader* def_shader;

enum ShapeType
{
	NONE,
	AXES,
	CUBE,
	GOAL,
	L_SHAPE,
	SLOPE,
	CIRCLE,
	CYLINDER,
	RORTARY_KNOB,
	CORN,
	SPHERE,
	CHARACTER
};

class Shape
{
protected:
	GLuint type_;
	bool can_be_located_;
	float* side_vertex = 0;
public:
	Shape(GLuint type = 0, bool can_be_located = false) : type_(type), can_be_located_(can_be_located) {};
	virtual void draw(glm::mat4 model) {};
};

class Axes :public Shape
{
private:
	static GLuint line_VAO, line_VBO;
public:
	Axes();
	void draw(glm::mat4 model);
};

class Cube :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Cube();
	void draw(glm::mat4 model);
	void MakeBuffer();
};

class Goal :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Goal();
	void draw(glm::mat4 model);
	void MakeBuffer();
	void FreeVertex();
};

class L_shape :public Shape
{
private:
	Cube cube;
public:
	L_shape();
	void draw(glm::mat4 model);
};

class Slope :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Slope();
	void draw(glm::mat4 model);
	void MakeBuffer();
	void FreeVertex();
};

class Circle :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO;
public:
	Circle();
	void draw(glm::mat4 model);
	void MakeBuffer();
	void FreeVertex();
};

class Cylinder :public Shape
{
private:
	static GLuint line_VAO, line_VBO;
	Circle circle;
public:
	Cylinder();
	void draw(glm::mat4 model);
	void MakeBuffer();
	//void FreeVertex();
};

class Rotary_Knob :public Shape
{
private:
	Cylinder cylinder;
	Cube cube;
public:
	Rotary_Knob();
	void draw(glm::mat4 model);
};

class Corn :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO;
	Circle circle;
public:
	Corn();
	void draw(glm::mat4 model);
	void MakeBuffer();
};
 
class Sphere :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO;
public:
	Sphere();
	void draw(glm::mat4 model);
	void MakeBuffer();
	void FreeVertex();
};

class Character :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO;
	Corn corn;
	Cylinder cylinder;
	Sphere sphere;
public:
	Character();
	void draw(glm::mat4 model);
};

#endif
