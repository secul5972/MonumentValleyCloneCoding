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
public:
	virtual void Draw() = 0;
};

class Level1
{
private:
	int			shape_cnt;
	int			single_shape_cnt;
	int			edge_size;
	Shape*		shapes[8];
	glm::vec3	aligned_pos;
	glm::vec3	character_pos;
	bool		character_move_flag = false;

	//data for character moving
	float*		start_face = 0;
	int			start_shape_idx = -1;
	int			start_edge_idx = -1;
	int			start_face_direc = 0;
	int			start_face_cnt = 0;
	int			start_face_ver_cnt = 0;
	float*		end_face = 0;
	int			end_shape_idx = -1;
	int			end_edge_idx = -1;
	int			end_face_direc = 0;
public:
	bool**		edge;

	Level1();
	void Draw(glm::mat4 worldModel);
	void FindFace(double xpos, double ypos);
	~Level1();

	static void				mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void				mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void					PrintFace(float*, int);

	glm::vec3				AlignPos(float* face, int direction, glm::vec2 point, int ver_cnt);
	std::vector<int>		FindPath(int start, int end, int size, bool** edge);
	std::vector<glm::vec3>	PathIdxToCoord(glm::vec3 start, vector<int> path_idx);
	glm::vec3 FindCoord(float** curr_face, int next, glm::vec3 start, int* curr_direc_ptr, int* curr_face_cnt_ptr, int* curr_face_ver_cnt_ptr, vector<glm::vec3>* path_coord);
	std::vector<glm::vec3> FindOverlappingLine(int curr_face_cnt, float* curr_face, int next_face_cnt, float* next_face);
};

#endif