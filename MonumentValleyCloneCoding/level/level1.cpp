#include "../headerFile/Level.h"

double rotateStartTime = 0;
double rotateEndTime = -1;
double rotateCurrTime = 0;
double l_shape_angle = 0;
int shape = 0;

EllipseArea* ellipse_area;
glm::mat4 ellipse_area_model;
bool l_shape_moving_flag = false;
glm::vec2 prev_mouse_pos_in_model;
extern Level1* level1;

extern float line_vertices[2][3];

Level1::Level1(): aligned_pos(glm::vec3(0.0f, 0.0f, 0.0f)), character_pos(glm::vec3(0.0f, -0.3f, 1.2f))
{
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
	float*		face = 0;
	float		depth = 1;
	int			type = 0;
	int			face_ver_cnt = 0;
	int			direction = 0;

	for (int i = 0; i < size; i++)
	{
		float*	curr_face;
		float	curr_depth;
		int		curr_direction;

		if (shapes[i]->GetCanBeLocated() == false) continue;
		if ((curr_face = shapes[i]->InShape(point, &curr_direction)))
		{
			curr_depth = AverDepth(curr_face, shapes[i]->GetFaceVerCnt());
			if (curr_depth > depth) continue;
			face = curr_face;
			depth = curr_depth;
			direction = curr_direction;
			face_ver_cnt = shapes[i]->GetFaceVerCnt();
			type = (int)shapes[i]->GetShapeType();
		}
	}

	printf("type: %d\n", type);
	printf("direction: %d\n", direction);

	aligned_pos = AlignPos(face, direction, point, face_ver_cnt);

	printf("aligned_pos: %f %f\n", aligned_pos.x, aligned_pos.y);
	PrintFace(face, face_ver_cnt);

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