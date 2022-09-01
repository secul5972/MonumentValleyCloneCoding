#include "../headerFIle/Shape.h"

class Cube:Shape {
public:
	virtual bool prepare();
	virtual void draw(Shader sh);
};

extern glm::mat4 projection, view, worldModel;
