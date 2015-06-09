#include "Plane.h"

Plane::Plane(GLuint width, GLuint height) : Object(){
	//BuildTriangleStrip(this->width = width, this->height = height);
	BuildTriangles(this->width = width, this->height = height);
}

Plane::~Plane(){
	
}