#include "../headerFile/Level.h"

float rotateStartTime = 0;
float rotateEndTime = -1;
float rotateCurrTime = 0;
float l_shape_angle = 0;

EllipseArea* ellipse_area;
glm::mat4 ellipse_area_model;
bool l_shape_moving_flag = false;
bool adjust_angle_flag = false;
glm::vec2 prev_mouse_pos_in_model;

extern glm::mat4 vpvp_mat, inv_vp;
extern Level* level;
extern float line_vertices[2][3];

Level::Level(int shape_cnt) : shape_cnt_(shape_cnt), vp_aligned_pos(glm::vec3(0.0f, 0.0f, 0.0f)), wd_char_pos(glm::vec3(0.0f, -0.3f, 1.2f))
{
	shapes_ = new Shape*[shape_cnt];

	moving_shape_cnt_ = 12;

	ellipse_area = new EllipseArea;
	prev_mouse_pos_in_model.x = -1;
	prev_mouse_pos_in_model.y = -1;

	shapes_[0] = new Cuboid();
	shapes_[0]->SetCanBeLocated(true);

	shapes_[1] = new Slope();
	shapes_[1]->SetCanBeLocated(true);

	shapes_[2] = new Goal();
	shapes_[2]->SetCanBeLocated(true);

	shapes_[3] = new Cuboid();
	shapes_[3]->SetCanBeLocated(true);
	shapes_[3]->SetIsFixed(false);

	shapes_[4] = new Cube();
	shapes_[4]->SetCanBeLocated(true);
	shapes_[4]->SetIsFixed(false);

	shapes_[5] = new Cuboid();
	shapes_[5]->SetCanBeLocated(true);
	shapes_[5]->SetIsFixed(false);

	shapes_[6] = new Cuboid();
	shapes_[6]->SetCanBeLocated(true);
	shapes_[6]->SetIsFixed(false);

	shapes_[7] = new Cube();
	shapes_[7]->SetCanBeLocated(true);
	shapes_[7]->SetIsFixed(false);

	shapes_[8] = new Cuboid();
	shapes_[8]->SetCanBeLocated(true);
	shapes_[8]->SetIsFixed(false);

	shapes_[9] = new Cuboid();
	shapes_[9]->SetCanBeLocated(true);
	shapes_[9]->SetIsFixed(false);

	shapes_[10] = new Cube();
	shapes_[10]->SetCanBeLocated(true);
	shapes_[10]->SetIsFixed(false);

	shapes_[11] = new Cuboid();
	shapes_[11]->SetCanBeLocated(true);
	shapes_[11]->SetIsFixed(false);

	shapes_[12] = new Character();

	shapes_[13] = new Rotary_Knob();

	edge = new bool*[moving_shape_cnt_];
	for (int i = 0; i < moving_shape_cnt_; i++)
	{
		edge[i] = new bool[moving_shape_cnt_];
		memset(edge[i], 0, sizeof(bool) * moving_shape_cnt_);
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

void Level::Draw(glm::mat4 worldModel)
{
	glm::mat4 model;
	glm::mat4 model2;

	// draw l_shape
	model = worldModel;
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	model2 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	shapes_[3]->SaveModelData(model2);
	shapes_[3]->Draw(model2);

	shapes_[4]->SaveModelData(model);
	shapes_[4]->Draw(model);

	model2 = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	model2 = glm::rotate(model2, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes_[5]->SaveModelData(model2);
	shapes_[5]->Draw(model2);

	// draw l_shape
	model = worldModel;
	model = glm::translate(model, glm::vec3(1.8f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	model2 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	shapes_[6]->SaveModelData(model2);
	shapes_[6]->Draw(model2);

	shapes_[7]->SaveModelData(model);
	shapes_[7]->Draw(model);

	model2 = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	model2 = glm::rotate(model2, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes_[8]->SaveModelData(model2);
	shapes_[8]->Draw(model2);

	// character
	if (char_move_flag)
	{
		wd_char_pos += deltaTime * dist_vec;
		for (int i = 0; i < path_coord.size() - 1; i++)
		{
			line.SetLine(glm::vec3(path_coord[i].x, path_coord[i].y, -1.0f), glm::vec3(path_coord[i + 1].x, path_coord[i + 1].y, -1.0f));
			line.Draw(worldModel);
		}
		//line.SetLine(projection * view * glm::vec4(wd_char_pos, 1.0f), vp_aligned_pos);
		//line.Draw(worldModel);
		if (glm::length(wd_char_pos - wd_aligned_pos) < 0.01)
		{
			char_move_flag = false;
			wd_char_pos = wd_aligned_pos;
			printf("aa\n");
		}
	}

	model = worldModel;
	model = glm::translate(model, wd_char_pos - glm::vec3(0.0f, -0.4f, 1.2f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	shapes_[12]->Draw(model);

	// adjust angle
	float tmp_angle = (float)fmod(l_shape_angle, 90);
	if (!l_shape_moving_flag && adjust_angle_flag)
	{
		if (tmp_angle < 0.5)
		{
			l_shape_angle = float(int(l_shape_angle / 90) * 90);
			adjust_angle_flag = false;
		}
		else if (tmp_angle > 90 - 0.5)
		{
			l_shape_angle = float((int(l_shape_angle / 90) + 1) % 4 * 90);
			adjust_angle_flag = false;
		}
		else if (tmp_angle > 45.0f)
			l_shape_angle += deltaTime * 60;
		else
			l_shape_angle -= deltaTime * 60;
		level->shapes_[9]->SetIsDirty(true);
		level->shapes_[10]->SetIsDirty(true);
		level->shapes_[11]->SetIsDirty(true);
	}

	// update edge
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

	// draw rotary_knob
	model = worldModel;
	model2 = worldModel;
	model2 = glm::translate(model2, glm::vec3(1.9f, 1.8f, 0.0f));
	model2 = glm::rotate(model2, glm::radians(float(l_shape_angle)), glm::vec3(1.0f, 0.0f, 0.0f));
	shapes_[13]->Draw(model2);

	model = worldModel;
	model = glm::translate(model, glm::vec3(2.15f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 3.0f, 3.0f));
	ellipse_area_model = model;

	if (225 < l_shape_angle && l_shape_angle < 315)
		worldModel = glm::translate(worldModel, glm::vec3(-1.8f, -1.8f, -1.8f));

	// draw l_shape
	model = worldModel;
	model = glm::translate(model, glm::vec3(1.8f, 1.8f, 0.0f));
	model = glm::rotate(model, glm::radians(float(-90 + l_shape_angle)), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	model2 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	shapes_[9]->SaveModelData(model2);
	shapes_[9]->Draw(model2);

	shapes_[10]->SaveModelData(model);
	shapes_[10]->Draw(model);

	model2 = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	model2 = glm::rotate(model2, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes_[11]->SaveModelData(model2);
	shapes_[11]->Draw(model2);;

	// draw cuboid
	model = worldModel;
	model = glm::translate(model, glm::vec3(0.4f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.25f, 1.0f, 1.0f));
	shapes_[0]->SaveModelData(model);
	shapes_[0]->Draw(model);

	// draw slope
	model = worldModel;
	model = glm::translate(model, glm::vec3(0.0f, 2.0f, -0.2f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes_[1]->Draw(model);

	// draw goal
	model = worldModel;
	model = glm::translate(model, glm::vec3(0.0f, 2.3f, -1.1f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	shapes_[2]->SaveModelData(model);
	shapes_[2]->Draw(model);
}

void Level::FindPathCoord(double xpos, double ypos)
{
	glm::vec2	mouse_pos(xpos, ypos);
	float		start_depth = 1;
	float		end_depth = 1;
	glm::vec3	vp_char_pos = vpvp_mat * glm::vec4(wd_char_pos, 1.0f);
	int			start_shape_idx = -1;
	int			end_shape_idx = -1;
	// find the clicked face and face with character
	for (int i = 0; i < shape_cnt_; i++)
	{
		float*	curr_start_face;
		float	curr_start_depth;
		float*	curr_end_face;
		float	curr_end_depth;
		int		curr_face_idx;

		if (shapes_[i]->GetCanBeLocated() == false) continue;
		
		// find the face with character in the shape
		if ((curr_start_face = shapes_[i]->InShape(vp_char_pos, &start_face_direc, &curr_face_idx)))
		{
			curr_start_depth = AverDepth(curr_start_face, shapes_[i]->GetFaceVerCnt());
			if (curr_start_depth > start_depth) continue;
			start_face = curr_start_face;
			start_depth = curr_start_depth;
			start_shape_idx = i;
			start_face_cnt = shapes_[i]->GetFaceCnt();
			start_face_ver_cnt = shapes_[i]->GetFaceVerCnt();
			start_normal_vec = shapes_[i]->GetNormalVec(curr_face_idx);
		}

		// find the clicked face in the shape
		if ((curr_end_face = shapes_[i]->InShape(mouse_pos, &end_face_direc, &curr_face_idx)))
		{
			curr_end_depth = AverDepth(curr_end_face, shapes_[i]->GetFaceVerCnt());
			if (curr_end_depth > end_depth) continue;
			end_face = curr_end_face;
			end_depth = curr_end_depth;
			end_shape_idx = i;
			end_normal_vec = shapes_[i]->GetNormalVec(curr_face_idx);
		}
	}

	// there is no face with chararcter or clicked face
	if (start_shape_idx == -1 || end_shape_idx == -1) return;

	// align mouse_pos
	vp_aligned_pos = AlignPos(end_face, end_face_direc, mouse_pos, shapes_[start_shape_idx]->GetFaceVerCnt());
	
	// find idx path and convert to coord path
	vector<int> path_idx = FindPath(start_shape_idx, end_shape_idx, moving_shape_cnt_, Level::edge);
	//if (path_idx.size() == 0)
	//	return ;

	PathIdxToCoord(vp_char_pos, vp_aligned_pos, path_idx);
	wd_aligned_pos = glm::inverse(viewport * projection * view) * glm::vec4(vp_aligned_pos, 1.0f);
	dist_vec = glm::normalize(wd_aligned_pos - wd_char_pos);
	printf("dist_vec:%f %f %f\nwd_aligned_pos:%f %f %f", dist_vec.x, dist_vec.y, dist_vec.z, wd_aligned_pos.x, wd_aligned_pos.y, wd_aligned_pos.z);
}

Level::~Level()
{
	if (ellipse_area)
		delete ellipse_area;
}

void Level::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		left_mouse_button_down = true;
		glfwGetCursorPos(window, &xpos, &ypos);
		printf("\nmousepos: %f %f\n", xpos, SCR_HEIGHT - ypos);
		if (level->char_move_flag == false)
			level->FindPathCoord((float)xpos, (float)(SCR_HEIGHT - ypos));
		
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		left_mouse_button_down = false;
		l_shape_moving_flag = false;
		adjust_angle_flag = true;
		prev_mouse_pos_in_model.x = -1;
		prev_mouse_pos_in_model.y = -1;
	}
}

void Level::mouse_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (left_mouse_button_down)
	{
		//rotate angle of rotary knob
		float angle = ellipse_area->CheckClickAndFindAngle((float)xpos, (float)(SCR_HEIGHT - ypos), ellipse_area_model);
		if (abs(angle) < 0.000001) return;
		l_shape_angle += angle;
		l_shape_angle = (float)fmod(l_shape_angle + 360, (double)360);
		level->shapes_[9]->SetIsDirty(true);
		level->shapes_[10]->SetIsDirty(true);
		level->shapes_[11]->SetIsDirty(true);
	}
}

void Level::PrintFace(float* face, int ver_cnt)
{
	for (int i = 0; i < ver_cnt; i++)
	{
		printf("point%d: (%f, %f, %f)\n",i , face[i * 3], face[i * 3 + 1], face[i * 3 + 2]);
	}
}

glm::vec3 Level::AlignPos(float* face, int direction, glm::vec2 point, int face_ver_cnt)
{
	glm::vec3 center(0.0f, 0.0f, 0.0f);

	// make center
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

	//direc vector and orthogonal vector
	direc = glm::vec3(face[3] - face[0], face[4] - face[1], face[5] - face[2]);
	ortho = glm::vec3(face[6] - face[3], face[7] - face[4], face[8] - face[5]);

	if (direction == 2)
		std::swap(direc, ortho);

	glm::vec3 vp_aligned_pos(0.0f, 0.0f, 0.0f);

	//find x, y using Linear Equation
	if (abs(direc.x) < 0.000001)
	{
		vp_aligned_pos.x = center.x;
		if (abs(ortho.y) < 0.00001)
			vp_aligned_pos.y = point.y;
		else
			vp_aligned_pos.y = LinearEquation(ortho, point, 1, vp_aligned_pos.x);
	}
	else if (abs(direc.y) < 0.00001)
	{
		vp_aligned_pos.y = center.y;
		if (abs(ortho.x) < 0.00001)
			vp_aligned_pos.x = point.x;
		else
			vp_aligned_pos.x = LinearEquation(ortho, point, 0, vp_aligned_pos.y);
	}
	else
	{
		vp_aligned_pos.x = (direc.x * ortho.x * (point.y - center.y) + (direc.y * ortho.x * center.x - ortho.y * direc.x * point.x))
			/ (direc.y * ortho.x - ortho.y * direc.x);
		if (abs(ortho.x) < 0.00001)
		{
			vp_aligned_pos.x = point.x;
			vp_aligned_pos.y = LinearEquation(direc, center, 1, vp_aligned_pos.x);
		}
		else if (abs(ortho.y) < 0.00001)
		{
			vp_aligned_pos.y = point.y;
			vp_aligned_pos.x = LinearEquation(direc, center, 0, vp_aligned_pos.y);
		}
		else
		{
			vp_aligned_pos.x = (direc.x * ortho.x * (point.y - center.y) + (direc.y * ortho.x * center.x - ortho.y * direc.x * point.x))
				/ (direc.y * ortho.x - ortho.y * direc.x);
			vp_aligned_pos.y = LinearEquation(ortho, point, 1, vp_aligned_pos.x);
		}
	}

	//find z from x, y using equation of a plane
	vp_aligned_pos.z = PlaneEquation(glm::cross(glm::vec3(face[3] - face[0], face[4] - face[1], face[5] - face[2]), glm::vec3(face[6] - face[0], face[7] - face[1], face[8] - face[2])),
		glm::vec3(face[0], face[1], face[2]), vp_aligned_pos);
	return vp_aligned_pos;
}

// find path using bfs
std::vector<int> Level::FindPath(int start, int end, int size, bool** edge)
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
	std::reverse(ret.begin(), ret.end());
	return ret;
}

glm::vec3 curr_normal_vec;

bool Level::PathIdxToCoord(glm::vec3 vp_start, glm::vec3 vp_end, vector<int> path_idx)
{
	int	size = (int)path_idx.size();
	int curr_direc = start_face_direc;
	float* curr_face = start_face;
	int curr_face_cnt = start_face_cnt;
	int curr_face_ver_cnt = start_face_ver_cnt;
	curr_normal_vec = start_normal_vec;

	path_coord.clear();
	path_coord.push_back(inv_vp * glm::vec4(vp_start, 1.0f));

	if (size == 1) return false;
	else
	{
		glm::vec3 curr = vp_start;
		for (int i = 0; i < size - 1; i++)
			FindCoord(&curr_face, path_idx[i + 1], curr, &curr_direc, &curr_face_cnt, &curr_face_ver_cnt);

		float vdot = glm::dot(curr_normal_vec, end_normal_vec);
		if (abs(1.0f - vdot) > 0.000001) return false;

		//curr_direc_vec와 aligned pos를 지나는 직선위에 last pos가 놓여 있다.
		glm::vec3 recent_pos = viewport * glm::vec4(path_coord[path_coord.size() - 1], 1.0f);
		glm::vec3 curr_direc_vec;
		glm::vec3 curr_ortho_vec;
		glm::vec3 additional_pos;

		if (curr_direc == 0)
		{
			char_move_flag = true;
			path_coord_idx = 0;
			return true;
		}

		curr_direc_vec = glm::vec3(curr_face[3] - curr_face[0], curr_face[4] - curr_face[1], curr_face[5] - curr_face[2]);
		curr_ortho_vec = glm::vec3(curr_face[6] - curr_face[3], curr_face[7] - curr_face[4], curr_face[8] - curr_face[5]);
		if (curr_direc == 2)
			swap(curr_direc_vec, curr_ortho_vec);

		if (curr_direc_vec.x == 0)
		{
			if (recent_pos.x == vp_end.x)
				path_coord.push_back(inv_vp * glm::vec4(vp_end, 1.0f));
			else
			{
				// curr_direc_vec.x == 0 && curr_ortho_vec.x == 0 불가능
				additional_pos.x = vp_end.x;
				if (curr_ortho_vec.y == 0)
				{
					additional_pos.y = recent_pos.y;
					additional_pos.z = PlaneEquation(vpvp_mat * glm::vec4(curr_normal_vec, 0.0f), vp_end, additional_pos);
					path_coord.push_back(inv_vp * glm::vec4(additional_pos, 1.0f));
				}
				else
				{
					additional_pos.y = LinearEquation(curr_ortho_vec, recent_pos, 1, vp_end.x);
					additional_pos.z = PlaneEquation(vpvp_mat * glm::vec4(curr_normal_vec, 0.0f), vp_end, additional_pos);
					path_coord.push_back(inv_vp * glm::vec4(additional_pos, 1.0f));
				}
			}
		}
		else if (curr_direc_vec.y == 0)
		{
			if (recent_pos.y == vp_end.y)
				path_coord.push_back(inv_vp * glm::vec4(vp_end, 1.0f));
			else
			{
				//curr_direc_vec.x == 0 && curr_direc_vec.y == 0 이미 처리함
				additional_pos.y = vp_end.y;
				additional_pos.x = LinearEquation(curr_ortho_vec, recent_pos, 0, additional_pos.y);
				additional_pos.z = PlaneEquation(vpvp_mat * glm::vec4(curr_normal_vec, 0.0f), vp_end, additional_pos);
				path_coord.push_back(inv_vp * glm::vec4(additional_pos, 1.0f));
			}
		}
		else
		{
			//direc, ortho 교점 구하기
		}

		char_move_flag = true;
		path_coord_idx = 0;
		return true;
	}
}

void Level::FindCoord(float** curr_face_ptr, int next_idx, glm::vec3 curr_pos, int* curr_direc_ptr, int* curr_face_cnt_ptr, int* curr_face_ver_cnt_ptr)
{
	float* curr_face = *curr_face_ptr;
	int curr_face_cnt = *curr_face_cnt_ptr;
	int curr_face_ver_cnt = *curr_face_ver_cnt_ptr;
	float* next_face = shapes_[next_idx]->GetCurrFaceVer();
	int next_face_cnt = shapes_[next_idx]->GetFaceCnt();
	int next_face_ver_cnt = shapes_[next_idx]->GetFaceVerCnt();

	//-- Find next_face having same curr_normal
	glm::mat4 inv_mat = glm::inverse(viewport * projection * view);
	glm::vec3 curr_normal = curr_normal_vec;
	glm::vec3 next_normal(0.0f, 0.0f, 0.0f);

	int curr_direc = *curr_direc_ptr;
	int next_direc = 0;
	float vdot;

	// brute force to find a suitable face in shape
	for (int i = 0; i < next_face_cnt; i++)
	{
		next_normal = shapes_[next_idx]->GetNormalVec(i);
		vdot = glm::dot(curr_normal, next_normal);
		if (abs(1.0f - vdot) < 0.0001)
		{
			next_direc = shapes_[next_idx]->WGetFaceDirFlag(i);
			break; 
		}
		next_face += 3 * next_face_ver_cnt;
	}

	//-- Change next data to curr data for loop 
	*curr_direc_ptr = next_direc;
	*curr_face_cnt_ptr = next_face_cnt;
	*curr_face_ptr = next_face;
	*curr_face_ver_cnt_ptr = next_face_ver_cnt;
	curr_normal_vec = next_normal;
	//-- Consider all face_direc_vec pairs
	// Find curr and next_direc_vec;
	// Direc_vec is direction that the character can move on the face
	glm::vec3 curr_direc_vec;
	glm::vec3 next_direc_vec;

	// Direc = 0 : a face of cube (face is square)
	// Direc = 1 : find direc vector with face_vertex[0] and face_vertex[1] (face is rectangular)
	// Direc = 2 : find direc vector with face_vertex[1] and face_vertex[2] (face is rectangular)
	if (next_direc == 0)
	{
		path_coord.push_back(inv_vp * glm::vec4(FindCenterPos(next_face, next_face_ver_cnt), 1.0f));
		return;
	}
	if (curr_direc == 0)
	{
		// Find intersection line
		vector<glm::vec3> over_line = FindOverlappingLine(curr_face_ver_cnt, curr_face, next_face_ver_cnt, next_face);
		// Midpoint of line
		path_coord.push_back(inv_vp * glm::vec4((over_line[0].x + over_line[1].x) / 2, (over_line[0].y + over_line[1].y) / 2, (over_line[0].z + over_line[1].z) / 2, 1.0f));
		return;
	}

	if (curr_direc == 1)
		curr_direc_vec = glm::vec3(curr_face[3] - curr_face[0], curr_face[4] - curr_face[1], curr_face[5] - curr_face[2]);
	else
		curr_direc_vec = glm::vec3(curr_face[6] - curr_face[3], curr_face[7] - curr_face[4], curr_face[8] - curr_face[5]);

	if (next_direc == 1)
		next_direc_vec = glm::vec3(next_face[3] - next_face[0], next_face[4] - next_face[1], next_face[5] - next_face[2]);
	else
		next_direc_vec = glm::vec3(next_face[6] - next_face[3], next_face[7] - next_face[4], next_face[8] - next_face[5]);

	// Check to is parallel
	vdot = glm::dot(glm::normalize(glm::vec2(curr_direc_vec.x, curr_direc_vec.y)), glm::normalize(glm::vec2(next_direc_vec.x, next_direc_vec.y)));
	if (abs(1.0f - vdot) < 0.000001 || abs(-1.0f - vdot) < 0.000001)
	{
		// When two direc_vec are parallel
		vector<glm::vec3> over_line = FindOverlappingLine(curr_face_ver_cnt, curr_face, next_face_ver_cnt, next_face);
		// Midpoint of overlapping line
		path_coord.push_back(inv_vp * glm::vec4((over_line[0].x + over_line[1].x) / 2, (over_line[0].y + over_line[1].y) / 2, (over_line[0].z + over_line[1].z) / 2, 1.0f));
		return; 
	}
	else
	{
		// When two direc_vec are not parallel

		glm::vec3 curr_center_pos = FindCenterPos(curr_face, curr_face_ver_cnt);
		glm::vec3 next_center_pos = FindCenterPos(next_face, next_face_ver_cnt);

		glm::vec3 inter_pos;
		if (abs(curr_direc_vec.x) < 0.0001)
		{
			inter_pos.x = curr_center_pos.x;
			if (abs(next_direc_vec.y) < 0.0001)
				inter_pos.y = curr_center_pos.y;
			else
				inter_pos.y = LinearEquation(next_direc_vec, next_center_pos, 1, inter_pos.x);
		}
		else if (abs(curr_direc_vec.y) < 0.0001)
		{
			inter_pos.y = curr_center_pos.y;
			// if (abs(next_direc_vec.y) < 0.0001) 위에서 처리됨
			inter_pos.x = LinearEquation(next_direc_vec, next_center_pos, 0, inter_pos.y);
		}
		else
		{
			inter_pos.x = (curr_direc_vec.y * next_direc_vec.x * curr_center_pos.x - curr_direc_vec.x * next_direc_vec.y * next_center_pos.x + curr_direc_vec.x * next_direc_vec.x * (next_center_pos.y - curr_center_pos.y))
				/ (curr_direc_vec.y * next_direc_vec.x - curr_direc_vec.x * next_direc_vec.y);
			inter_pos.y = LinearEquation(next_direc_vec, next_center_pos, 1, inter_pos.x);
		}
		if (OnFace(inter_pos, curr_face, curr_face_ver_cnt))
		{
			inter_pos.z = PlaneEquation(vpvp_mat * glm::vec4(curr_normal, 0.0f), curr_center_pos, inter_pos);
			vector<glm::vec3> over_line = FindOverlappingLine(curr_face_ver_cnt, curr_face, next_face_ver_cnt, next_face);

			path_coord.push_back(inv_vp * glm::vec4(inter_pos, 1.0f));
			path_coord.push_back(inv_vp * glm::vec4((over_line[0].x + over_line[1].x) / 2, (over_line[0].y + over_line[1].y) / 2, (over_line[0].z + over_line[1].z) / 2, 1.0f));
		}
		else
		{
			inter_pos.z = PlaneEquation(vpvp_mat * glm::vec4(next_normal, 0.0f), next_center_pos, inter_pos);
			path_coord.push_back(inv_vp * glm::vec4(inter_pos, 1.0f));
		}
		*curr_direc_ptr = next_direc;
		*curr_face_cnt_ptr = next_face_cnt;
		*curr_face_ptr = next_face;
	}
}

std::vector<glm::vec3> Level::FindOverlappingLine(int curr_face_ver_cnt, float* curr_face, int next_face_ver_cnt, float* next_face)
{
	int curr_line_fidx = 0;
	int next_line_fidx = 0;
	vector<glm::vec3> ret;

	for (curr_line_fidx = 0; curr_line_fidx < curr_face_ver_cnt; curr_line_fidx++)
	{
		int curr_line_sidx = (curr_line_fidx + 1) % curr_face_ver_cnt;

		for (next_line_fidx = 0; next_line_fidx < next_face_ver_cnt; next_line_fidx++)
		{
			int next_line_sidx = (next_line_fidx + 1) % next_face_ver_cnt;

			if ((abs(curr_face[curr_line_fidx * 3] - next_face[next_line_fidx * 3]) < 0.0001 && abs(curr_face[curr_line_fidx * 3 + 1] - next_face[next_line_fidx * 3 + 1]) < 0.0001
				&& abs(curr_face[curr_line_sidx * 3] - next_face[next_line_sidx * 3]) < 0.0001 && abs(curr_face[curr_line_sidx * 3 + 1] - next_face[next_line_sidx * 3 + 1]) < 0.0001)
				|| (abs(curr_face[curr_line_fidx * 3] - next_face[next_line_sidx * 3]) < 0.0001 && abs(curr_face[curr_line_fidx * 3 + 1] - next_face[next_line_sidx * 3 + 1]) < 0.0001
				&& abs(curr_face[curr_line_sidx * 3] - next_face[next_line_fidx * 3]) < 0.0001 && abs(curr_face[curr_line_sidx * 3 + 1] - next_face[next_line_fidx * 3 + 1]) < 0.0001))
			{
				ret.push_back(glm::vec3(curr_face[curr_line_fidx * 3], curr_face[curr_line_fidx * 3 + 1], curr_face[curr_line_fidx * 3 + 2]));
				ret.push_back(glm::vec3(next_face[next_line_fidx * 3], next_face[next_line_fidx * 3 + 1], next_face[next_line_fidx * 3 + 2]));
				return ret;
			}
		}
	}

	//there is no overlapping line segments, error
	return ret;
}

glm::vec3 Level::FindCenterPos(float *points, int ver_cnt)
{
	glm::vec3 center_pos(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < ver_cnt; i++)
	{
		center_pos.x += points[i * 3];
		center_pos.y += points[i * 3 + 1];
		center_pos.z += points[i * 3 + 2];
	}
	center_pos.x /= ver_cnt;
	center_pos.y /= ver_cnt;
	center_pos.z /= ver_cnt;
	return center_pos;
}