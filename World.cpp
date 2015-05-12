#include "World.h"

//TODO: Add functionality later...
World::World(){
	plane = new Plane(1, 1);
}

//TODO: Add functionality later...
World::~World(){
	delete plane;
	plane = NULL;
}

void World::Update(const float& deltaTime){

	plane->Update(deltaTime);
}

void World::Render(const Camera& camera){
	plane->Render(camera);
}