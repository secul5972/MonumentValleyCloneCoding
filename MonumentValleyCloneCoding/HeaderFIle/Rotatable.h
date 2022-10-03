#ifndef	ROTATABLE_H
#define ROTATABLE_H

#include <glm/glm.hpp>

class Rotatable
{
protected:

	//need to update face vertex position
	bool			isdirty_ = true;
	//current model matrix
	glm::mat4		model_;
public:

	void			SetIsDirty(bool isdirty);

	// isfixed_ == false
	virtual void	UpdateObjData(glm::mat4) = 0;
};

#endif