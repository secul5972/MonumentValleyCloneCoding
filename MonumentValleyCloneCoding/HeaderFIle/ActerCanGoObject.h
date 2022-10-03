#ifndef ACTERCANGOOBJECT_H
#define ACTERCANGOOBJECT_H

#include "Shape.h"
#include "Rotatable.h"
#include "CanBeLocated.h"
#include "MoveDrc.h"
#include "Shader.h"

extern float		cube_tri_ver[];
extern float		cube_line_ver[];
extern float		cube_face_ver[];
extern float		cube_normal_vec[];
extern const int	cube_tri_ver_cnt;
extern const int	cube_line_ver_cnt;
extern Shader*		def_shader;

class ActerCanGoObject :public Shape, public Rotatable, public CanBeLocated
{ 
protected:
	//this shape do not rotate
	bool			isfixed_ = true;
	bool			issaved_ = false;
	bool*			disable_face_ = 0;
public:
	ActerCanGoObject(ShapeType shape_type, bool can_be_located_);
	~ActerCanGoObject();
	virtual int			GetFaceVerCnt() = 0;
	virtual int			GetFaceCnt() = 0;
	virtual int			WGetFaceDrcFlag(int) = 0;	

	void				SetIsFixed(bool isfixed);
	void				SetDisableFace(int idx, bool val);
	bool				GetDisableFace(int idx);
};

class Cube :public ActerCanGoObject, public MoveDrc
{
private:
	static GLuint		tri_VAO_, tri_VBO_, line_VAO_, line_VBO_;
	static float*		base_face_vertex_;
	static float*		base_normal_vec_;
	static const int	kFaceVerSize = 72;
	static const int	kFaceCnt = 6;
	static const int	kFaceVerCnt = 4;
public:
	Cube();
	~Cube();

	static void			MakeBuffer();

	// virtual
	void				Draw(glm::mat4);
	float*				InObj(glm::vec2, int*, int*);
	void				SaveModelData(glm::mat4);
	void				MakeFaceDrcFlag();
	int					GetFaceVerCnt();
	int					GetFaceCnt();

	//wrapper
	int					WGetFaceDrcFlag(int);
};

class Cuboid :public ActerCanGoObject, public MoveDrc
{
private:
	static GLuint		tri_VAO_, tri_VBO_, line_VAO_, line_VBO_;
	static float*		base_face_vertex_;
	static float*		base_normal_vec_;
	static const int	kFaceVerSize = 72;
	static const int	kFaceCnt = 6;
	static const int	kFaceVerCnt = 4;
	static glm::mat4	pre_model_;
public:
	Cuboid();
	~Cuboid();

	static void			MakeBuffer();

	// virtual
	void				Draw(glm::mat4);
	float*				InObj(glm::vec2, int*, int*);
	void				SaveModelData(glm::mat4);
	void				MakeFaceDrcFlag();
	int					GetFaceVerCnt();
	int					GetFaceCnt();

	// wrapper
	int					WGetFaceDrcFlag(int);
};

class Goal :public ActerCanGoObject, public MoveDrc
{
private:
	static GLuint		tri_VAO_, tri_VBO_, line_VAO_, line_VBO_;
	static float*		base_face_vertex_;
	static float*		base_normal_vec_;
	static const int	kFaceVerSize = 72;
	static const int	kFaceCnt = 6;
	static const int	kFaceVerCnt = 4;
	static glm::mat4	pre_model_;
public:
	Goal();
	~Goal();

	static void			MakeBuffer();

	// virtual
	void				Draw(glm::mat4 model);
	float*				InObj(glm::vec2, int*, int*);
	void				SaveModelData(glm::mat4);
	void				MakeFaceDrcFlag();
	int					GetFaceVerCnt();
	int					GetFaceCnt();

	// wrapper
	int					WGetFaceDrcFlag(int);
};

#endif
