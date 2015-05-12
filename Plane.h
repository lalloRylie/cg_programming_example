#include "Application.h"
#include "Object.h"

#pragma once

class Plane : public Object{

	public:
		Plane(GLuint width, GLuint height);
		virtual ~Plane();

	private:
		GLuint width, height;
};