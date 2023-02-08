#include "engine/asteroid.h"

MyEngine::Asteroid::Asteroid(const std::pair<float, float>& initialPosition, short lvl) : BaseEntity(0, ASTEROID_RADIUS, speedRange(generator), speedRange(generator)), level(lvl)	{
	identifier = idAssigner++;

	switch (level)	{
	case LARGE:
		currentPosition.first = initialPosition.first + (initialDistance(generator) * sideOptions[sidePicker(generator)]);
		currentPosition.second = initialPosition.second + (initialDistance(generator) * sideOptions[sidePicker(generator)]);

		if(currentPosition.first > initialPosition.first)	{
			if(currentSpeed.first > 0)	{
				currentSpeed.first *= -1;
			} 
		} else if(currentPosition.first < initialPosition.first)	{
			if(currentSpeed.first < 0)	{
				currentSpeed.first *= -1;
			} 
		}

		if(currentPosition.second > initialPosition.second)	{
			if(currentSpeed.second > 0)	{
				currentSpeed.second *= -1;
			} 
		} else if(currentPosition.second < initialPosition.second)	{
			if(currentSpeed.second < 0)	{
				currentSpeed.second *= -1;
			} 
		}

		life = 4;
		break;
	
	case MEDIUM:
		currentPosition = initialPosition;
		life = 2; 
		break;
	
	case SMALL:
		currentPosition = initialPosition;
		life = 1;
		break;
	
	default:
		break;
	}
	
}

void MyEngine::Asteroid::update(float timeElapsed)	{
	currentPosition.first += currentSpeed.first * timeElapsed;
	currentPosition.second += currentSpeed.second * timeElapsed;
}

unsigned short MyEngine::Asteroid::getLevel() const	{
	return level;
}

unsigned MyEngine::Asteroid::getIdentifier() const	{
	return identifier;
}