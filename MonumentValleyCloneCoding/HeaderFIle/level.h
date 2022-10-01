#ifndef LEVEL_H
#define LEVEL_H

#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shape.h"
#include "ClickArea.h"

extern GLFWwindow* window;
extern bool left_mouse_button_down;
extern glm::vec2 prev_mouse_pos;
extern float deltaTime;

class Level
{
private:
	Shape**				shapes_;
	int					shape_cnt_;
	int					moving_shape_cnt_;
	
	//data for character moving
	glm::vec3			vp_aligned_pos;
	glm::vec3			wd_char_pos;
	bool				char_move_flag = false;
	vector<glm::vec3>	path_coord;
	bool				path_coord_idx = 0;

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
public:
	bool**		edge;

	Level(int shape_cnt);
	~Level();
	void					Draw(glm::mat4 worldModel);
	void					FindPathCoord(double xpos, double ypos);

	static void				mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void				mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void					PrintFace(float*, int);

	glm::vec3				AlignPos(float* face, int direction, glm::vec2 point, int ver_cnt);
	std::vector<int>		FindPath(int start, int end, int size, bool** edge);
	bool					PathIdxToCoord(glm::vec3 start, glm::vec3 vp_end, vector<int> path_idx);
	void					FindCoord(float** curr_face, int next, glm::vec3 start, int* curr_direc_ptr, int* curr_face_cnt_ptr, int* curr_face_ver_cnt_ptr);
	std::vector<glm::vec3>	FindOverlappingLine(int curr_face_cnt, float* curr_face, int next_face_cnt, float* next_face);
	glm::vec3				FindCenterPos(float* points, int ver_cnt);
};

#endif