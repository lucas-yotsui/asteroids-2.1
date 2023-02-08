#include "graphical-interface/graphical-asteroid.h"

MyGUI::GraphicalAsteroid::GraphicalAsteroid(const CommunicationEngineWithGUI::AsteroidCommunication& asteroidData) : Animation({asteroidData.positionInX, asteroidData.positionInY}), size(asteroidData.level), identifier(asteroidData.identifier)	{	
	switch (size)	{
	case LARGE_ASTEROID:
		setTexture(textures[LARGE_ASTEROID][0]);
		setScale(0.15f, 0.15f);
		break;

	case MEDIUM_ASTEROID:
		setTexture(textures[MEDIUM_ASTEROID][0]);
		setScale(0.15f, 0.15f);
		break;

	case SMALL_ASTEROID:
		setTexture(textures[SMALL_ASTEROID][0]);
		setScale(0.125f, 0.125f);
		break;

	default:
		break;
	}

	setOrigin(sf::Vector2f(getTexture()->getSize())/2.f);
}

void MyGUI::GraphicalAsteroid::updateAnimation(const sf::Vector2f& position)	{
	frameCounter++;

	if(frameCounter > RELACAO_FRAME_ANIMACAO_FRAME_REAL)	{
		frameCounter = 0;
		rotate(11.75);
	}

	setPosition(position);
}

long unsigned MyGUI::GraphicalAsteroid::getIdentifier() const	{
	return identifier;
}