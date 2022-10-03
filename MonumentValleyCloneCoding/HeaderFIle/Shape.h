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

extern glm::mat4	viewport, projection, view;
extern glm::mat4	vpvp_mat;

enum ShapeType {
	DEFAULT,
	AXES,
	CUBE,
	CUBOID,
	GOAL,
	L_SHAPE,
	SLOPE,
	CIRCLE,
	CYLINDER,
	RORTARY_KNOB,
	CORN,
	SPHERE,
	ACTER
};

const string kShapeTypeName[] = {
	"DEFAULT",
	"AXES",
	"CUBE",
	"CUBOID",
	"GOAL",
	"L_SHAPE",
	"SLOPE",
	"CIRCLE",
	"CYLINDER",
	"RORTARY_KNOB",
	"CORN",
	"SPHERE",
	"ACTER"
};

class Shape
{
protected:

	//shape Type
	ShapeType		type_;
	//player can be located on shape
	bool			can_be_located_;
public:
	Shape();
	Shape(ShapeType, bool);

	void				SetCanBeLocated(bool can_be_located);
	bool				GetCanBeLocated();
	virtual void		Draw(glm::mat4) = 0;
};

#endif
