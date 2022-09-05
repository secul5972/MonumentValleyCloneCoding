#ifndef ClickBox_H
#define ClickBox_H

#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shape.h"

#include "AdditionalMathFunction.h"
#include <iostream>
using namespace std;

extern glm::mat4 projection, view, viewport;

extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

extern bool l_shape_moving_flag;

static glm::vec2 prev_mouse_pos_in_model;
static float click_and_rotate_angle;

class ClickBox
{
public:
	virtual bool CheckClickInBox(float xpos, float ypos, glm::mat4 model) = 0;
	virtual float CheckClickAndRotateInBox(float xpos, float ypos, glm::mat4 model) = 0;
};

class CircleBox :ClickBox
{
private:
	float radius;
public:
	CircleBox();
	virtual bool CheckClickInBox(float xpos, float ypos, glm::mat4 model);
	virtual float CheckClickAndRotateInBox(float xpos, float ypos, glm::mat4 model);
};

#endif