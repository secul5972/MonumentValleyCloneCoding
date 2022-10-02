#include "../headerFile/Shape.h"



Shape::Shape() : type_(DEFAULT), can_be_located_(false) {};
Shape::Shape(ShapeType type = DEFAULT, bool can_be_located = false) : type_(type), can_be_located_(can_be_located) {};

void		Shape::SetCanBeLocated(bool can_be_located) { can_be_located_ = can_be_located; }
bool		Shape::GetCanBeLocated() { return can_be_located_; };
void		Shape::SetIsFixed(bool isfixed) { isfixed_ = isfixed; }