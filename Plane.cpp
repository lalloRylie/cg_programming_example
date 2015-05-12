#include "Plane.h"

Plane::Plane(GLuint width, GLuint height) : Object(){
	LoadTriangles(this->width = width, this->height = height,
		GL_TRIANGLE_STRIP);
}

Plane::~Plane(){
	
}