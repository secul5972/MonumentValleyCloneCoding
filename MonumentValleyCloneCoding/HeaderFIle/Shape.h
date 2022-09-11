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

class Shape
{
protected:
	//fixed variable
	GLuint		type_;
	bool		can_be_located_;
	bool		isfixed_;

	//changed per render
	bool		isdirty_ = false;
	float		*base_side_vertex_ = 0;
	float		*curr_side_vertex_ = 0;

	enum ShapeType {
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

	static const string ShapeTypeName[];
public:
	Shape(GLuint type = 0, bool can_be_located = false, bool isfixed = true) {};
	void SetCanBeLocated(bool can_be_located);
	void SetIsFixed(bool isfixed);
	void SetIsDirty(bool isdirty);
	virtual void Draw(glm::mat4 model);
	virtual void MakeBuffer();
	virtual void MakeSideVertex();
	virtual void FreeVertex();
};

class Axes :public Shape
{
private:
	static GLuint line_VAO, line_VBO;
public:
	Axes();
	void Draw(glm::mat4 model);
};

class Cube :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Cube();
	void Draw(glm::mat4 model);
	void MakeBuffer();
};

class Goal :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Goal();
	void Draw(glm::mat4 model);
	void MakeBuffer();
	void FreeVertex();
};

class L_shape :public Shape
{
private:
	Cube cube;
public:
	L_shape();
	void MakeSideVertex();
	void Draw(glm::mat4 model);
};

class Slope :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO, line_VAO, line_VBO;
public:
	Slope();
	void Draw(glm::mat4 model);
	void MakeBuffer();
	void FreeVertex();
};

class Circle :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO;
public:
	Circle();
	void Draw(glm::mat4 model);
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
	void Draw(glm::mat4 model);
	void MakeBuffer();
};

class Rotary_Knob :public Shape
{
private:
	Cylinder cylinder;
	Cube cube;
public:
	Rotary_Knob();
	void Draw(glm::mat4 model);
};

class Corn :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO;
	Circle circle;
public:
	Corn();
	void Draw(glm::mat4 model);
	void MakeBuffer();
};
 
class Sphere :public Shape
{
private:
	static GLuint tri_VAO, tri_VBO;
public:
	Sphere();
	void Draw(glm::mat4 model);
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
	void Draw(glm::mat4 model);
};

#endif
