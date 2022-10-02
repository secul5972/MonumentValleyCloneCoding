#ifndef ORNAMENT_H
#define ORNAMENT_H

#include "../headerFile/Shape.h"
#include "../headerFile/Rotatable.h"
#include "../headerFile/CanBeLocated.h"
#include "../headerFile/ActerCanGoObject.h"

class Ornament :public Shape
{
private:
public:
	Ornament(ShapeType shape_type, bool can_be_located_);
	~Ornament();
};

class Axes :public Ornament
{
private:
	static GLuint line_VAO_, line_VBO_;
public:
	Axes();
	void Draw(glm::mat4);
};

class Slope :public Ornament
{
private:
	static GLuint		tri_VAO_, tri_VBO_, line_VAO_, line_VBO_;
public:
	Slope();
	void Draw(glm::mat4 model);
	static void	MakeBuffer();
	void FreeVertex();
};


class Circle :public Ornament
{
private:
	static GLuint tri_VAO_, tri_VBO_;
public:
	Circle();
	void Draw(glm::mat4 model);
	static void	MakeBuffer();
	void FreeVertex();
};

class Cylinder :public Ornament
{
private:
	static GLuint line_VAO_, line_VBO_;
	Circle circle;
public:
	Cylinder();
	void Draw(glm::mat4 model);
	static void	MakeBuffer();
};

class Rotary_Knob :public Ornament
{
private:
	Cylinder cylinder;
	Cube cube;
public:
	Rotary_Knob();
	void Draw(glm::mat4 model);
};

class Corn :public Ornament
{
private:
	static GLuint tri_VAO_, tri_VBO_;
	Circle circle;
public:
	Corn();
	void Draw(glm::mat4 model);
	static void	MakeBuffer();
};

class Sphere :public Ornament
{
private:
	static GLuint tri_VAO_, tri_VBO_;
public:
	Sphere();
	void Draw(glm::mat4 model);
	static void	MakeBuffer();
	void FreeVertex();
};

class Acter :public Ornament
{
private:
	static GLuint tri_VAO_, tri_VBO_;
	Corn corn;
	Cylinder cylinder;
	Sphere sphere;
public:
	Acter();
	void Draw(glm::mat4 model);
};

class Line :public Ornament
{
private:
	static GLuint line_VAO_, line_VBO_;
public:
	Line();
	void Draw(glm::mat4);
	void SetLine(glm::vec3, glm::vec3);
};
#endif