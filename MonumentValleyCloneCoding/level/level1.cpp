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
	single_shape_cnt = 3;
	edge_size = 12;

	ellipse_area = new EllipseArea;
	prev_mouse_pos_in_model.x = -1;
	prev_mouse_pos_in_model.y = -1;

	shapes[0] = new Cuboid();
	shapes[0]->SetCanBeLocated(true);

	shapes[1] = new Slope();
	shapes[1]->SetCanBeLocated(true);

	shapes[2] = new Goal();
	shapes[2]->SetCanBeLocated(true);

	shapes[3] = new L_shape();
	shapes[3]->SetCanBeLocated(true);

	shapes[4] = new L_shape();
	shapes[4]->SetCanBeLocated(true);

	shapes[5] = new L_shape();
	shapes[5]->SetCanBeLocated(true);
	shapes[5]->SetIsFixed(false);

	shapes[6] = new Character();

	shapes[7] = new Rotary_Knob();

	edge = new bool*[edge_size];
	for (int i = 0; i < edge_size; i++)
	{
		edge[i] = new bool[edge_size];
		memset(edge[i], 0, sizeof(bool) * edge_size);
	}

	edge[0][1] = 1;
	edge[0][9] = 1;
	edge[1][0] = 1;
	edge[1][2] = 1;
	edge[2][1] = 1;
	edge[3][4] = 1;
	edge[4][3] = 1;
	edge[4][5] = 1;
	edge[5][4] = 1;
	edge[5][6] = 1;
	edge[6][5] = 1;
	edge[6][7] = 1;
	edge[7][6] = 1;
	edge[7][8] = 1;
	edge[8][7] = 1;
	edge[8][11] = 1;
	edge[9][0] = 1;
	edge[9][10] = 1;
	edge[10][9] = 1;
	edge[10][11] = 1;
	edge[11][8] = 1;
	edge[11][10] = 1;
}

void Level1::Draw(glm::mat4 worldModel)
{
	glm::mat4 model;

	// l_shape
	model = worldModel;
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes[3]->SaveModelData(model);
	shapes[3]->Draw(model);

	model = worldModel;
	model = glm::translate(model, glm::vec3(1.8f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes[4]->SaveModelData(model);
	shapes[4]->Draw(model);

	// character
	if (character_move_flag)
	{
		character_pos += deltaTime * (aligned_pos - character_pos);
	}

	model = worldModel;
	model = glm::translate(model, character_pos - glm::vec3(0.0f, -0.4f, 1.2f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	shapes[6]->Draw(model);

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
		edge[8][11] = 0;
		edge[11][8] = 0;
		edge[3][11] = 1;
		edge[11][3] = 1;
	}
	else if (l_shape_angle == 0)
	{
		edge[8][11] = 1;
		edge[11][8] = 1;
		edge[3][11] = 0;
		edge[11][3] = 0;
	}
	else if (l_shape_angle == 90 || l_shape_angle == 180)
	{
		edge[8][11] = 0;
		edge[11][8] = 0;
		edge[3][11] = 0;
		edge[11][3] = 0;
	}

	// rotary_knob
	model = worldModel;
	glm::mat4 model2 = worldModel;
	model2 = glm::translate(model2, glm::vec3(1.9f, 1.8f, 0.0f));
	model2 = glm::rotate(model2, glm::radians(float(l_shape_angle)), glm::vec3(1.0f, 0.0f, 0.0f));
	shapes[7]->Draw(model2);

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
	shapes[5]->SaveModelData(model);
	shapes[5]->Draw(model);

	// cuboid
	model = worldModel;
	model = glm::translate(model, glm::vec3(0.4f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.25f, 1.0f, 1.0f));
	shapes[0]->SaveModelData(model);
	shapes[0]->Draw(model);

	// slope
	model = worldModel;
	model = glm::translate(model, glm::vec3(0.0f, 2.0f, -0.2f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes[1]->Draw(model);

	// goal
	model = worldModel;
	model = glm::translate(model, glm::vec3(0.0f, 2.3f, -1.1f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes[2]->SaveModelData(model);
	shapes[2]->Draw(model);
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
		int		in_shape_idx;

		if (shapes[i]->GetCanBeLocated() == false) continue;
		if ((curr_start_face = shapes[i]->InShape(viewport_char_pos, &curr_start_direc, &in_shape_idx)))
		{
			curr_start_depth = AverDepth(curr_start_face, shapes[i]->GetFaceVerCnt());
			if (curr_start_depth > start_depth) continue;
			start_face = curr_start_face;
			start_depth = curr_start_depth;
			start_shape_idx = i;
			start_face_direc = curr_start_direc;
			start_face_cnt = shapes[i]->GetFaceCnt();
			start_face_ver_cnt = shapes[i]->GetFaceVerCnt();
			if (i >= single_shape_cnt)
				start_edge_idx = single_shape_cnt + (i - single_shape_cnt ? i - single_shape_cnt : 0) * 3 + in_shape_idx;
			else start_edge_idx = i;
		}

		if ((curr_end_face = shapes[i]->InShape(point, &curr_end_direc, &in_shape_idx)))
		{
			curr_end_depth = AverDepth(curr_end_face, shapes[i]->GetFaceVerCnt());
			if (curr_end_depth > end_depth) continue;
			end_face = curr_end_face;
			end_depth = curr_end_depth;
			end_shape_idx = i;
			end_face_direc = curr_end_direc;
			if (i >= single_shape_cnt)
				end_edge_idx = single_shape_cnt + ((i - single_shape_cnt) > 0 ? i - single_shape_cnt : 0) * 3 + in_shape_idx;
			else end_edge_idx = i;
		}
	}

	if (start_shape_idx == -1 || end_shape_idx == -1) return;

	//printf("type: %d\n", (int)shapes[start_shape_idx]->GetShapeType());
	//printf("direction: %d\n", start_face_direc);

	aligned_pos = AlignPos(end_face, end_face_direc, point, shapes[start_shape_idx]->GetFaceVerCnt());

	//vector<glm::vec3> path = PathIdxToCoord(viewport_char_pos, FindPath(start_edge_idx, end_edge_idx, edge_size, Level1::edge));

	//printf("aligned_pos: %f %f %f\n", aligned_pos.x, aligned_pos.y, aligned_pos.z);
	//PrintFace(end_face, shapes[end_shape_idx]->GetFaceVerCnt());

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
	glm::vec3 center(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < face_ver_cnt; i++)
	{
		center.x += face[i * 3];
		center.y += face[i * 3 + 1];
		center.z += face[i * 3 + 2];
	}
	center.x /= face_ver_cnt;
	center.y /= face_ver_cnt;
	center.z /= face_ver_cnt;

	if (direction == 0)
		return center;

	glm::vec2 direc, ortho;

	direc = glm::vec3(face[3] - face[0], face[4] - face[1], face[5] - face[2]);
	ortho = glm::vec3(face[6] - face[3], face[7] - face[4], face[8] - face[5]);

	if (direction == 2)
		std::swap(direc, ortho);

	glm::vec3 aligned_pos(0.0f, 0.0f, 0.0f);

	//find x, y using Linear Equation
	if (abs(direc.x) < 0.000001)
	{
		aligned_pos.x = center.x;
		if (abs(ortho.y) < 0.00001)
			aligned_pos.y = point.y;
		else
			aligned_pos.y = LinearEquation(ortho, point, 1, aligned_pos.x);
	}
	else if (abs(direc.y) < 0.00001)
	{
		aligned_pos.y = center.y;
		if (abs(ortho.x) < 0.00001)
			aligned_pos.x = point.x;
		else
			aligned_pos.x = LinearEquation(ortho, point, 0, aligned_pos.y);
	}
	else
	{
		aligned_pos.x = (direc.x * ortho.x * (point.y - center.y) + (direc.y * ortho.x * center.x - ortho.y * direc.x * point.x))
			/ (direc.y * ortho.x - ortho.y * direc.x);
		if (abs(ortho.x) < 0.00001)
		{
			aligned_pos.x = point.x;
			aligned_pos.y = LinearEquation(direc, center, 1, aligned_pos.x);
		}
		else if (abs(ortho.y) < 0.00001)
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
	aligned_pos.z = PlaneEquation(glm::cross(glm::vec3(face[3] - face[0], face[4] - face[1], face[5] - face[2]), glm::vec3(face[6] - face[0], face[7] - face[1], face[8] - face[2])),
		glm::vec3(face[0], face[1], face[2]), aligned_pos);
	
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

std::vector<glm::vec3>	Level1::PathIdxToCoord(glm::vec3 start, vector<int> path_idx)
{
	vector<glm::vec3> path_coord;
	int	size = (int)path_idx.size();
	int curr_direc = start_face_direc;
	float* curr_face = start_face;
	int curr_face_cnt = start_face_cnt;
	int curr_face_ver_cnt = start_face_ver_cnt;

	path_coord.push_back(start);

	if (size == 1) return path_coord;
	else
	{
		glm::vec3 curr = start;
		for (int i = 0; i < size - 1; i++)
		{
			FindCoord(&curr_face, path_idx[i + 1], curr, &curr_direc, &curr_face_cnt, &curr_face_ver_cnt, &path_coord);
		}
		//마지막 face에서 aligned pos로 이동이 필요
	}

	return path_coord;
}

glm::vec3 Level1::FindCoord(float** curr_face_ptr, int next, glm::vec3 curr_pos, int* curr_direc_ptr, int* curr_face_cnt_ptr, int* curr_face_ver_cnt_ptr, vector<glm::vec3>* path_coord_ptr)
{
	float* curr_face = *curr_face_ptr;
	float* next_face;
	int curr_face_cnt = *curr_face_cnt_ptr;
	int curr_face_ver_cnt = *curr_face_ver_cnt_ptr;
	int next_face_ver_cnt;
	int next_face_cnt;
	int next_shape_idx;


	if (next > single_shape_cnt)
		next_shape_idx = single_shape_cnt + (next - single_shape_cnt) / 3 + 1;
	else
		next_shape_idx = next;

	next_face = shapes[next_shape_idx]->GetCurrFaceVer();
	next_face_ver_cnt = shapes[next_shape_idx]->GetFaceVerCnt();
	next_face_cnt = shapes[next_shape_idx]->GetFaceCnt();

	glm::vec3 curr_normal = glm::normalize(glm::cross(glm::vec3(curr_face[3] - curr_face[0], curr_face[4] - curr_face[1], curr_face[5] - curr_face[2])
		, glm::vec3(curr_face[6] - curr_face[0], curr_face[7] - curr_face[1], curr_face[8] - curr_face[2])));
	glm::vec3 next_normal(0.0f, 0.0f, 0.0f);

	int curr_direc = *curr_direc_ptr;
	int next_direc = 0;
	float vdot;
	for (int i = 0; i < next_face_cnt; i++)
	{
		next_normal = glm::normalize(glm::cross(glm::vec3(next_face[3] - next_face[0], next_face[4] - next_face[1], next_face[5] - next_face[2])
			, glm::vec3(next_face[6] - next_face[0], next_face[7] - next_face[1], next_face[8] - next_face[2])));
		vdot = glm::dot(curr_normal, next_normal);
		if (abs(1.0f - vdot) < 0.000001)
		{
			next_direc = shapes[next_shape_idx]->WGetFaceDirFlag(i);
			break; 
		}
		next_normal += 3 * next_face_ver_cnt;
	}

	glm::vec3 curr_direc_vec;
	glm::vec3 next_direc_vec;

	if (curr_direc == 1)
		curr_direc_vec = glm::vec3(curr_face[3] - curr_face[0], curr_face[4] - curr_face[1], curr_face[5] - curr_face[2]);
	else
		curr_direc_vec = glm::vec3(curr_face[6] - curr_face[3], curr_face[7] - curr_face[4], curr_face[8] - curr_face[5]);

	if (next_direc == 1)
		next_direc_vec = glm::vec3(next_face[3] - next_face[0], next_face[4] - next_face[1], next_face[5] - next_face[2]);
	else
		next_direc_vec = glm::vec3(next_face[6] - next_face[3], next_face[7] - next_face[4], next_face[8] - next_face[5]);




	// curr and next vec
	vdot = glm::dot(glm::vec2(curr_direc_vec.x, curr_direc_vec.y), glm::vec2(next_direc_vec.x, next_direc_vec.y));
	if (abs(1.0f - vdot) < 0.000001 || abs(-1.0f - vdot) < 0.000001)
	{
		vector<glm::vec3> over_line = FindOverlappingLine(curr_face_cnt, curr_face, next_face_cnt, next_face);

		*curr_direc_ptr = next_direc;
		*curr_face_cnt_ptr = next_face_cnt;
		*curr_face_ptr = next_face;
		path_coord_ptr->push_back(glm::vec3((over_line[0].x + over_line[1].x) / 2, (over_line[0].y + over_line[1].y) / 2, (over_line[0].z + over_line[1].z) / 2));
		return; 
	}
	else
	{
		//direc 직선 교점 구하기

		glm::vec3 curr_center_pos(0.0f, 0.0f, 0.0f);
		glm::vec3 next_center_pos(0.0f, 0.0f, 0.0f);

		for (int i = 0; i < curr_face_ver_cnt; i++)
		{
			curr_center_pos.x += curr_face[0];
			curr_center_pos.y += curr_face[1];
			curr_center_pos.z += curr_face[2];
		}

		for (int i = 0; i < next_face_ver_cnt; i++)
		{
			next_center_pos.x += next_face[0];
			next_center_pos.y += next_face[1];
			next_center_pos.z += next_face[2];
		}

		glm::vec3 inter_pos;
		if (abs(curr_direc_vec.x) < 0.000001)
		{
			inter_pos.x = curr_center_pos.x;
			if (abs(next_direc_vec.y) < 0.000001)
				inter_pos.y = curr_center_pos.y;
			else
				inter_pos.y = LinearEquation(next_direc_vec, next_center_pos, 1, inter_pos.x);
		}
		else if (abs(curr_direc_vec.y) < 0.000001)
		{
			inter_pos.y = curr_center_pos.y;
			if (abs(next_direc_vec.x) < 0.000001)
				inter_pos.x = curr_center_pos.x;
			else
				inter_pos.x = LinearEquation(next_direc_vec, next_center_pos, 0, inter_pos.y);
		}
		if (OnFace(inter_pos, curr_face, curr_face_ver_cnt))
		{
			inter_pos.z = PlaneEquation(curr_normal, curr_center_pos, inter_pos);
			vector<glm::vec3> over_line = FindOverlappingLine(curr_face_cnt, curr_face, next_face_cnt, next_face);

			path_coord_ptr->push_back(inter_pos);
			path_coord_ptr->push_back(glm::vec3((over_line[0].x + over_line[1].x) / 2, (over_line[0].y + over_line[1].y) / 2, (over_line[0].z + over_line[1].z) / 2));
		}
		else
		{
			inter_pos.z = PlaneEquation(next_normal, next_center_pos, inter_pos);
			path_coord_ptr->push_back(inter_pos);
		}
		*curr_direc_ptr = next_direc;
		*curr_face_cnt_ptr = next_face_cnt;
		*curr_face_ptr = next_face;
	}
}

std::vector<glm::vec3> Level1::FindOverlappingLine(int curr_face_cnt, float* curr_face, int next_face_cnt, float* next_face)
{
	int curr_line_fidx = 0;
	int next_line_fidx = 0;
	vector<glm::vec3> ret;

	for (curr_line_fidx = 0; curr_line_fidx < curr_face_cnt; curr_line_fidx++)
	{
		int curr_line_sidx = (curr_line_fidx + 1) % curr_face_cnt;

		glm::vec3 curr_vec(curr_face[curr_line_fidx * 3] - curr_face[curr_line_sidx * 3],
			curr_face[curr_line_fidx * 3 + 1] - curr_face[curr_line_sidx * 3 + 1], curr_face[curr_line_fidx * 3 + 2] - curr_face[curr_line_sidx * 3 + 2]);
		for (next_line_fidx = 0; next_line_fidx < next_face_cnt; next_line_fidx++)
		{
			int next_line_sidx = (next_line_fidx + 1) % next_face_cnt;
			glm::vec3 next_vec(next_face[next_line_fidx * 3] - next_face[next_line_sidx * 3],
				next_face[next_line_fidx * 3 + 1] - next_face[next_line_sidx * 3 + 1], next_face[next_line_fidx * 3 + 2] - next_face[next_line_sidx * 3 + 2]);
			float vdot = glm::dot(curr_vec, next_vec);
			if (abs(1.0f - vdot) < 0.000001 || abs(-1.0f - vdot) < 0.000001)
			{
				float curr_vec_size = glm::length(curr_vec);
				float next_vec_size = glm::length(next_vec);
				
				if (curr_vec_size < next_vec_size)
				{
					ret.push_back(glm::vec3(curr_face[curr_line_fidx * 3], curr_face[curr_line_fidx * 3 + 1], curr_face[curr_line_fidx * 3 + 2]));
					ret.push_back(glm::vec3(curr_face[curr_line_sidx * 3], curr_face[curr_line_sidx * 3 + 1], curr_face[curr_line_sidx * 3 + 2]));
				
				}
				else
				{
					ret.push_back(glm::vec3(next_face[next_line_fidx * 3], next_face[next_line_fidx * 3 + 1], next_face[next_line_fidx * 3 + 2]));
					ret.push_back(glm::vec3(next_face[next_line_sidx * 3], next_face[next_line_sidx * 3 + 1], next_face[next_line_sidx * 3 + 2]));
				}
				return ret;
			}
		}
	}

	//there is no overlapping line segments, error
	return ret;
}