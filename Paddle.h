#include "Object.h"

#pragma once

#define NO_KEY -2

class Paddle : public Object{
	
	public:
		Paddle();
		~Paddle();

		void Update(const float& deltaTime);
		void SetKeys(const int& upKey, const int&downKey);

	private:
		int upKey, downKey;
};