#include "../headerFile/Shape.h"

const string Shape::ShapeTypeName[] = {
		"NONE",
		"AXES",
		"CUBE",
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

void Shape::SetCanBeLocated(bool can_be_located) { can_be_located_ = can_be_located; }
void Shape::SetIsFixed(bool isfixed) { isfixed_ = isfixed; }
void Shape::SetIsDirty(bool isdirty) { isdirty_ = isdirty; }
bool Shape::GetCanBeLocated() { return can_be_located_; };
bool Shape::GetIsFixed() { return isfixed_; }
bool Shape::GetIsDirty() { return isdirty_; }

void Shape::Draw(glm::mat4 model) { cout << ShapeTypeName[type_] << " don't Draw\n"; }
void Shape::MakeBuffer() { cout << ShapeTypeName[type_] << " don't MakeBuffer\n"; }
void Shape::MakeFaceVertex() { cout << ShapeTypeName[type_] << " don't MakeFaceVertex\n"; }
void Shape::FreeVertex() { cout << ShapeTypeName[type_] << " don't need FreeVertex\n"; }
float* Shape::IsOnShape(glm::vec3) { cout << ShapeTypeName[type_] << " don't use IsOnFace\n"; return 0; }