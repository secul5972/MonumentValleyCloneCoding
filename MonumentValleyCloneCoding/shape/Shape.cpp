#include "../headerFile/Shape.h"

const string Shape::kShapeTypeName[] = {
	"DEFAULT",
	"AXES",
	"CUBE",
	"CUBOID",
	"GOAL",
	"L_SHAPE",
	"SLOPE",
	"CIRCLE",
	"CYLINDER",
	"RORTARY_KNOB",
	"CORN",
	"SPHERE",
	"CHARACTER"
};

Shape::Shape(ShapeType type = DEFAULT, bool can_be_located = false, bool isfixed = true) : type_(type), can_be_located_(can_be_located), isfixed_(isfixed), model_(glm::mat4(1.0f)) {};

void		Shape::SetCanBeLocated(bool can_be_located) { can_be_located_ = can_be_located; }
void		Shape::SetIsFixed(bool isfixed) { isfixed_ = isfixed; }
void		Shape::SetIsDirty(bool isdirty) { isdirty_ = isdirty; }
bool		Shape::GetCanBeLocated() { return can_be_located_; };
int			Shape::GetShapeType() { return type_; };
bool		Shape::GetIsFixed() { return isfixed_; }
bool		Shape::GetIsDirty() { return isdirty_; }

void		Shape::Draw(glm::mat4 model) { cout << kShapeTypeName[type_] << " don't Draw\n"; }
void		Shape::MakeBuffer() { cout << kShapeTypeName[type_] << " don't MakeBuffer\n"; }
void		Shape::MakeFaceVertex() { cout << kShapeTypeName[type_] << " don't MakeFaceVertex\n"; }
void		Shape::FreeVertex() { cout << kShapeTypeName[type_] << " don't need FreeVertex\n"; }
float*		Shape::InShape(glm::vec2, int*) { /*cout << kShapeTypeName[type_] << " don't use InShape\n";*/ return 0; }
void		Shape::SaveModelData(glm::mat4) { cout << kShapeTypeName[type_] << " don't use SaveModelData\n"; }
const int	Shape::GetFaceVerCnt() { cout << kShapeTypeName[type_] << " don't use SaveModelData\n"; return 0; };