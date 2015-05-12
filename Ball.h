#include "Object.h"

#pragma once

class Ball : public Object{
	
	public:
		Ball();
		~Ball();

		void Update(const float& deltaTime);

		vec3 GetVelocity();
		void SetVelocity(vec3 velocity);

	private:
		vec3 velocity;
};