#ifndef LEVEL_H
#define LEVEL_H

#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shape.h"
#include "TouchBox.h"

extern GLFWwindow* window;

class Level
{
public:
	virtual void draw() = 0;
};

class Level1
{
private:
	L_shape	l_shape[3];
	Cuboid	cuboid;
	Slope	slope;
	Goal	goal;
	Circle	circle;
	Point	point;
public:
	Level1();
	virtual void draw(Shader sh);
	~Level1();
};

#endif