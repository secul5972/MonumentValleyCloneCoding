#ifndef SHAPE_H
#define SHAPE_H

//vec3.xy();
#define GLM_FORCE_SWIZZLE

#include "Shader.h"
#include "Face.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>

#include <iostream>
using namespace std;

extern glm::mat4 projection, view;
extern float cube_tri_ver[];
extern float cube_face_ver[];
extern Shader* def_shader;

class Shape
{
protected:
	//fixed variable
	GLuint		type_;
	bool		can_be_located_;
	bool		isfixed_;

	//can be changed per render
	bool		isdirty_ = false;
	float		*base_face_vertex_ = 0;
	float		*curr_face_vertex_ = 0;

	enum ShapeType {
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

	enum FaceType {
		NONE,
		BACK,
		BOTTOM,
		RIGHT,
		FRONT,
		UP,
		LEFT
	};

	static const int kFaceTypeCnt = 7;

	static const string kShapeTypeName[];
	//face normal vector
	static const glm::vec3 kFaceAxes[];
	//remove vec3 factor
	static const glm::vec3 kFaceFactor[];
public:
	Shape(GLuint type = 0, bool can_be_located = false, bool isfixed = true) {};

	void SetCanBeLocated(bool can_be_located);
	void SetIsFixed(bool isfixed);
	void SetIsDirty(bool isdirty);
	bool GetCanBeLocated();
	bool GetIsFixed();
	bool GetIsDirty();

	virtual void Draw(glm::mat4 model);
	virtual void MakeBuffer();
	virtual void MakeFaceVertex();
	virtual void FreeVertex();
	virtual float* IsOnShape(glm::vec3);
	bool IsOnFace(glm::vec3 point, float* face, GLuint face_vertex_cnt);
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
	float* IsOnShape(glm::vec3);
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
	void MakeFaceVertex();
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
