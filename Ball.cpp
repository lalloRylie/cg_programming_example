#include "Ball.h"

Ball::Ball() : Object(){
	BuildTriangles(2, 0);
	SetScale(vec3(0.025f));
	SetVelocity(vec3(1.0f, 0.0f, 0.0f));
}

Ball::~Ball(){

}

void Ball::Update(const float& deltaTime){
	position += velocity * deltaTime;

	Object::Update(deltaTime);
}

vec3 Ball::GetVelocity(){
	return velocity;
}

void Ball::SetVelocity(vec3 velocity){
	this->velocity = velocity;
}