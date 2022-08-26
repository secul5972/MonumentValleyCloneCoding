#include "../headerFIle/Shape.h"

unsigned int slope_tri_VAO, slope_tri_VBO, slope_line_VAO, slope_line_VBO;
extern glm::mat4 projection, view, worldModel;

void prepare_slope()
{
#ifndef _slope
#define P_slope
#endif
}

void draw_slope(Shader sh)
{
	glm::mat4 shapeModel;

	sh.use();
	shapeModel = worldModel;
	shapeModel = glm::scale(shapeModel, glm::vec3(1.0f, 1.0f, 1.0f));
	sh.setMat4("model", shapeModel);
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);
	sh.setVec3("ObjectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(slope_tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(slope_line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);
	sh.unuse();
}