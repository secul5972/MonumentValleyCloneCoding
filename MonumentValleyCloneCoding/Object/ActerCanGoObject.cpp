#include "../headerFile/ActerCanGoObject.h"

ActerCanGoObject::ActerCanGoObject(ShapeType shape_type, bool can_be_located_) :Shape(shape_type, can_be_located_) {}
ActerCanGoObject::~ActerCanGoObject() {}

void		ActerCanGoObject::SetIsFixed(bool isfixed) { isfixed_ = isfixed; }
void		ActerCanGoObject::SetDisableFace(int idx, bool val) { disable_face_[idx] = val; }
bool		ActerCanGoObject::GetDisableFace(int idx) { return disable_face_[idx]; }
void		ActerCanGoObject::SetObjColor(glm::vec3 obj_color) { obj_color_ = obj_color; }
