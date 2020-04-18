#include "Pacman.h"


void Pacman::update(std::shared_ptr<GameState> gameState, std::shared_ptr<CollisionManager> collisionManager, SDL_Renderer* renderer)
{

	// Saves last direction pacman traveled in.
	int lastVelocity[2] = { velocity[0], velocity[1] };

	//update score on main screen;
	m_scoreComponent->update(m_score);

	//Death animation and handling
	if (*gameState == GameState::PACMAN_DIED) {

		m_deathAnimation->render(coordinates[0], coordinates[1], renderer, 0);

		if (m_deathAnimation->getCurrentFrame() == m_deathAnimation->getTotalFrames() - 1) {
			if (getRemainingLives() == 0) {
				resetLife();
				*gameState = GameState::GAME_OVER;
			}
			else {
				lostLife();
				*gameState = GameState::RESTART_LEVEL;
			}
		}
	}
	else {
		//collision check and switch case for what pacman should do depending on what entity type he collides with
		for (auto collidedWith : collisionManager->collisionCheck(shared_from_this())) {
			//returns a pointer to an entity that can be used for further handling
			if (collidedWith != nullptr) {
				switch (collidedWith->getEntityType())
				{

				case EntityType::GHOST:
					if (*gameState == GameState::GAME_RUNNING_FLEE || *gameState == GameState::GAME_RUNNING_FLEE_ENDING) {
						collidedWith->setOutSideCage(false);
						collidedWith->setEntityType(EntityType::GHOST_EYES);
						m_score += m_ghostPoints;
						m_ghostMunch->play(1, 0, 70);
						//Score increase for each ghost pacman eats
						m_ghostPoints *= m_pointDoubler;
					}
					else {
						m_deathSound->play(1, 0, 70);
						m_pointDoubler = 2;
						*gameState = GameState::PACMAN_DIED;

					}
					break;

				case EntityType::WALL:

					m_lastAnimation->render(coordinates[0], coordinates[1], renderer, 0);
					velocity[0] = 0;
					velocity[1] = 0;
					break;

				case EntityType::PELLET:
					collidedWith->setEntityType(EntityType::INACTIVE_PELLET);
					m_score += 10;
					m_pelletMunch->play(0, 0, 70);
					break;

				case EntityType::POWER_PELLET:
					*gameState = GameState::GAME_RUNNING_FLEE;
					collidedWith->setEntityType(EntityType::INACTIVE_POWER_PELLET);
					m_score += 50;
					m_pelletMunch->play(0, 0, 70);
					m_ghostPoints = 100;
					break;

				case EntityType::FRUIT:
					collidedWith->setEntityType(EntityType::INACTIVE_FRUIT);
					m_score += 50;
					break;

				case EntityType::DOOR:
					m_lastAnimation->render(coordinates[0], coordinates[1], renderer, 0);
					velocity[0] = 0;
					velocity[1] = 0;

					break;
				case EntityType::GHOST_EYES:
					

					break;

				default:
					break;
				}
			}
		}

		coordinates[0] += velocity[0];
		coordinates[1] += velocity[1];

		if (collisionManager->checkIntersection(shared_from_this())) {
			m_input->update(shared_from_this(), gameState);
		}

		//Checks the direction pacman is traveling and renders correct animation
		if (velocity[0] > 0) {
			m_lastAnimation = rightAnimation;
			rightAnimation->render(coordinates[0], coordinates[1], renderer, 0);

		}
		else if (velocity[0] < 0) {
			m_lastAnimation = leftAnimation;
			leftAnimation->render(coordinates[0], coordinates[1], renderer, 0);

		}
		else if (velocity[1] > 0) {
			m_lastAnimation = downAnimation;
			downAnimation->render(coordinates[0], coordinates[1], renderer, 0);

		}
		else if (velocity[1] < 0) {
			m_lastAnimation = upAnimation;
			upAnimation->render(coordinates[0], coordinates[1], renderer, 0);

		}
		else {
			m_lastAnimation = startAnimation;
			startAnimation->render(coordinates[0], coordinates[1], renderer, 0);
		}

		m_hp->update(getRemainingLives());
		//parent update function
		MovingEntity::update();
	}
}

Pacman::Pacman(SDL_Texture* mainSpriteSheet, int textureHeight, int textureWidth, SDL_Renderer* gameRenderer) : MovingEntity(104, 216, 3, mainSpriteSheet, textureWidth, textureHeight) {

	m_input = std::make_shared <InputComponent>();
	m_scoreComponent = std::make_shared<ScoreComponent>(gameRenderer);
	m_hp = std::make_shared<HPComponent>(gameRenderer);
	setEntityType(EntityType::PACMAN);
	m_lastAnimation = startAnimation;

	m_pelletMunch = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_chomp.wav");
	m_fruitMunch = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_eatfruit.wav");
	m_ghostMunch = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_eatghost.wav");
	m_deathSound = std::make_shared<SoundComponent>("..\\Pacman2020\\sounds\\pacman_death.wav");


	m_deathAnimation = std::make_shared<AnimationComponent>(11, mainSpriteSheet, textureWidth, textureHeight);

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

	m_deathAnimation->addRect(489, 1, 13, 13);
	m_deathAnimation->addRect(505, 1, 15, 13);
	m_deathAnimation->addRect(519, 1, 15, 13);
	m_deathAnimation->addRect(536, 1, 15, 13);
	m_deathAnimation->addRect(552, 1, 15, 13);
	m_deathAnimation->addRect(568, 1, 15, 13);
	m_deathAnimation->addRect(584, 1, 15, 13);
	m_deathAnimation->addRect(601, 1, 15, 13);
	m_deathAnimation->addRect(615, 1, 15, 13);
	m_deathAnimation->addRect(631, 1, 15, 13);
	m_deathAnimation->addRect(647, 1, 15, 13);
}

int Pacman::getRemainingLives()
{
	return m_remainingLife;
}

void Pacman::resetLife()
{
	m_remainingLife = 3;
}

int Pacman::getScore() {
	return m_score;
}

void Pacman::resetScore()
{
	m_score = 0;
}

void Pacman::lostLife()
{
	m_remainingLife--;
}

Pacman::~Pacman()
{
}


