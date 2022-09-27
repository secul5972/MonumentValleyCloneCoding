#include "../headerFile/Level.h"

double rotateStartTime = 0;
double rotateEndTime = -1;
double rotateCurrTime = 0;
double l_shape_angle = 0;

EllipseArea* ellipse_area;
glm::mat4 ellipse_area_model;
bool l_shape_moving_flag = false;
glm::vec2 prev_mouse_pos_in_model;
extern Level1* level1;

extern float line_vertices[2][3];

Level1::Level1(): aligned_pos(glm::vec3(0.0f, 0.0f, 0.0f)), character_pos(glm::vec3(0.0f, -0.3f, 1.2f))
{
	shape_cnt = 8;

	ellipse_area = new EllipseArea;
	prev_mouse_pos_in_model.x = -1;
	prev_mouse_pos_in_model.y = -1;

	shapes[0] = new L_shape();
	shapes[0]->SetCanBeLocated(true);

	shapes[1] = new L_shape();
	shapes[1]->SetCanBeLocated(true);

	shapes[2] = new Character();

	shapes[3] = new Rotary_Knob();

	shapes[4] = new L_shape();
	shapes[4]->SetCanBeLocated(true);
	shapes[4]->SetIsFixed(false);

	shapes[5] = new Cuboid();
	shapes[5]->SetCanBeLocated(true);

	shapes[6] = new Slope();
	shapes[6]->SetCanBeLocated(true);

	shapes[7] = new Goal();
	shapes[7]->SetCanBeLocated(true);

	edge = new bool*[shape_cnt];
	for (int i = 0; i < shape_cnt; i++)
	{
		edge[i] = new bool[shape_cnt];
		memset(edge[i], 0, sizeof(bool) * shape_cnt);
	}

	edge[0][1] = 1;
	edge[1][0] = 1;
	edge[1][4] = 1;
	edge[4][1] = 1;
	edge[4][5] = 1;
	edge[5][4] = 1;
	edge[5][6] = 1;
	edge[6][5] = 1;
	edge[6][7] = 1;
	edge[7][6] = 1;
}

void Level1::Draw(glm::mat4 worldModel)
{
	glm::mat4 model;

	// l_shape
	model = worldModel;
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes[0]->SaveModelData(model);
	shapes[0]->Draw(model);

	model = worldModel;
	model = glm::translate(model, glm::vec3(1.8f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes[1]->SaveModelData(model);
	shapes[1]->Draw(model);

	// character
	if (character_move_flag)
	{
		character_pos += deltaTime * (aligned_pos - character_pos);
	}

	model = worldModel;
	model = glm::translate(model, character_pos - glm::vec3(0.0f, -0.4f, 1.2f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	shapes[2]->Draw(model);

	float tmp_angle = (float)fmod(l_shape_angle, 90);
	if (!l_shape_moving_flag)
	{
		if (tmp_angle < 0.5)
			l_shape_angle = int(l_shape_angle / 90) * 90;
		else if (tmp_angle > 90 - 0.5)
			l_shape_angle = (int(l_shape_angle / 90) + 1) % 4 * 90;
		else if (tmp_angle > 45.0f)
			l_shape_angle += deltaTime * 60;
		else
			l_shape_angle -= deltaTime * 60;
	}

	if (l_shape_angle == 270)
	{
		edge[1][4] = 0;
		edge[4][1] = 0;
		edge[0][4] = 1;
		edge[4][0] = 1;
	}
	else if (l_shape_angle == 0)
	{
		edge[1][4] = 1;
		edge[4][1] = 1;
		edge[0][4] = 0;
		edge[4][0] = 0;
	}
	else if (l_shape_angle == 90 || l_shape_angle == 180)
	{
		edge[1][4] = 0;
		edge[4][1] = 0;
		edge[0][4] = 0;
		edge[4][0] = 0;
	}

	// rotary_knob
	model = worldModel;
	glm::mat4 model2 = worldModel;
	model2 = glm::translate(model2, glm::vec3(1.9f, 1.8f, 0.0f));
	model2 = glm::rotate(model2, glm::radians(float(l_shape_angle)), glm::vec3(1.0f, 0.0f, 0.0f));
	shapes[3]->Draw(model2);

	model = worldModel;
	model = glm::translate(model, glm::vec3(2.15f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 3.0f, 3.0f));
	ellipse_area_model = model;

	if (225 < l_shape_angle && l_shape_angle < 315)
		worldModel = glm::translate(worldModel, glm::vec3(-1.8f, -1.8f, -1.8f));

	// l_shape
	model = worldModel;
	model = glm::translate(model, glm::vec3(1.8f, 1.8f, 0.0f));
	model = glm::rotate(model, glm::radians(float(-90 + l_shape_angle)), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes[4]->SaveModelData(model);
	shapes[4]->Draw(model);

	// cuboid
	model = worldModel;
	model = glm::translate(model, glm::vec3(0.4f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.25f, 1.0f, 1.0f));
	shapes[5]->SaveModelData(model);
	shapes[5]->Draw(model);

	// slope
	model = worldModel;
	model = glm::translate(model, glm::vec3(0.0f, 2.0f, -0.2f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes[6]->Draw(model);

	// goal
	model = worldModel;
	model = glm::translate(model, glm::vec3(0.0f, 2.3f, -1.1f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes[7]->SaveModelData(model);
	shapes[7]->Draw(model);
}

void Level1::FindFace(double xpos, double ypos)
{
	int			size = sizeof(shapes) / sizeof(Shape*);
	glm::vec2	point(xpos, ypos);
	float		start_depth = 1;
	float		end_depth = 1;
	glm::vec3	viewport_char_pos = viewport * projection * view * glm::vec4(character_pos, 1.0f);

	// find face clicked
	for (int i = 0; i < size; i++)
	{
		float*	curr_start_face;
		float	curr_start_depth;
		int		curr_start_direc;
		float*	curr_end_face;
		float	curr_end_depth;
		int		curr_end_direc;

		if (shapes[i]->GetCanBeLocated() == false) continue;
		if ((curr_start_face = shapes[i]->InShape(viewport_char_pos, &curr_start_direc)))
		{
			curr_start_depth = AverDepth(curr_start_face, shapes[i]->GetFaceVerCnt());
			if (curr_start_depth > start_depth) continue;
			start_face = curr_start_face;
			start_depth = curr_start_depth;
			start_shape_idx = i;
			start_face_direc = curr_start_direc;
		}

		if ((curr_end_face = shapes[i]->InShape(point, &curr_end_direc)))
		{
			curr_end_depth = AverDepth(curr_end_face, shapes[i]->GetFaceVerCnt());
			if (curr_end_depth > end_depth) continue;
			end_face = curr_end_face;
			end_depth = curr_end_depth;
			end_shape_idx = i;
			end_face_direction = curr_end_direc;
		}
	}

	if (start_shape_idx == -1 || end_shape_idx == -1) return;

	printf("type: %d\n", (int)shapes[start_shape_idx]->GetShapeType());
	printf("direction: %d\n", start_face_direc);

	aligned_pos = AlignPos(start_face, start_face_direc, point, shapes[start_shape_idx]->GetFaceVerCnt());

	vector<glm::vec3> path = PathIdxToCoord(viewport_char_pos, aligned_pos, FindPath(start_shape_idx, end_shape_idx, shape_cnt, Level1::edge));

	printf("aligned_pos: %f %f\n", aligned_pos.x, aligned_pos.y);
	PrintFace(start_face, shapes[start_shape_idx]->GetFaceVerCnt());

	aligned_pos = glm::vec3(glm::inverse(viewport) * glm::vec4(aligned_pos, 1.0f));
	glm::vec3 tmp = projection * view * glm::vec4(character_pos, 1.0f);
	
	character_move_flag = true;

	//for debug
	line_vertices[0][0] = aligned_pos.x;
	line_vertices[0][1] = aligned_pos.y;
	line_vertices[0][2] = aligned_pos.z;
	line_vertices[1][0] = tmp.x;
	line_vertices[1][1] = tmp.y;
	line_vertices[1][2] = tmp.z;

	aligned_pos = glm::vec3(glm::inverse(projection * view) * glm::vec4(aligned_pos, 1.0f));
}

Level1::~Level1()
{
	if (ellipse_area)
		delete ellipse_area;
}

void Level1::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		left_mouse_button_down = true;
		glfwGetCursorPos(window, &xpos, &ypos);
		printf("\nmousepos: %f %f\n", xpos, SCR_HEIGHT - ypos);
		level1->FindFace((float)xpos, (float)(SCR_HEIGHT - ypos));
		
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		left_mouse_button_down = false;
		l_shape_moving_flag = false;
		prev_mouse_pos_in_model.x = -1;
		prev_mouse_pos_in_model.y = -1;
	}
}

void Level1::mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (left_mouse_button_down)
	{
		//rotate angle of rotary knob
		l_shape_angle += ellipse_area->CheckClickAndRotateInArea((float)xpos, (float)(SCR_HEIGHT - ypos), ellipse_area_model);
		l_shape_angle = fmod(l_shape_angle + 360, (double)360);
	}
}

void Level1::PrintFace(float* face, int ver_cnt)
{
	for (int i = 0; i < ver_cnt; i++)
	{
		printf("point%d: (%f, %f, %f)\n",i , face[i * 3], face[i * 3 + 1], face[i * 3 + 2]);
	}
}

glm::vec3 Level1::AlignPos(float* face, int direction, glm::vec2 point, int face_ver_cnt)
{
	glm::vec2 direc, ortho;

	if (direction == 0)
		return glm::vec3(point, 0.0f);

	direc = glm::vec2(face[3] - face[0], face[4] - face[1]);
	ortho = glm::vec2(face[6] - face[3], face[7] - face[4]);

	if (direction == 2)
		std::swap(direc, ortho);

	glm::vec2 center(0.0f, 0.0f);

	for (int i = 0; i < face_ver_cnt; i++)
	{
		center.x += face[i * 3];
		center.y += face[i * 3 + 1];
	}
	center.x /= face_ver_cnt;
	center.y /= face_ver_cnt;

	glm::vec3 aligned_pos(0.0f, 0.0f, 0.0f);

	//find x, y using Linear Equation
	if (direc.x == 0)
	{
		aligned_pos.x = center.x;
		if (ortho.y == 0)
			aligned_pos.y = point.y;
		else
			aligned_pos.y = LinearEquation(ortho, point, 1, aligned_pos.x);
	}
	else if (direc.y == 0)
	{
		aligned_pos.y = center.y;
		if (ortho.x == 0)
			aligned_pos.x = point.x;
		else
			aligned_pos.x = LinearEquation(ortho, point, 0, aligned_pos.y);
	}
	else
	{
		aligned_pos.x = (direc.x * ortho.x * (point.y - center.y) + (direc.y * ortho.x * center.x - ortho.y * direc.x * point.x))
			/ (direc.y * ortho.x - ortho.y * direc.x);
		if (ortho.x == 0)
		{
			aligned_pos.x = point.x;
			aligned_pos.y = LinearEquation(direc, center, 1, aligned_pos.x);
		}
		else if (ortho.y == 0)
		{
			aligned_pos.y = point.y;
			aligned_pos.x = LinearEquation(direc, center, 0, aligned_pos.y);
		}
		else
		{
			aligned_pos.x = (direc.x * ortho.x * (point.y - center.y) + (direc.y * ortho.x * center.x - ortho.y * direc.x * point.x))
				/ (direc.y * ortho.x - ortho.y * direc.x);
			aligned_pos.y = LinearEquation(ortho, point, 1, aligned_pos.x);
		}
	}

	//find z from x, y using equation of a plane
	glm::vec3 normal = glm::cross(glm::vec3(face[3] - face[0], face[4] - face[1], face[5] - face[2]), glm::vec3(face[6] - face[0], face[7] - face[1], face[8] - face[2]));
	aligned_pos.z = -(normal.x * (aligned_pos.x - face[0]) + normal.y * (aligned_pos.y - face[1])) / normal.z + face[2];

	return aligned_pos;
}

// bfs
std::vector<int> Level1::FindPath(int start, int end, int size, bool** edge)
{
	std::queue<int>	qu;
	int				visited[20];
	int				curr;

	std::fill(visited, visited + size, -1);

	visited[start] = 0;

	qu.push(start);
	while (!qu.empty())
	{
		curr = qu.front();
		qu.pop();

		for (int i = 0; i < size; i++)
		{
			if (visited[i] != -1)continue;
			if (edge[curr][i] == 0)continue;
			visited[i] = curr;
			if (i == end) break;
			qu.push(i);
		}
	}

	std::vector<int> ret;

	curr = end;
	while (curr != start)
	{
		ret.push_back(curr);
		curr = visited[curr];
	}
	ret.push_back(curr);
	return ret;
}

std::vector<glm::vec3>	Level1::PathIdxToCoord(glm::vec3 start, glm::vec3 end, vector<int> path_idx)
{
	vector<glm::vec3> path_coord;
	int size = (int)path_idx.size();

	path_coord.push_back(start);

	// error
	if (size == 0) return path_coord;

	// start shape == end shape
	if (size == 1)
	{
	
	}

	for (int i = 1; i < size; i++)
	{

	}
	
	return path_coord;
}