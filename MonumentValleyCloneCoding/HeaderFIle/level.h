#ifndef LEVEL_H
#define LEVEL_H

#define GLM_FORCE_SWIZZLE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <algorithm>
#include <queue>

#include "Shader.h"
#include "Shape.h"
#include "Math.h"
#include "ClickArea.h"
#include "ActerCanGoObject.h"
#include "Ornament.h"

extern GLFWwindow* window;
extern bool left_mouse_button_down;
extern glm::vec2 prev_mouse_pos;
extern float delta_time;

class Level
{
private:
	ActerCanGoObject**	acg_object_;
	Ornament**			ornaments_;
	Acter*				acter_;
	int					acg_cnt_;
	int					orna_cnt_;

	//world model matrix
	glm::mat4			world_model_;

	//data for acter moving
	glm::vec3			vp_aligned_pos;
	glm::vec3			wd_acter_pos;
	glm::vec3			init_acter_direc_vec;
	
	int					obj_on_acter = -1;
	bool				acter_move_flag = false;
	vector<glm::vec3>	path_coord;
	int					path_coord_idx = 0;

	float*				start_face = 0;
	int					start_face_direc = 0;
	glm::vec3			start_normal_vec;
	int					start_face_cnt = 0;
	int					start_face_ver_cnt = 0;

	float*				end_face = 0;
	int					end_face_direc = 0;
	glm::vec3			end_normal_vec;

	glm::vec3			dist_vec;
	glm::vec3			wd_aligned_pos;
	Line				line;

	bool				opt_obj_move_flag = false;
public:
	vector<int>			obj_can_rotate;
	vector<int>			obj_opt_mov;
	bool**				edge;

	Level(int acg_cnt, int actg_cnt, glm::mat4 world_model);
	~Level();
	void					Draw();
	void					FindPathCoord(double xpos, double ypos);

	static void				mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void				mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void					PrintFace(float*, int);

	glm::vec3				AlignPos(float* face, int direction, glm::vec2 point, int ver_cnt);
	std::vector<int>		FindPath(int start, int end, int size, bool** edge);
	bool					PathIdxToCoord(glm::vec3 start, glm::vec3 vp_end, vector<int> path_idx);
	bool					FindCoord(float** curr_face, int next, glm::vec3 start, int* curr_direc_ptr, int* curr_face_cnt_ptr, int* curr_face_ver_cnt_ptr);
	std::vector<glm::vec3>	FindOverlappingLine(int curr_face_cnt, float* curr_face, int next_face_cnt, float* next_face);
	void					ChkDisableFace();
	void					CmpTwoObj(int fobj_idx, int sobj_idx);
	bool					ChkActorOnObj(vector<int> obj_idx);
};

#endif