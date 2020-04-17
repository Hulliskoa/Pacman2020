#include "Pacman.h"


void Pacman::update(std::shared_ptr<GameState> gameState, std::shared_ptr<CollisionManager> collisionManager, SDL_Renderer* renderer)
{

	// Saves last direction pacman traveled in.
	int lastVelocity[2] = { velocity[0], velocity[1] };

	//Death animation and handling
	if (*gameState == GameState::PACMAN_DIED) {
		deathAnimation->render(coordinates[0], coordinates[1], renderer);

		if (deathAnimation->getCurrentFrame() == deathAnimation->getTotalFrames() - 1) {
			if (getRemainingLives() < 0) {
				*gameState = GameState::GAME_OVER;
			}
			else {
				*gameState = GameState::RESTART_LEVEL;
			}
		}
	}
	else {
		std::shared_ptr<Entity>  collidedWith = collisionManager->collisionCheck(shared_from_this());
		if (collidedWith != nullptr) {
			switch (collidedWith->getEntityType())
			{
			case EntityType::GHOST:
				std::cout << "hit ghost" << std::endl;
				if (*gameState == GameState::GAME_RUNNING_FLEE || *gameState == GameState::GAME_RUNNING_FLEE_ENDING) {
					std::cout << "hit scared ghost" << std::endl;
					collidedWith->setEntityType(EntityType::GHOST_EYES);


					//Score increase for each ghost pacman eats
					pointDoubler = pointDoubler * 2;
					score += ghostPoints * pointDoubler;
					if (pointDoubler == 0) {
						pointDoubler = 2;
					}
				}
				else {
					pointDoubler = 2;
					*gameState = GameState::PACMAN_DIED;
					std::cout << "hit ghost" << std::endl;
					remainingLife--;

				}

				break;
			case EntityType::WALL:
				if ((velocity[0] != lastVelocity[0]) || (velocity[1] != lastVelocity[1])) {
					velocity[0] = lastVelocity[0];
					velocity[1] = lastVelocity[1];
					lastAnimation->render(coordinates[0], coordinates[1], renderer);
				}
				else {
					lastAnimation->render(coordinates[0], coordinates[1], renderer);
					velocity[0] = 0;
					velocity[1] = 0;
				}
				break;
			case EntityType::PELLET:
				collidedWith->setEntityType(EntityType::INACTIVE_PELLET);
				score += 10;
				//Legg til poeng
				//Forsvinne fra kartet
				break;
			case EntityType::POWER_PELLET:
				*gameState = GameState::GAME_RUNNING_FLEE;
				collidedWith->setEntityType(EntityType::INACTIVE_POWER_PELLET);
				score += 50;
				ghostPoints = 100;
				////Animere til blått spøkelse
				//Starte timer
				//Ghost skal løpe vekk fra pacman
				break;
			case EntityType::FRUIT:
				//Legg til poeng
				collidedWith->setEntityType(EntityType::INACTIVE_FRUIT);
				score += 50;
				break;
			case EntityType::TELEPORT:
				//Endre koordinat
				break;
			case EntityType::INTERSECTION:
				//Endre koordinat
				break;
			case EntityType::DOOR:
				if ((velocity[0] != lastVelocity[0]) || (velocity[1] != lastVelocity[1])) {
					velocity[0] = lastVelocity[0];
					velocity[1] = lastVelocity[1];
					lastAnimation->render(coordinates[0], coordinates[1], renderer);
				}
				else {

					lastAnimation->render(coordinates[0], coordinates[1], renderer);
					velocity[0] = 0;
					velocity[1] = 0;
				}
				break;
			default:
				break;
			}
		}
		else {

		}
		coordinates[0] += velocity[0];
		coordinates[1] += velocity[1];

		if (collisionManager->checkIntersection(shared_from_this())) {
			m_input->update(velocity, gameState);
		}




		//Checks the direction pacman is traveling
		if (velocity[0] > 0) {
			lastAnimation = rightAnimation;
			rightAnimation->render(coordinates[0], coordinates[1], renderer);

		}
		else if (velocity[0] < 0) {
			lastAnimation = leftAnimation;
			leftAnimation->render(coordinates[0], coordinates[1], renderer);

		}

		else if (velocity[1] > 0) {
			lastAnimation = downAnimation;
			downAnimation->render(coordinates[0], coordinates[1], renderer);

		}
		else if (velocity[1] < 0) {
			lastAnimation = upAnimation;
			upAnimation->render(coordinates[0], coordinates[1], renderer);

		}
		else {
			lastAnimation = startAnimation;
			startAnimation->render(coordinates[0], coordinates[1], renderer);
		}

		MovingEntity::update();



	}



}

Pacman::Pacman(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth) : MovingEntity(104, 216, 3, mainSpriteSheet, textureWidth, textureHeight) {

	m_input = std::make_shared <InputComponent>();
	MovingEntity::setEntityType(EntityType::PACMAN);
	lastAnimation = startAnimation;
	deathAnimation = std::make_shared<AnimationComponent>(11, mainSpriteSheet, textureWidth, textureHeight);

	rightAnimation->addRect(457, 1, 13, 13);
	rightAnimation->addRect(473, 1, 13, 13);
	rightAnimation->addRect(489, 1, 13, 13);

	leftAnimation->addRect(457, 17, 13, 13);
	leftAnimation->addRect(473, 17, 13, 13);
	leftAnimation->addRect(489, 1, 13, 13);

	upAnimation->addRect(457, 33, 13, 13);
	upAnimation->addRect(473, 33, 13, 13);
	upAnimation->addRect(489, 1, 13, 13);

	downAnimation->addRect(457, 49, 13, 13);
	downAnimation->addRect(473, 49, 13, 13);
	downAnimation->addRect(489, 1, 13, 13);

	startAnimation->addRect(489, 1, 13, 13);
	startAnimation->addRect(489, 1, 13, 13);
	startAnimation->addRect(489, 1, 13, 13);

	deathAnimation->addRect(489, 1, 13, 13);
	deathAnimation->addRect(505, 1, 15, 13);
	deathAnimation->addRect(519, 1, 15, 13);
	deathAnimation->addRect(536, 1, 15, 13);
	deathAnimation->addRect(552, 1, 15, 13);
	deathAnimation->addRect(568, 1, 15, 13);
	deathAnimation->addRect(584, 1, 15, 13);
	deathAnimation->addRect(601, 1, 15, 13);
	deathAnimation->addRect(615, 1, 15, 13);
	deathAnimation->addRect(631, 1, 15, 13);
	deathAnimation->addRect(647, 1, 15, 13);
}

int Pacman::getRemainingLives()
{
	return remainingLife;
}

Pacman::~Pacman()
{
}


