#include "../headerFile/Level.h"

float rotateStartTime = 0;
float rotateEndTime = -1;
float rotateCurrTime = 0;
float rotate_obj_angle = 0;

EllipseArea* ellipse_area;
glm::mat4 ellipse_area_model;
bool l_shape_moving_flag = false;
bool adjust_angle_flag = false;
glm::vec2 prev_mouse_pos_in_model;

extern glm::mat4 vpvp_mat, inv_vp, inv_vpvp;
extern Level* level;
extern float line_vertices[2][3];

Level::Level(int acg_cnt, int orna_cnt, glm::mat4 world_model) : acg_cnt_(acg_cnt), orna_cnt_(orna_cnt), vp_aligned_pos(glm::vec3(0.0f, 0.0f, 0.0f)), wd_acter_pos(glm::vec3(0.0f, -0.3f, 1.2f)),
init_acter_direc_vec(glm::vec3(1.0f, 0.0f, 0.0f))
{
	world_model_ = world_model;
	acg_object_ = new ActerCanGoObject * [acg_cnt_];
	ornaments_ = new Ornament * [orna_cnt_];

	ellipse_area = new EllipseArea;
	prev_mouse_pos_in_model.x = -1;
	prev_mouse_pos_in_model.y = -1;

	acg_object_[0] = new Cuboid();
	acg_object_[0]->SetCanBeLocated(true);
	acg_object_[0]->SetIsFixed(false);

	acg_object_[1] = new Goal();
	acg_object_[1]->SetCanBeLocated(true);
	acg_object_[1]->SetIsFixed(false);

	// L_Shape
	acg_object_[2] = new Cuboid();
	acg_object_[2]->SetCanBeLocated(true);
	acg_object_[2]->SetIsFixed(false);

	acg_object_[3] = new Cube();
	acg_object_[3]->SetCanBeLocated(true);
	acg_object_[3]->SetIsFixed(false);

	acg_object_[4] = new Cuboid();
	acg_object_[4]->SetCanBeLocated(true);
	acg_object_[4]->SetIsFixed(false);

	// L_Shape
	acg_object_[5] = new Cuboid();
	acg_object_[5]->SetCanBeLocated(true);
	acg_object_[5]->SetIsFixed(false);

	acg_object_[6] = new Cube();
	acg_object_[6]->SetCanBeLocated(true);
	acg_object_[6]->SetIsFixed(false);

	acg_object_[7] = new Cuboid();
	acg_object_[7]->SetCanBeLocated(true);
	acg_object_[7]->SetIsFixed(false);

	// Rotating L_Shape
	acg_object_[8] = new Cuboid();
	acg_object_[8]->SetCanBeLocated(true);
	acg_object_[8]->SetIsFixed(false);

	acg_object_[9] = new Cube();
	acg_object_[9]->SetCanBeLocated(true);
	acg_object_[9]->SetIsFixed(false);

	acg_object_[10] = new Cuboid();
	acg_object_[10]->SetCanBeLocated(true);
	acg_object_[10]->SetIsFixed(false);

	acg_object_[11] = new Cuboid();
	acg_object_[11]->SetCanBeLocated(true);
	acg_object_[11]->SetIsFixed(false);

	obj_can_rotate.push_back(8);
	obj_can_rotate.push_back(9);
	obj_can_rotate.push_back(10);

	obj_opt_mov.push_back(0);
	obj_opt_mov.push_back(1);
	obj_opt_mov.push_back(8);
	obj_opt_mov.push_back(9);
	obj_opt_mov.push_back(10);
	obj_opt_mov.push_back(11);


	for (int i = 0; i < acg_cnt_; i++)
	{
		acg_object_[i]->SetObjColor(glm::vec3(0.8f, 0.64f, 0.64f));
	}

	ornaments_[0] = new Acter();
	ornaments_[1] = new Rotary_Knob();

	edge = new bool* [acg_cnt_];
	for (int i = 0; i < acg_cnt_; i++)
	{
		edge[i] = new bool[acg_cnt_];
		memset(edge[i], 0, sizeof(bool) * acg_cnt_);
	}

	edge[0][8] = 1;
	edge[0][11] = 1;
	edge[1][11] = 1;
	edge[2][3] = 1;
	edge[3][2] = 1;
	edge[3][4] = 1;
	edge[4][3] = 1;
	edge[4][5] = 1;
	edge[5][4] = 1;
	edge[5][6] = 1;
	edge[6][5] = 1;
	edge[6][7] = 1;
	edge[7][6] = 1;
	edge[7][10] = 1;
	edge[8][0] = 1;
	edge[8][9] = 1;
	edge[9][8] = 1;
	edge[9][10] = 1;
	edge[10][7] = 1;
	edge[10][9] = 1;
	edge[11][0] = 1;
	edge[11][1] = 1;

	acter_ = (Acter*)ornaments_[0];
}

void Level::Draw()
{
	glm::mat4 model;
	glm::mat4 model2;

	// draw l_shape
	model = world_model_;
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	model2 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	acg_object_[2]->UpdateObjData(model2);
	acg_object_[2]->Draw(model2);

	acg_object_[3]->UpdateObjData(model);
	acg_object_[3]->Draw(model);

	model2 = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	model2 = glm::rotate(model2, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	acg_object_[4]->UpdateObjData(model2);
	acg_object_[4]->Draw(model2);

	// draw l_shape
	model = world_model_;
	model = glm::translate(model, glm::vec3(1.8f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	model2 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	acg_object_[5]->UpdateObjData(model2);
	acg_object_[5]->Draw(model2);

	acg_object_[6]->UpdateObjData(model);
	acg_object_[6]->Draw(model);

	model2 = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	model2 = glm::rotate(model2, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	acg_object_[7]->UpdateObjData(model2);
	acg_object_[7]->Draw(model2);

	// acter moving
	if (acter_move_flag)
	{
		wd_acter_pos += delta_time * dist_vec;
		for (int i = 0; i < path_coord.size() - 1; i++)
		{
			glm::vec3 fpos = projection * view * glm::vec4(path_coord[i], 1.0f);
			glm::vec3 spos = projection * view * glm::vec4(path_coord[i + 1], 1.0f);
			fpos.z += -0.001f;
			spos.z += -0.001f;
			line.SetLine(fpos, spos);
			line.Draw(world_model_);
		}
		if (glm::length(wd_acter_pos - path_coord[path_coord_idx]) < 0.01)
		{
			wd_acter_pos = path_coord[path_coord_idx];
			path_coord_idx++;
			if (path_coord_idx == path_coord.size())
				acter_move_flag = false;
			else
			{
				dist_vec = glm::normalize(path_coord[path_coord_idx] - path_coord[path_coord_idx - 1]);
				float angle = glm::degrees(acos(glm::dot(init_acter_direc_vec.xz(), dist_vec.xz())));
				if (glm::cross(glm::vec3(init_acter_direc_vec.x, 0, init_acter_direc_vec.y), glm::vec3(dist_vec.x, 0, dist_vec.z)).y < 0)
					angle *= -1;

				acter_->SetActerRotateAngle(angle);
			}
		}
	}

	model = world_model_;
	model = glm::translate(model, wd_acter_pos - glm::vec3(0.0f, -0.4f, 1.2f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	ornaments_[0]->Draw(model);

	// adjust angle
	float tmp_angle = (float)fmod(rotate_obj_angle, 90);
	if (!l_shape_moving_flag && adjust_angle_flag)
	{
		if (tmp_angle < 0.5)
		{
			rotate_obj_angle = float(int(rotate_obj_angle / 90) * 90);
			adjust_angle_flag = false;
		}
		else if (tmp_angle > 90 - 0.5)
		{
			rotate_obj_angle = float((int(rotate_obj_angle / 90) + 1) % 4 * 90);
			adjust_angle_flag = false;
		}
		else if (tmp_angle > 45.0f)
			rotate_obj_angle += delta_time * 60;
		else
			rotate_obj_angle -= delta_time * 60;
		acg_object_[8]->SetIsDirty(true);
		acg_object_[9]->SetIsDirty(true);
		acg_object_[10]->SetIsDirty(true);
	}

	// update edge
	if (rotate_obj_angle == 270)
	{
		edge[7][10] = 0;
		edge[10][7] = 0;
		edge[2][10] = 1;
		edge[10][2] = 1;
	}
	else if (rotate_obj_angle == 0)
	{
		edge[7][10] = 1;
		edge[10][7] = 1;
		edge[2][10] = 0;
		edge[10][2] = 0;
	}
	else if (rotate_obj_angle == 90 || rotate_obj_angle == 180)
	{
		edge[7][10] = 0;
		edge[10][7] = 0;
		edge[2][10] = 0;
		edge[10][2] = 0;
	}

	// draw rotary_knob
	model = world_model_;
	model2 = world_model_;
	model2 = glm::translate(model2, glm::vec3(1.9f, 1.8f, 0.0f));
	model2 = glm::rotate(model2, glm::radians(float(rotate_obj_angle)), glm::vec3(1.0f, 0.0f, 0.0f));
	ornaments_[1]->Draw(model2);

	model = world_model_;
	model = glm::translate(model, glm::vec3(2.15f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 3.0f, 3.0f));
	ellipse_area_model = model;

	glm::mat4 opt_world_model_ = world_model_;
	if (225 < rotate_obj_angle && rotate_obj_angle < 315)
	{
		opt_world_model_ = glm::translate(world_model_, glm::vec3(-1.8f, -1.8f, -1.8f));
		if (opt_obj_move_flag == false)
		{
			level->acg_object_[0]->SetIsDirty(true);
			level->acg_object_[1]->SetIsDirty(true);
			level->acg_object_[11]->SetIsDirty(true);
			if (ChkActorOnObj(obj_opt_mov))
				wd_acter_pos += glm::vec3(-1.8f, -1.8f, -1.8f);
		}
		opt_obj_move_flag = true;
	}
	else
	{
		if (opt_obj_move_flag == true)
		{
			level->acg_object_[0]->SetIsDirty(true);
			level->acg_object_[1]->SetIsDirty(true);
			level->acg_object_[11]->SetIsDirty(true);
			if (ChkActorOnObj(obj_opt_mov))
				wd_acter_pos += glm::vec3(1.8f, 1.8f, 1.8f);
		}
		opt_obj_move_flag = false;
	}

	// draw l_shape
	model = opt_world_model_;
	model = glm::translate(model, glm::vec3(1.8f, 1.8f, 0.0f));
	model = glm::rotate(model, glm::radians(float(-90 + rotate_obj_angle)), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(float(180)), glm::vec3(0.0f, 1.0f, 0.0f));
	model2 = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
	acg_object_[8]->UpdateObjData(model2);
	acg_object_[8]->Draw(model2);

	acg_object_[9]->UpdateObjData(model);
	acg_object_[9]->Draw(model);

	model2 = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f));
	model2 = glm::rotate(model2, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	acg_object_[10]->UpdateObjData(model2);
	acg_object_[10]->Draw(model2);

	// draw cuboid
	model = opt_world_model_;
	model = glm::translate(model, glm::vec3(0.4f, 1.8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.25f, 1.0f, 1.0f));
	acg_object_[0]->UpdateObjData(model);
	acg_object_[0]->Draw(model);

	// draw cuboid
	model = opt_world_model_;
	model = glm::translate(model, glm::vec3(0.0f, 1.8f, -0.5f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	acg_object_[11]->UpdateObjData(model);
	acg_object_[11]->Draw(model);

	// draw goal
	model = opt_world_model_;
	model = glm::translate(model, glm::vec3(0.0f, 1.9f, -0.9f));
	model = glm::rotate(model, glm::radians(float(90)), glm::vec3(0.0f, 1.0f, 0.0f));
	acg_object_[1]->UpdateObjData(model);
	acg_object_[1]->Draw(model);

	ChkDisableFace();
}

void Level::FindPathCoord(double xpos, double ypos)
{
	glm::vec2	mouse_pos(xpos, ypos);
	float		start_depth = 1;
	float		end_depth = 1;
	glm::vec3	vp_acter_pos = vpvp_mat * glm::vec4(wd_acter_pos, 1.0f);
	int			start_obj_idx = -1;
	int			end_obj_idx = -1;
	// find the clicked face and face with acter
	for (int i = 0; i < acg_cnt_; i++)
	{
		float*	curr_start_face;
		float	curr_start_depth;
		float*	curr_end_face;
		float	curr_end_depth;
		int		curr_face_idx;

		if (acg_object_[i]->GetCanBeLocated() == false) continue;

		// find the face with acter in the obj
		if ((curr_start_face = acg_object_[i]->IsInObj(vp_acter_pos, &start_face_direc, &curr_face_idx)))
		{
			curr_start_depth = AverDepth(curr_start_face, acg_object_[i]->GetFaceVerCnt());
			if (curr_start_depth < start_depth)
			{
				start_face = curr_start_face;
				start_depth = curr_start_depth;
				start_obj_idx = i;
				start_face_cnt = acg_object_[i]->GetFaceCnt();
				start_face_ver_cnt = acg_object_[i]->GetFaceVerCnt();
				start_normal_vec = acg_object_[i]->GetNormalVec(curr_face_idx);
			}
		}

		// find the clicked face in the obj
		if ((curr_end_face = acg_object_[i]->IsInObj(mouse_pos, &end_face_direc, &curr_face_idx)))
		{
			curr_end_depth = AverDepth(curr_end_face, acg_object_[i]->GetFaceVerCnt());
			if (curr_end_depth > end_depth) continue;
			end_face = curr_end_face;
			end_depth = curr_end_depth;
			end_obj_idx = i;
			end_normal_vec = acg_object_[i]->GetNormalVec(curr_face_idx);
		}
	}

	// there is no face with chararcter or clicked face
	if (start_obj_idx == -1 || end_obj_idx == -1) return;

	// align mouse_pos
	vp_aligned_pos = AlignPos(end_face, end_face_direc, mouse_pos, acg_object_[start_obj_idx]->GetFaceVerCnt());

	// find idx path and convert to coord path
	vector<int> path_idx = FindPath(start_obj_idx, end_obj_idx, acg_cnt_, Level::edge);
	if (path_idx.size() == 0)return;
	if (!PathIdxToCoord(vp_acter_pos, vp_aligned_pos, path_idx)) return;
	acter_move_flag = true;
	path_coord_idx = 1;
	obj_on_acter = end_obj_idx;
	dist_vec = glm::normalize(path_coord[1] - path_coord[0]);

	float angle = glm::degrees(acos(glm::dot(init_acter_direc_vec.xz(), dist_vec.xz())));
	if (glm::cross(glm::vec3(init_acter_direc_vec.x, 0, init_acter_direc_vec.y), glm::vec3(dist_vec.x, 0, dist_vec.z)).y < 0)
		angle *= -1;

	acter_->SetActerRotateAngle(angle);
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
		if (level->acter_move_flag == false)
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
	if (left_mouse_button_down && level->acter_move_flag == false)
	{
		// Make sure the actor is not on an object
		if (level->ChkActorOnObj(level->obj_can_rotate) == true) return;

		// Find the angle of rotation
		float angle = ellipse_area->CheckClickAndFindAngle((float)xpos, (float)(SCR_HEIGHT - ypos), ellipse_area_model);
		if (abs(angle) < 0.001) return;
		rotate_obj_angle += angle;
		rotate_obj_angle = (float)fmod(rotate_obj_angle + 360, (double)360);

		// Need vertex update
		level->acg_object_[8]->SetIsDirty(true);
		level->acg_object_[9]->SetIsDirty(true);
		level->acg_object_[10]->SetIsDirty(true);
	}
}

void Level::PrintFace(float* face, int ver_cnt)
{
	for (int i = 0; i < ver_cnt; i++)
	{
		printf("point%d: (%f, %f, %f)\n", i, face[i * 3], face[i * 3 + 1], face[i * 3 + 2]);
	}
}

glm::vec3 Level::AlignPos(float* face, int direction, glm::vec2 point, int face_ver_cnt)
{
	glm::vec3 center = FindCenterPos(face, face_ver_cnt);

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
	std::queue<int>		qu;
	int*				visited;
	int					curr;
	bool				find_flag = false;
	std::vector<int>	ret;

	if (start == end)
	{
		ret.push_back(start);
		return ret;
	}
	visited = new int[size];
	std::fill(visited, visited + size, -1);

	visited[start] = 0;

	// bfs
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
			if (i == end)
			{
				find_flag = true;
				break;
			}
			qu.push(i);
		}
		if (find_flag)
			break;
	}


	if (find_flag == false)
	{
		delete[] visited;
		return ret;
	}

	// save path idx
	curr = end;
	while (curr != start)
	{
		ret.push_back(curr);
		curr = visited[curr];
	}
	ret.push_back(curr);
	std::reverse(ret.begin(), ret.end());
	delete[] visited;
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
	path_coord.push_back(inv_vpvp * glm::vec4(vp_start, 1.0f));

	if (size != 1 || size == 1 && curr_direc != 0)
	{
		glm::vec3 curr = vp_start;
		for (int i = 0; i < size - 1; i++)
			if (FindCoord(&curr_face, path_idx[i + 1], curr, &curr_direc, &curr_face_cnt, &curr_face_ver_cnt) == false)
				return false;

		float vdot = glm::dot(curr_normal_vec, end_normal_vec);
		if (abs(1.0f - vdot) > 0.000001) return false;

		//curr_direc_vec�� aligned pos�� ������ �������� last pos�� ���� �ִ�.
		glm::vec3 recent_pos = vpvp_mat * glm::vec4(path_coord[path_coord.size() - 1], 1.0f);
		glm::vec3 curr_direc_vec;
		glm::vec3 curr_ortho_vec;
		glm::vec3 additional_pos;

		if (curr_direc == 0)
			return true;

		curr_direc_vec = glm::vec3(curr_face[3] - curr_face[0], curr_face[4] - curr_face[1], curr_face[5] - curr_face[2]);
		curr_ortho_vec = glm::vec3(curr_face[6] - curr_face[3], curr_face[7] - curr_face[4], curr_face[8] - curr_face[5]);
	
		if (curr_direc == 2)
			swap(curr_direc_vec, curr_ortho_vec);

		if (curr_direc_vec.x == 0)
		{
			if (recent_pos.x != vp_end.x)
			{
				// curr_direc_vec.x == 0 && curr_ortho_vec.x == 0 �Ұ���
				additional_pos.x = vp_end.x;
				if (curr_ortho_vec.y == 0)
				{
					additional_pos.y = recent_pos.y;
					additional_pos.z = PlaneEquation(vpvp_mat * glm::vec4(curr_normal_vec, 0.0f), vp_end, additional_pos);
					path_coord.push_back(inv_vpvp * glm::vec4(additional_pos, 1.0f));
				}
				else
				{
					additional_pos.y = LinearEquation(curr_ortho_vec, recent_pos, 1, additional_pos.x);
					additional_pos.z = PlaneEquation(vpvp_mat * glm::vec4(curr_normal_vec, 0.0f), vp_end, additional_pos);
					path_coord.push_back(inv_vpvp * glm::vec4(additional_pos, 1.0f));
				}
			}
		}
		else if (curr_direc_vec.y == 0)
		{
			if (recent_pos.y != vp_end.y)
			{
				//curr_direc_vec.x == 0 && curr_direc_vec.y == 0 �̹� ó����
				additional_pos.y = vp_end.y;
				additional_pos.x = LinearEquation(curr_ortho_vec, recent_pos, 0, additional_pos.y);
				additional_pos.z = PlaneEquation(vpvp_mat * glm::vec4(curr_normal_vec, 0.0f), vp_end, additional_pos);
				path_coord.push_back(inv_vpvp * glm::vec4(additional_pos, 1.0f));
			}
		}
		else
		{
			if (abs(recent_pos.y - LinearEquation(curr_direc_vec, vp_aligned_pos, 1, recent_pos.x)) > 0.01)
			{
				//direc, ortho ���� ���ϱ�
				additional_pos.x = (curr_ortho_vec.x * curr_direc_vec.x * (recent_pos.y - vp_end.y) + curr_direc_vec.y * curr_ortho_vec.x * vp_end.x - curr_ortho_vec.y * curr_direc_vec.x * recent_pos.x)
					/ (curr_ortho_vec.x * curr_direc_vec.y - curr_direc_vec.x * curr_ortho_vec.y);
				additional_pos.y = LinearEquation(curr_ortho_vec, recent_pos, 1, additional_pos.x);
				additional_pos.z = PlaneEquation(glm::cross(curr_direc_vec, curr_ortho_vec), vp_end, additional_pos);
				path_coord.push_back(inv_vpvp * glm::vec4(additional_pos, 1.0f));
			}
		}
		path_coord.push_back(inv_vpvp * glm::vec4(vp_end, 1.0f));
		return true;
	}
	return false;
}

bool Level::FindCoord(float** curr_face_ptr, int next_idx, glm::vec3 curr_pos, int* curr_direc_ptr, int* curr_face_cnt_ptr, int* curr_face_ver_cnt_ptr)
{
	float* curr_face = *curr_face_ptr;
	int curr_face_cnt = *curr_face_cnt_ptr;
	int curr_face_ver_cnt = *curr_face_ver_cnt_ptr;
	float* next_face = acg_object_[next_idx]->GetCurrFaceVer();
	int next_face_cnt = acg_object_[next_idx]->GetFaceCnt();
	int next_face_ver_cnt = acg_object_[next_idx]->GetFaceVerCnt();

	//-- Find next_face having same curr_normal
	glm::mat4 inv_mat = glm::inverse(viewport * projection * view);
	glm::vec3 curr_normal = curr_normal_vec;
	glm::vec3 next_normal(0.0f, 0.0f, 0.0f);

	int curr_direc = *curr_direc_ptr;
	int next_direc = -1;
	float vdot;

	// brute force to find a suitable face in shape
	for (int i = 0; i < next_face_cnt; i++, next_face += 3 * next_face_ver_cnt)
	{
		if (acg_object_[next_idx]->GetDisableFace(i)) continue;
		next_normal = acg_object_[next_idx]->GetNormalVec(i);
		vdot = glm::dot(curr_normal, next_normal);
		if (abs(1.0f - vdot) < 0.0001)
		{
			next_direc = acg_object_[next_idx]->WGetFaceDrcFlag(i);
			break;
		}
	}

	if (next_direc == -1) return false;

	//-- Change next data to curr data for loop 
	*curr_direc_ptr = next_direc;
	*curr_face_cnt_ptr = next_face_cnt;
	*curr_face_ptr = next_face;
	*curr_face_ver_cnt_ptr = next_face_ver_cnt;
	curr_normal_vec = next_normal;
	//-- Consider all face_direc_vec pairs
	// Find curr and next_direc_vec;
	// Direc_vec is direction that the acter can move on the face
	glm::vec3 curr_direc_vec;
	glm::vec3 next_direc_vec;

	// Direc = 0 : a face of cube (face is square)
	// Direc = 1 : find direc vector with face_vertex[0] and face_vertex[1] (face is rectangular)
	// Direc = 2 : find direc vector with face_vertex[1] and face_vertex[2] (face is rectangular)
	if (next_direc == 0)
	{
		path_coord.push_back(inv_vpvp * glm::vec4(FindCenterPos(next_face, next_face_ver_cnt), 1.0f));
		return true;
	}
	if (curr_direc == 0)
	{
		// Find intersection line
		vector<glm::vec3> over_line = FindOverlappingLine(curr_face_ver_cnt, curr_face, next_face_ver_cnt, next_face);
		// Midpoint of line
		path_coord.push_back(inv_vpvp * glm::vec4((over_line[0].x + over_line[1].x) / 2, (over_line[0].y + over_line[1].y) / 2, (over_line[0].z + over_line[1].z) / 2, 1.0f));
		return true;
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
		path_coord.push_back(inv_vpvp * glm::vec4((over_line[0].x + over_line[1].x) / 2, (over_line[0].y + over_line[1].y) / 2, (over_line[0].z + over_line[1].z) / 2, 1.0f));
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
			// if (abs(next_direc_vec.y) < 0.0001) ������ ó����
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
			inter_pos.z = PlaneEquation(glm::cross(glm::vec3(curr_face[3] - curr_face[0], curr_face[4] - curr_face[1], curr_face[5] - curr_face[2]),
				glm::vec3(curr_face[6] - curr_face[0], curr_face[7] - curr_face[1], curr_face[8] - curr_face[2])), curr_center_pos, inter_pos);
			vector<glm::vec3> over_line = FindOverlappingLine(curr_face_ver_cnt, curr_face, next_face_ver_cnt, next_face);

			path_coord.push_back(inv_vpvp * glm::vec4(inter_pos, 1.0f));
			path_coord.push_back(inv_vpvp * glm::vec4((over_line[0].x + over_line[1].x) / 2, (over_line[0].y + over_line[1].y) / 2, (over_line[0].z + over_line[1].z) / 2, 1.0f));
		}
		else
		{
			inter_pos.z = PlaneEquation(glm::cross(glm::vec3(next_face[3] - next_face[0], next_face[4] - next_face[1], next_face[5] - next_face[2]),
				glm::vec3(next_face[6] - next_face[0], next_face[7] - next_face[1], next_face[8] - next_face[2])), next_center_pos, inter_pos);
			path_coord.push_back(inv_vpvp * glm::vec4(inter_pos, 1.0f));
		}
		*curr_direc_ptr = next_direc;
		*curr_face_cnt_ptr = next_face_cnt;
		*curr_face_ptr = next_face;
	}
	return true;
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


			glm::vec3 long_fpos(curr_face[curr_line_fidx * 3], curr_face[curr_line_fidx * 3 + 1], curr_face[curr_line_fidx * 3 + 2]);
			glm::vec3 long_spos(curr_face[curr_line_sidx * 3], curr_face[curr_line_sidx * 3 + 1], curr_face[curr_line_sidx * 3 + 2]);
			glm::vec3 short_fpos(next_face[next_line_fidx * 3], next_face[next_line_fidx * 3 + 1], next_face[next_line_fidx * 3 + 2]);
			glm::vec3 short_spos(next_face[next_line_sidx * 3], next_face[next_line_sidx * 3 + 1], next_face[next_line_sidx * 3 + 2]);

			glm::vec2 long_vec(long_fpos - long_spos);
			glm::vec2 short_vec(short_fpos - short_spos);
			if (glm::length(long_vec) < glm::length(short_vec))
			{
				swap(long_vec, short_vec);
				swap(long_fpos, short_fpos);
				swap(long_spos, short_spos);
			}

			float vdot = glm::dot(glm::normalize(long_vec), glm::normalize(short_vec));
			if (!(abs(1.0f - vdot) < 0.0001 || abs(-1.0f - vdot) < 0.0001)) continue;
			
			float big_x, big_y;
			float small_x, small_y;
			if (long_vec.x == 0)
			{
				if (abs(long_fpos.x - short_fpos.x) > 0.0001) continue;

				big_y = long_fpos.y;
				small_y = long_spos.y;
				if (big_y < small_y)
					swap(big_y, small_y);
				if (small_y <= short_fpos.y && short_fpos.y <= big_y && small_y <= short_spos.y && short_spos.y <= big_y)
				{
					ret.push_back(short_fpos);
					ret.push_back(short_spos);
					return ret;
				}
			}
			else if (long_vec.y == 0)
			{
				if (abs(long_fpos.y - short_fpos.y) > 0.0001) continue;

				big_x = long_fpos.x;
				small_x = long_spos.x;
				if (big_x < small_x)
					swap(big_x, small_x);
				if (small_x <= short_fpos.x && short_fpos.x <= big_x && small_x <= short_spos.x && short_spos.x <= big_x)
				{
					ret.push_back(short_fpos);
					ret.push_back(short_spos);
					return ret;
				}
			}
			else
			{
				float aa = LinearEquation(long_vec, long_fpos, 1, short_fpos.x);
				if (abs(short_fpos.y - LinearEquation(long_vec, long_fpos, 1, short_fpos.x)) > 0.001) continue;

				big_y = long_fpos.y;
				small_y = long_spos.y;
				if (big_y < small_y)
					swap(big_y, small_y);
				big_y += 0.001f;
				small_y -= 0.001f;
				if (!(small_y <= short_fpos.y && short_fpos.y <= big_y && small_y <= short_spos.y && short_spos.y <= big_y)) continue;

				big_x = long_fpos.x;
				small_x = long_spos.x;
				if (big_x < small_x)
					swap(big_x, small_x);
				big_x += 0.001f;
				small_x -= 0.001f;

				if (!(small_x <= short_fpos.x && short_fpos.x <= big_x && small_x <= short_spos.x && short_spos.x <= big_x)) continue;

				ret.push_back(short_fpos);
				ret.push_back(short_spos);
				return ret;
			}
		}
	}

	//there is no overlapping line segments, error
	return ret;
}

void Level::ChkDisableFace()
{
	for (int i = 0; i < acg_cnt_; i++)
	{
		for (int j = i + 1; j < acg_cnt_; j++)
		{
			if (edge[i][j] == 0)continue;
			CmpTwoObj(i, j);
		}
	}
}

void Level::CmpTwoObj(int fobj_idx, int sobj_idx)
{
	float* fobj_face = acg_object_[fobj_idx]->GetCurrFaceVer();
	int fobj_face_cnt = acg_object_[fobj_idx]->GetFaceCnt();
	int fobj_face_ver_cnt = acg_object_[fobj_idx]->GetFaceVerCnt();
	float* sobj_face = acg_object_[sobj_idx]->GetCurrFaceVer();
	int sobj_face_cnt = acg_object_[sobj_idx]->GetFaceCnt();
	int sobj_face_ver_cnt = acg_object_[sobj_idx]->GetFaceVerCnt();

	for (int i = 0; i < fobj_face_cnt; i++, fobj_face += 3 * fobj_face_ver_cnt)
	{
		glm::vec3 fobj_nrm = acg_object_[fobj_idx]->GetNormalVec(i);
		glm::vec3 fobj_center = FindCenterPos(fobj_face, fobj_face_ver_cnt);

		sobj_face = acg_object_[sobj_idx]->GetCurrFaceVer();
		for (int j = 0; j < sobj_face_cnt; j++, sobj_face += 3 * sobj_face_ver_cnt)
		{
			glm::vec3 sobj_nrm = acg_object_[sobj_idx]->GetNormalVec(j);
			float vdot = glm::dot(fobj_nrm, sobj_nrm);
			if (abs(-1.0f - vdot) > 0.001) continue;

			glm::vec3 sobj_center = FindCenterPos(sobj_face, sobj_face_ver_cnt);
			if (glm::length(fobj_center - sobj_center) > 0.001) continue;

			acg_object_[fobj_idx]->SetDisableFace(i, true);
			acg_object_[sobj_idx]->SetDisableFace(j, true);
			break;
		}
	}
}

bool Level::ChkActorOnObj(vector<int> obj_idx)
{
	int size = (int)obj_idx.size();
	for (int i = 0; i < size; i++)
	{
		if (obj_idx[i] == obj_on_acter)
			return true;
	}
	return false;
}