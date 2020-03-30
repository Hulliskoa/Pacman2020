#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "EntityController.h"

class Entity
{

private:
	std::vector<int> currentPosition;
	Animation animations; //Håndterer aminasjon og inneholder sprites
	EntityController controller; //Inputmanager eller AI-controller
public:

	Entity(std::string entityType){}




};

