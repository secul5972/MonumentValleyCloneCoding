#ifndef LEVEL_H
#define LEVEL_H

#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shape.h"
#include "ClickArea.h"

extern GLFWwindow* window;
extern bool left_mouse_button_down;
extern glm::vec2 prev_mouse_pos;
extern float deltaTime;


class Level
{
public:
	virtual void draw() = 0;
};

class Level1
{
private:
	L_shape		l_shape;
	Cuboid		cuboid;
	Slope		slope;
	Goal		goal;
	Circle		circle;
	Rotary_Knob	rotary_knob;
	Character	character;
public:
	Level1();
	void draw(glm::mat4 worldModel);
	~Level1();
};

#endif