#ifndef SHAPE_H
#define SHAPE_H

//vec3.xy();
#define GLM_FORCE_SWIZZLE

#include "Shader.h"
#include "Face.h"
#include "Movement.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>

#include <iostream>
using namespace std;

extern glm::mat4	viewport, projection, view;
extern glm::mat4	vpvp_mat;
extern float		cube_tri_ver[];
extern float		cube_line_ver[];
extern float		cube_face_ver[];
extern float		cube_normal_vec[];
extern int			cube_tri_ver_cnt;
extern int			cube_line_ver_cnt;
extern Shader*		def_shader;

class Shape
{
protected:

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
		CHARACTER
	};

	static const	string kShapeTypeName[];

	//const로 고칠 필요가 있다.
	//shape Type
	ShapeType		type_;
	//player can be located on shape
	bool			can_be_located_;
	//this shape do not rotate
	bool			isfixed_;


	//
	bool			issaved_ = false;
	//need to update face vertex position
	bool			isdirty_ = true;
	//current face vertex position
	float*			curr_face_vertex_ = 0;
	//current model matrix
	glm::mat4		model_;

	float*			curr_normal_vec_ = 0;
	const int		normal_vec_size_ = 18;

public:
	Shape();
	Shape(ShapeType, bool, bool);

	void				SetCanBeLocated(bool can_be_located);
	void				SetIsFixed(bool isfixed);
	void				SetIsDirty(bool isdirty);
	bool				GetCanBeLocated();
	int					GetShapeType();
	bool				GetIsFixed();
	bool				GetIsDirty();
	

	virtual void		Draw(glm::mat4);
	virtual void		MakeBuffer();
	virtual void		MakeFaceVertex();
	virtual void		DelFaceVertex();
	virtual float*		InShape(glm::vec2, int*, int*);
	virtual void		SaveModelData(glm::mat4);
	virtual int			GetFaceVerCnt();
	virtual int			GetFaceCnt();
	virtual int			WGetFaceDirFlag(int);
	float*				GetCurrFaceVer();
	float*				GetCurrFaceVer(int);
	virtual glm::vec3	GetNormalVec(int);
};

class Axes :public Shape
{
private:
	static GLuint line_VAO, line_VBO;
public:
	Axes();
	void Draw(glm::mat4);
};

class Cube :public Shape, public Face, public Movement
{
private:
	static GLuint		tri_VAO, tri_VBO, line_VAO, line_VBO;
	static float*		base_face_vertex_;
	static float*		base_normal_vec_;
	static const int	face_ver_size_ = 72;
	static const int	face_cnt_ = 6;
	static const int	face_ver_cnt_ = 4;
public:
	Cube();
	~Cube();
	void		Draw(glm::mat4);
	void		MakeBuffer();
	float*		InShape(glm::vec2, int*, int*);
	void		SaveModelData(glm::mat4);
	int			GetFaceVerCnt();
	int			GetFaceCnt();
	void		MakeFaceDirFlag();
	int			WGetFaceDirFlag(int);
	glm::vec3	GetNormalVec(int);
};

class Cuboid :public Shape, public Face, public Movement
{
private:
	static GLuint		tri_VAO, tri_VBO, line_VAO, line_VBO;
	static float*		base_face_vertex_;
	static float*		base_normal_vec_;
	static const int	face_ver_size_ = 72;
	static const int	face_cnt_ = 6;
	static const int	face_ver_cnt_ = 4;
	static glm::mat4	pre_model_;
public:
	Cuboid();
	~Cuboid();
	void		Draw(glm::mat4);
	void		MakeBuffer();
	float*		InShape(glm::vec2, int*, int*);
	void		SaveModelData(glm::mat4);
	int			GetFaceVerCnt();
	int			GetFaceCnt();
	void		MakeFaceDirFlag();
	int			WGetFaceDirFlag(int);
	glm::vec3	GetNormalVec(int);
};

class Goal :public Shape, public Face, public Movement
{
private:
	static GLuint		tri_VAO, tri_VBO, line_VAO, line_VBO;
	static float*		base_face_vertex_;
	static float*		base_normal_vec_;
	static const int	face_ver_size_ = 72;
	static const int	face_cnt_ = 6;
	static const int	face_ver_cnt_ = 4;
	static glm::mat4	pre_model_;
public:
	Goal();
	~Goal();
	void		Draw(glm::mat4 model);
	void		MakeBuffer();
	float*		InShape(glm::vec2, int*, int *);
	void		SaveModelData(glm::mat4);
	int			GetFaceVerCnt();
	int			GetFaceCnt();
	void		MakeFaceDirFlag();
	int			WGetFaceDirFlag(int);
	glm::vec3	GetNormalVec(int);
};

class L_shape :public Shape, public Face, public Movement
{
private:
	Cube				cube;
	static float*		base_face_vertex_;
	static const int	face_ver_size_ = 168;
	static const int	face_cnt_ = 14;
	static const int	face_shape_cnt_[3];
	static const int	face_ver_cnt_ = 4;
public:
	L_shape();
	~L_shape();
	void		MakeFaceVertex();
	void		DelFaceVertex();
	void		Draw(glm::mat4 model);
	//float*		InShape(glm::vec2, int*, int*);
	void		SaveModelData(glm::mat4);
	int			GetFaceVerCnt();
	int			GetFaceCnt();
	void		MakeFaceDirFlag();
	int			WGetFaceDirFlag(int);
	float*		GetCurrFaceVer(int);
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

class Line :public Shape
{
private:
	static GLuint line_VAO, line_VBO;
public:
	Line();
	void Draw(glm::mat4);
	void SetLine(glm::vec3, glm::vec3);
};

#endif
