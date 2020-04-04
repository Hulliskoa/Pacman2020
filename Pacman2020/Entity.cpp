#include "Entity.h"

void Entity::setVelocity(int x, int y) {
	velocity[0] = 0;
	velocity[1] = 0;
}

void Entity::setCoordinates(int* newCoordinates)
{
	coordinates[0] = newCoordinates[0];
	coordinates[1] = newCoordinates[1];
}

void Entity::setEntityType(entityType type)
{
	entityT = type;
}

entityType Entity::getEntityType()
{
	return entityT;
}

void Entity::update(SDL_Window* window) {}

int* Entity::getNewLocation() {
	return nullptr;
}



Entity::Entity(SDL_Renderer* renderer, int x, int y): velocity{0,0}, coordinates{x,y}
{
	leftAnimation = AnimationComponent(renderer, "..\\Pacman2020\\sprites\\spritesheet.png", 3);
	rightAnimation = AnimationComponent(renderer, "..\\Pacman2020\\sprites\\spritesheet.png", 3);
	upAnimation = AnimationComponent(renderer, "..\\Pacman2020\\sprites\\spritesheet.png", 3);
	downAnimation = AnimationComponent(renderer, "..\\Pacman2020\\sprites\\spritesheet.png", 3);
	startAnimation = AnimationComponent(renderer, "..\\Pacman2020\\sprites\\spritesheet.png", 1);


	if (!leftAnimation.loadFromFile("..\\Pacman2020\\sprites\\spritesheet.png"))
	{
		printf("Failed to load sprite sheet texture!\n");

	}
	if (!rightAnimation.loadFromFile("..\\Pacman2020\\sprites\\spritesheet.png"))
	{
		printf("Failed to load sprite sheet texture!\n");

	}
	if (!upAnimation.loadFromFile("..\\Pacman2020\\sprites\\spritesheet.png"))
	{
		printf("Failed to load sprite sheet texture!\n");

	}
	if (!downAnimation.loadFromFile("..\\Pacman2020\\sprites\\spritesheet.png"))
	{
		printf("Failed to load sprite sheet texture!\n");

	}
}

Entity::Entity() :coordinates{ 0,0 }, velocity{ 0,0 } {}

