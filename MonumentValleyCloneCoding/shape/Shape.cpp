#include "../headerFile/Shape.h"

const string Shape::kShapeTypeName[] = {
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

const glm::vec3 Shape::kFaceAxes[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(-1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, -1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, -1.0f),
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f)
};

const glm::vec3 Shape::kFaceFactor[] = {
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 0.0f)
};

void Shape::SetCanBeLocated(bool can_be_located) { can_be_located_ = can_be_located; }
void Shape::SetIsFixed(bool isfixed) { isfixed_ = isfixed; }
void Shape::SetIsDirty(bool isdirty) { isdirty_ = isdirty; }
bool Shape::GetCanBeLocated() { return can_be_located_; };
bool Shape::GetIsFixed() { return isfixed_; }
bool Shape::GetIsDirty() { return isdirty_; }

void Shape::Draw(glm::mat4 model) { cout << kShapeTypeName[type_] << " don't Draw\n"; }
void Shape::MakeBuffer() { cout << kShapeTypeName[type_] << " don't MakeBuffer\n"; }
void Shape::MakeFaceVertex() { cout << kShapeTypeName[type_] << " don't MakeFaceVertex\n"; }
void Shape::FreeVertex() { cout << kShapeTypeName[type_] << " don't need FreeVertex\n"; }
float* Shape::IsOnShape(glm::vec3) { cout << kShapeTypeName[type_] << " don't use IsOnFace\n"; return 0; }

bool Shape::IsOnFace(glm::vec3 point, float* face, GLuint face_vertex_cnt)
{
	FaceType ft = NONE;

	glm::vec3 vecA(face[0], face[1], face[2]);
	glm::vec3 vecB(face[3], face[4], face[5]);
	glm::vec3 vecC(face[6], face[7], face[8]);
	glm::vec3 normal = glm::cross(vecB - vecA, vecC - vecA);

	// Is normal of face parallel to axes?
	for (int i = 1; i <= kFaceTypeCnt; i++)
	{
		if (glm::dot(normal, kFaceAxes[i]) > 0)
		{
			ft = FaceType(i);
			break;
		}
	}

	if (ft == NONE)
		return 0;

	// Is the vector component in normal direction equal to the point?
	if (glm::dot(kFaceAxes[ft], vecA) != glm::dot(kFaceAxes[ft], point))
		return 0;

	//점이 평면 내부인지 검사

	return 1;
}