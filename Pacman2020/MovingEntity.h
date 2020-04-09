#pragma once

#include "Entity.h"






class MovingEntity : public Entity
{

protected:
	int numFrames = 0;

public:
	//current direction the entity is travelling element 0 = x-plane and element 1 = y-plane.
	int velocity[2];

	std::shared_ptr<AnimationComponent> leftAnimation;
	std::shared_ptr<AnimationComponent>  rightAnimation;
	std::shared_ptr<AnimationComponent>  upAnimation;
	std::shared_ptr<AnimationComponent>  downAnimation;
	std::shared_ptr<AnimationComponent>  startAnimation;

	virtual void setVelocity(int x, int y);
	virtual void update();

	MovingEntity(SDL_Renderer* renderer, int x, int y, int numAnimFrames, SDL_Surface* mainSpriteSheet);
	MovingEntity();

};

