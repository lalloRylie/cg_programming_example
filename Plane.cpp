#include "Plane.h"

Plane::Plane(GLuint width, GLuint height) : Object(){
	BuildTriangles(this->width = width, this->height = height);
	//LoadTriangles(this->width = width, this->height = height,	GL_TRIANGLES);
}

Plane::~Plane(){
	
}