#ifndef ClickArea_H
#define ClickArea_H

#include "Shader.h"
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

extern const GLuint SCR_WIDTH;
extern const GLuint SCR_HEIGHT;

extern bool l_shape_moving_flag;
extern bool left_mouse_button_down;
extern glm::vec2 prev_mouse_pos_in_model;

class ClickArea
{
public:
	virtual bool CheckClickInArea(float xpos, float ypos, glm::mat4 model) = 0;
	virtual float CheckClickAndFindAngle(float xpos, float ypos, glm::mat4 model) = 0;
};

class EllipseArea :ClickArea
{
public:
	EllipseArea();
	bool CheckClickInArea(float xpos, float ypos, glm::mat4 model);
	float CheckClickAndFindAngle(float xpos, float ypos, glm::mat4 model);
};

#endif