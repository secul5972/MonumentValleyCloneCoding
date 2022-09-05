#include "../headerFile/AdditionalMathFunction.h"

std::ostream& operator<<(std::ostream& o, glm::mat4& mat)
{
	for (int i = 0; i < 4; i++)
	{
		o << '|';
		for (int j = 0; j < 4; j++)
		{
			std::cout.width(10);
			o << mat[j][i] << "\t";
		}
		o << "|\n";
	}
	return o;
}

std::ostream& operator<<(std::ostream& o, glm::mat3& mat)
{
	for (int i = 0; i < 3; i++)
	{
		o << '|';
		for (int j = 0; j < 3; j++)
		{
			std::cout.width(10);
			o << mat[j][i] << "\t";
		}
		o << "|\n";
	}
	return o;
}

std::ostream& operator<<(std::ostream& o, glm::vec4& vec)
{
	std::cout.width(10);
	o << vec.x << '\t' << vec.y << '\t' << vec.z << '\t' << vec.w;
	return o;
}

std::ostream& operator<<(std::ostream& o, glm::vec3& vec)
{
	std::cout.width(10);
	o << vec.x << '\t' << vec.y << '\t' << vec.z;
	return o;
}

std::ostream& operator<<(std::ostream& o, glm::vec2& vec)
{
	std::cout.width(10);
	o << vec.x << '\t' << vec.y;
	return o;
}
