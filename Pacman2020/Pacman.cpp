#include "Pacman.h"


void Pacman::update()
{

	m_input.update(window, velocity);

	//collision check må inn her
	//Spørre hva pacman traff?

	coordinates[0] += velocity[0];
	coordinates[1] += velocity[1];





	//Checks the direction pacman is traveling
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



	Entity::update();

}

Pacman::Pacman(SDL_Renderer* renderer, SDL_Window* w, SDL_Surface * mainSpriteSheet) : Entity(renderer, 100, 100, 3, mainSpriteSheet), window(w) {


	setEntityType(PACMAN);



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


