#include "Pacman.h"


void Pacman::update(std::shared_ptr<GameState> gameState, CollisionManager collisionManager)
{
	//husk forrige velocity
	int lastVelocity[2] = { velocity[0], velocity[1] };
	//InputManager
	m_input.update(window, velocity, gameState);
	EntityType collisionCheck = collisionManager.collisionCheck(this);
	//Hva traff jeg?

	if (collisionCheck == EntityType::GHOST)
		std::cout << "HELLO" << std::endl;
	//collision check må inn her
	//Spørre hva pacman traff?
	 //type = CollisionManager().collisionCheck(this);


	
	switch (collisionCheck)
	{
	case EntityType::GHOST:
		deathAnimation.render(coordinates[0], coordinates[1]);
		//gameState = GameState::GAME_OVER;
		break;
	case EntityType::WALL:
		break;
	case EntityType::AFRAID_GHOST:
		break;
	case EntityType::PELLET:
		break;
	case EntityType::POWER_PELLET:
		break;
	case EntityType::FRUIT:
		break;
	case EntityType::TELEPORT:
		break;
	default:
		break;
	}



	
	coordinates[0] += velocity[0];
	coordinates[1] += velocity[1];


	if (velocity[0] > 0) {
		rightAnimation.render(coordinates[0], coordinates[1]);
	}
	else if (velocity[0] < 0) {
		leftAnimation.render(coordinates[0], coordinates[1]);
	}
	else if (velocity[1] > 0) {
		downAnimation.render(coordinates[0], coordinates[1]);
	}
	else if (velocity[1] < 0) {
		upAnimation.render(coordinates[0], coordinates[1]);
	}
	else {
		startAnimation.render(coordinates[0], coordinates[1]);
	}

	//Checks the direction pacman is traveling




	Entity::update();

}

Pacman::Pacman(SDL_Renderer* renderer, SDL_Window* w, SDL_Surface* mainSpriteSheet) : Entity(renderer, 100, 100, 3, mainSpriteSheet), window(w) {


	setEntityType(EntityType::PACMAN);


	rightAnimation.addRect(457, 1, 9, 14);
	rightAnimation.addRect(473, 1, 12, 14);
	rightAnimation.addRect(489, 1, 13, 13);

	leftAnimation.addRect(459, 17, 13, 13);
	leftAnimation.addRect(474, 17, 13, 13);
	leftAnimation.addRect(489, 1, 13, 13);

	upAnimation.addRect(457, 33, 13, 13);
	upAnimation.addRect(473, 33, 13, 13);
	upAnimation.addRect(489, 1, 13, 13);

	downAnimation.addRect(457, 48, 13, 13);
	downAnimation.addRect(473, 48, 13, 13);
	downAnimation.addRect(489, 1, 13, 13);

	startAnimation.addRect(489, 1, 13, 13);
	startAnimation.addRect(489, 1, 13, 13);
	startAnimation.addRect(489, 1, 13, 13);


}

Pacman::~Pacman()
{
}


