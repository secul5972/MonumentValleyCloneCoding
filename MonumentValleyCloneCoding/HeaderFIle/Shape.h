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

extern glm::mat4 viewport, projection, view;
extern float cube_tri_ver[];
extern float cube_face_ver[];
extern Shader* def_shader;

class Shape
{
protected:
	//fixed variable
	enum ShapeType {
		DEFAULT,
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

	ShapeType	type_;
	bool		can_be_located_;
	bool		isfixed_;
	bool		issaved_ = false;

	//can be changed per render
	bool		isdirty_ = true;
	float		*curr_face_vertex_ = 0;

	glm::mat4 model_;

	static const string kShapeTypeName[];

public:
	Shape(ShapeType type = DEFAULT, bool can_be_located = false, bool isfixed = true) : type_(type), can_be_located_(can_be_located), isfixed_(isfixed) {};

	void SetCanBeLocated(bool can_be_located);
	void SetIsFixed(bool isfixed);
	void SetIsDirty(bool isdirty);
	bool GetCanBeLocated();
	int GetShapeType();
	bool GetIsFixed();
	bool GetIsDirty();

	virtual void Draw(glm::mat4);
	virtual void MakeBuffer();
	virtual void MakeFaceVertex();
	virtual void FreeVertex();
	virtual float* InShape(glm::vec2);
	virtual void SaveModelData(glm::mat4);
};

class Axes :public Shape
{
private:
	static GLuint line_VAO, line_VBO;
public:
	Axes();
	void Draw(glm::mat4);
};

class Cube :public Shape, public Face
{
private:

	static GLuint tri_VAO, tri_VBO, line_VAO, line_VBO;
	static float* base_face_vertex_;
public:
	//size of cube_face_ver
	static const GLuint cube_face_ver_size = 72;
	//count of cube face(rectangle) vertex
	static const GLuint cube_face_ver_cnt = 4;
	Cube();
	~Cube();
	void Draw(glm::mat4);
	void MakeBuffer();
	float* InShape(glm::vec2);
	void SaveModelData(glm::mat4);
};

class Goal :public Shape, public Face
{
private:
	static GLuint tri_VAO, tri_VBO, line_VAO, line_VBO;
	static float* base_face_vertex_;
	static glm::mat4 pre_model_;
public:
	Goal();
	~Goal();
	void Draw(glm::mat4 model);
	void MakeBuffer();
	float* InShape(glm::vec2);
	void SaveModelData(glm::mat4);
};

class L_shape :public Shape, public Face
{
private:
	Cube cube;
	static float* base_face_vertex_;
public:
	//size of cube_face_ver
	static const GLuint l_shape_face_ver_size = 168;
	//count of cube face(rectangle) vertex
	static const GLuint l_shape_face_ver_cnt = 4;
	L_shape();
	~L_shape();
	void MakeFaceVertex();
	void Draw(glm::mat4 model);
	float* InShape(glm::vec2);
	void SaveModelData(glm::mat4);
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
