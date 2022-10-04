#include "../headerFile/Ornament.h"

Ornament::Ornament(ShapeType shape_type, bool can_be_located_) :Shape(shape_type, can_be_located_) {}
Ornament::~Ornament() {};
void		Ornament::SetObjColor(glm::vec3 obj_color) { obj_color_ = obj_color; }
