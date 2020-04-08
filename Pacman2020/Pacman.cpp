#include "Pacman.h"


void Pacman::update(std::shared_ptr<GameState> gameState, std::shared_ptr<CollisionManager> collisionManager)
{
	// Saves last direction pacman traveled in.
	int lastVelocity[2] = { velocity[0], velocity[1] };
	//InputManager
	m_input.update(window, velocity, gameState);
	
	//Hva traff jeg?

	//collision check må inn her
	//Spørre hva pacman traff?
	 //type = CollisionManager().collisionCheck(this);


	std::shared_ptr<Entity>  collidedWith = collisionManager->collisionCheck(this);
	if (collidedWith != nullptr) {
		switch (collidedWith->getEntityType())
		{
		case EntityType::GHOST:
			//deathAnimation.render(coordinates[0], coordinates[1]);
			//gameState = GameState::GAME_OVER;
			break;
		case EntityType::WALL:
			if ((velocity[0] == lastVelocity[0]) || (velocity[1] == lastVelocity[1])) {
				lastAnimation->render(coordinates[0], coordinates[1]);
			}
			else {
				coordinates[0] += lastVelocity[0];
				coordinates[1] += lastVelocity[1];
			}

			//Stoppe
			break;
		case EntityType::AFRAID_GHOST:
			//Legg til poeng
			//Animere som øyne
			//Søke tilbake til huset
			break;
		case EntityType::PELLET:
			//Legg til poeng
			//Forsvinne fra kartet
			break;
		case EntityType::POWER_PELLET:
			//Legg til poeng
			////Animere til blått spøkelse
			//Starte timer
			//Ghost skal løpe vekk fra pacman
			break;
		case EntityType::FRUIT:
			//Legg til poeng
			//Fjerne fra kart
			break;
		case EntityType::TELEPORT:
			//Endre koordinat
			break;
		default:
			break;
		}
	}
	else {
		coordinates[0] += velocity[0];
		coordinates[1] += velocity[1];
	}




	if (velocity[0] > 0) {
		lastAnimation = rightAnimation;
		rightAnimation->render(coordinates[0], coordinates[1]);

	}
	else if (velocity[0] < 0) {
		lastAnimation = leftAnimation;
		leftAnimation->render(coordinates[0], coordinates[1]);

	}

	else if (velocity[1] > 0) {
		lastAnimation = downAnimation;
		downAnimation->render(coordinates[0], coordinates[1]);

	}
	else if (velocity[1] < 0) {
		lastAnimation = upAnimation;
		upAnimation->render(coordinates[0], coordinates[1]);

	}
	else {
		startAnimation->render(coordinates[0], coordinates[1]);
	}

	//Checks the direction pacman is traveling




	Entity::update();

}

Pacman::Pacman(SDL_Renderer* renderer, SDL_Window* w, SDL_Surface* mainSpriteSheet) : Entity(renderer, 100, 100, 3, mainSpriteSheet), window(w) {


	setEntityType(EntityType::PACMAN);


	rightAnimation->addRect(457, 1, 9, 14);
	rightAnimation->addRect(473, 1, 12, 14);
	rightAnimation->addRect(489, 1, 13, 13);

	leftAnimation->addRect(459, 17, 13, 13);
	leftAnimation->addRect(474, 17, 13, 13);
	leftAnimation->addRect(489, 1, 13, 13);

	upAnimation->addRect(457, 33, 13, 13);
	upAnimation->addRect(473, 33, 13, 13);
	upAnimation->addRect(489, 1, 13, 13);

	downAnimation->addRect(457, 48, 13, 13);
	downAnimation->addRect(473, 48, 13, 13);
	downAnimation->addRect(489, 1, 13, 13);

	startAnimation->addRect(489, 1, 13, 13);
	startAnimation->addRect(489, 1, 13, 13);
	startAnimation->addRect(489, 1, 13, 13);


}

Pacman::~Pacman()
{
}


