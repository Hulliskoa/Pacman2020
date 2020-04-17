#include "Pacman.h"


void Pacman::update(std::shared_ptr<GameState> gameState, std::shared_ptr<CollisionManager> collisionManager, SDL_Renderer* renderer)
{

	// Saves last direction pacman traveled in.
	int lastVelocity[2] = { velocity[0], velocity[1] };

	//update score on main screen;
	scoreComponent->update(score);

	//Death animation and handling
	if (*gameState == GameState::PACMAN_DIED) {
		deathAnimation->render(coordinates[0], coordinates[1], renderer, 0);

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
		//collision check and what switch case for what pacman should do depending on what entity type he collides with
		std::shared_ptr<Entity>  collidedWith = collisionManager->collisionCheck(shared_from_this());//returns a pointer to an entity that can be used for further handling
		if (collidedWith != nullptr) {
			switch (collidedWith->getEntityType())
			{

			case EntityType::GHOST:
				std::cout << "hit ghost" << std::endl;
				if (*gameState == GameState::GAME_RUNNING_FLEE || *gameState == GameState::GAME_RUNNING_FLEE_ENDING) {
					std::cout << "hit scared ghost" << std::endl;
					scoreComponent->renderGhostPoints(shared_from_this(), ghostPoints);
					collidedWith->setEntityType(EntityType::GHOST_EYES);
					score += ghostPoints;
					//Score increase for each ghost pacman eats
					ghostPoints *= pointDoubler;
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
					lastAnimation->render(coordinates[0], coordinates[1], renderer, 0);
				}
				else {
					lastAnimation->render(coordinates[0], coordinates[1], renderer, 0);
					velocity[0] = 0;
					velocity[1] = 0;
				}
				break;

			case EntityType::PELLET:
				collidedWith->setEntityType(EntityType::INACTIVE_PELLET);
				score += 10;
				m_pelletMunch->play(0,70);
				break;

			case EntityType::POWER_PELLET:
				*gameState = GameState::GAME_RUNNING_FLEE;
				collidedWith->setEntityType(EntityType::INACTIVE_POWER_PELLET);
				score += 50;
				ghostPoints = 100;
				break;

			case EntityType::FRUIT:
				collidedWith->setEntityType(EntityType::INACTIVE_FRUIT);
				score += 50;
				break;

			case EntityType::DOOR:
				if ((velocity[0] != lastVelocity[0]) || (velocity[1] != lastVelocity[1])) {
					velocity[0] = lastVelocity[0];
					velocity[1] = lastVelocity[1];
					lastAnimation->render(coordinates[0], coordinates[1], renderer, 0);
				}
				else {
					lastAnimation->render(coordinates[0], coordinates[1], renderer, 0);
					velocity[0] = 0;
					velocity[1] = 0;
				}
				break;

			default:
				break;
			}
		}
		coordinates[0] += velocity[0];
		coordinates[1] += velocity[1];

		if (collisionManager->checkIntersection(shared_from_this())) {
			m_input->update(velocity, gameState);
		}

		//Checks the direction pacman is traveling and renders correct animation
		if (velocity[0] > 0) {
			lastAnimation = rightAnimation;
			rightAnimation->render(coordinates[0], coordinates[1], renderer, 0);

		}
		else if (velocity[0] < 0) {
			lastAnimation = leftAnimation;
			leftAnimation->render(coordinates[0], coordinates[1], renderer, 0);

		}
		else if (velocity[1] > 0) {
			lastAnimation = downAnimation;
			downAnimation->render(coordinates[0], coordinates[1], renderer, 0);

		}
		else if (velocity[1] < 0) {
			lastAnimation = upAnimation;
			upAnimation->render(coordinates[0], coordinates[1], renderer, 0);

		}
		else {
			lastAnimation = startAnimation;
			startAnimation->render(coordinates[0], coordinates[1], renderer, 0);
		}
		//parent update function
		MovingEntity::update();
	}
}

Pacman::Pacman(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, SDL_Renderer* gameRenderer) : MovingEntity(104, 216, 3, mainSpriteSheet, textureWidth, textureHeight) {

	m_input = std::make_shared <InputComponent>();
	scoreComponent = std::make_shared<Score>(gameRenderer);

	setEntityType(EntityType::PACMAN);
	lastAnimation = startAnimation;


	m_pelletMunch = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_chomp.wav");
	m_fruitMunch = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_eatfruit.wav");
	m_ghostMunch = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_eatghost.wav");
	m_deathSound = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_death.wav");


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

int Pacman::getScore() {
	return score;
}

Pacman::~Pacman()
{
}


