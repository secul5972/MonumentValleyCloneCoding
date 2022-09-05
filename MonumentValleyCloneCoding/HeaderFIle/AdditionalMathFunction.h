#ifndef ADDITIONALMATHFUNCTION_H
#define ADDITIONALMATHFUNCTION_H

#include <glm/glm.hpp>
#include <iostream>

std::ostream& operator<<(std::ostream& o, glm::mat4& mat);
std::ostream& operator<<(std::ostream& o, glm::mat3& mat);
std::ostream& operator<<(std::ostream& o, glm::vec4& vec);
std::ostream& operator<<(std::ostream& o, glm::vec3& vec);
std::ostream& operator<<(std::ostream& o, glm::vec2& vec);

#endif
