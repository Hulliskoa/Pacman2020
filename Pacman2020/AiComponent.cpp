#include "AiComponent.h"

AiComponent::AiComponent() {}

void AiComponent::update(int ghost, int* pacmanCoord, int* ghostCoord, EntityType currentEntityType)
{
	switch (ghost)
	{
	case 0:
		shadowAI(pacmanCoord, ghostCoord, currentEntityType);
		break;
	case 1:
		speedyAI(pacmanCoord, ghostCoord, currentEntityType);
		break;
	case 2:
		bashfulAI(pacmanCoord, ghostCoord, currentEntityType);
		break;
	case 3:
		pokeyAI(pacmanCoord, ghostCoord, currentEntityType);
		break;
	default:
		break;
	}
}

int* AiComponent::shadowAI(int* pacmanCoord, int* ghostCoord, EntityType currentEntityType)
{
	return nullptr;
}

int* AiComponent::speedyAI(int* pacmanCoord, int* ghostCoord, EntityType currentEntityType)
{
	return nullptr;
}

int* AiComponent::bashfulAI(int* pacmanCoord, int* ghostCoord, EntityType currentEntityType)
{
	return nullptr;
}

int* AiComponent::pokeyAI(int* pacmanCoord, int* ghostCoord, EntityType currentEntityType)
{
	return nullptr;
}
