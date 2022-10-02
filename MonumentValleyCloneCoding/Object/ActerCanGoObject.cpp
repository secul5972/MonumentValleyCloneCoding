#include "../headerFile/ActerCanGoObject.h"

ActerCanGoObject::ActerCanGoObject(ShapeType shape_type, bool can_be_located_) :Shape(shape_type, can_be_located_) {}
ActerCanGoObject::~ActerCanGoObject() {}

void		ActerCanGoObject::SetIsFixed(bool isfixed) { isfixed_ = isfixed; }