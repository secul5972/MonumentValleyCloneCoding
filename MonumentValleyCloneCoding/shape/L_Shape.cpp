#include "../headerFIle/Shape.h"

extern unsigned int cuboid_tri_VAO, cuboid_line_VAO, cube_tri_VAO, cube_line_VAO;
extern glm::mat4 projection, view, model;

void prepare_L_shape()
{
#ifndef P_CUBE
	prepare_cube();
#endif
#ifndef P_CUBOID
	prepare_cuboid();
#endif
}

void draw_L_shape(Shader sh)
{
	//cube
	glm::mat4 shapeModel;
	sh.use();
	sh.setMat4("projection", projection);
	sh.setMat4("view", view);

	shapeModel = model;
	shapeModel = glm::scale(shapeModel, glm::vec3(1.0f, 1.0f, 1.0f));
	sh.setMat4("model", shapeModel);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(cube_tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(cube_line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);

	//cuboid
	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.5f, 0.0f, 0.0f));
	sh.setMat4("model", shapeModel);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(cuboid_tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(cuboid_line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);

	shapeModel = model;
	shapeModel = glm::translate(shapeModel, glm::vec3(0.0f, 0.0f, 0.5f));
	shapeModel = glm::rotate(shapeModel, glm::radians((float)90), glm::vec3(0.0f, 1.0f, 0.0f));
	sh.setMat4("model", shapeModel);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 0.5f, 0.2f));
	glBindVertexArray(cuboid_tri_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	sh.setVec3("ObjectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(cuboid_line_VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	glDrawArrays(GL_LINE_STRIP, 4, 4);
	glDrawArrays(GL_LINE_STRIP, 8, 4);
	glDrawArrays(GL_LINE_STRIP, 12, 4);
	sh.unuse();
}