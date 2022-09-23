#include "../headerFile/Shape.h"

GLuint Goal::tri_VAO, Goal::tri_VBO, Goal::line_VAO, Goal::line_VBO;
float* Goal::base_face_vertex_;
glm::mat4 Goal::pre_model_;

extern float cube_face_ver[];

Goal::Goal() : Shape(GOAL, true, true)
{
	curr_face_vertex_ = new float[Cube::cube_face_ver_size];
}

Goal::~Goal()
{
	delete []curr_face_vertex_;
}

void Goal::MakeBuffer()
{
	float* goal_tri_ver = new float[216];
	float* goal_line_ver = new float[48];

	glm::mat4 shapeModel(1.0f);
	shapeModel = glm::scale(shapeModel, glm::vec3(1.5f, 0.2f, 1.5f));
	shapeModel = glm::translate(shapeModel, glm::vec3(0.1f, -0.1f, 0.0f));
	pre_model_ = shapeModel;

	for (int i = 0; i < 36; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_tri_ver[i * 6];
		tmp.y = cube_tri_ver[i * 6 + 1];
		tmp.z = cube_tri_ver[i * 6 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_tri_ver[i * 6] = ret.x;
		goal_tri_ver[i * 6 + 1] = ret.y;
		goal_tri_ver[i * 6 + 2] = ret.z;

		tmp.x = cube_tri_ver[i * 6 + 3];
		tmp.y = cube_tri_ver[i * 6 + 4];
		tmp.z = cube_tri_ver[i * 6 + 5];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_tri_ver[i * 6 + 3] = ret.x;
		goal_tri_ver[i * 6 + 4] = ret.y;
		goal_tri_ver[i * 6 + 5] = ret.z;
	}

	for (int i = 0; i < 16; i++)
	{
		glm::vec3 tmp, ret;
		tmp.x = cube_face_ver[i * 3];
		tmp.y = cube_face_ver[i * 3 + 1];
		tmp.z = cube_face_ver[i * 3 + 2];
		ret = glm::vec3(shapeModel * glm::vec4(tmp, 1.0f));
		goal_line_ver[i * 3] = ret.x;
		goal_line_ver[i * 3 + 1] = ret.y;
		goal_line_ver[i * 3 + 2] = ret.z;
	}

	//triangle
	glGenBuffers(1, &tri_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, tri_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 216, goal_tri_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &tri_VAO);
	glBindVertexArray(tri_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//line
	glGenBuffers(1, &line_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 48, goal_line_ver, GL_STATIC_DRAW);

	glGenVertexArrays(1, &line_VAO);
	glBindVertexArray(line_VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	delete []goal_tri_ver;
	delete []goal_line_ver;
	base_face_vertex_ = cube_face_ver;
}

void Goal::Draw(glm::mat4 model)
{
	glm::mat4 shapeModel;

	def_shader->use();
	shapeModel = model;
	def_shader->setMat4("model", shapeModel);
	def_shader->setMat4("projection", projection);
	def_shader->setMat4("view", view);
	def_shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	def_shader->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);
	def_shader->unuse();
}

float* Goal::InShape(glm::vec2 point)
{
	int size = Cube::cube_face_ver_size / (Cube::cube_face_ver_cnt * 3);
	float* face = 0;

	for (int i = 0; i < size; i++)
	{
		//check per face
		//printf("\ngoal\n");
		if (OnFace(point, curr_face_vertex_ + i * Cube::cube_face_ver_cnt * 3, Cube::cube_face_ver_cnt))
		{
			face = curr_face_vertex_ + i * Cube::cube_face_ver_cnt * 3;
			break;
		}
	}

	//if face == 0, point is not in shape
	if (!face)
		return 0;

	return face;
}

void Goal::SaveModelData(glm::mat4 model)
{
	if (isfixed_ && issaved_) return;
	if (!isfixed_ && !isdirty_) return;
	model_ =  model * pre_model_;

	glm::mat4 matrix = viewport * projection * view * model_;
	for (int i = 0; i < Cube::cube_face_ver_size / 3; i++)
	{
		glm::vec3 prev, curr;
		prev = glm::vec3(base_face_vertex_[i * 3], base_face_vertex_[i * 3 + 1], base_face_vertex_[i * 3 + 2]);
		curr = matrix * glm::vec4(prev, 1.0f);
		curr_face_vertex_[i * 3] = curr.x;
		curr_face_vertex_[i * 3 + 1] = curr.y;
		curr_face_vertex_[i * 3 + 2] = curr.z;
	}
}