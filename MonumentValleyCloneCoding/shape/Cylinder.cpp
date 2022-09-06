#include "../headerFile/Shape.h"

extern float* circle_vertex;
extern int circle_vertex_cnt;

//Cylinder::Cylinder()
//{
//	if (circle_vertex == 0)
//		MakeCircleVertex();
//
//	glGenBuffers(1, &line_VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2172, circle_vertex, GL_STATIC_DRAW);
//
//	glGenVertexArrays(1, &line_VAO);
//	glBindVertexArray(line_VAO);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//
//}