#include "graphical-interface/graphical-shot.h"

MyGUI::GraphicalShot::GraphicalShot(const CommunicationEngineWithGUI::ShotCommunication& reference) : Animation({reference.positionInX, reference.positionInY})	{
	setTexture(textures[SHOT][0]);
	setOrigin(sf::Vector2f(getTexture()->getSize())/2.f);
	// setRotation(90);
	rotate(reference.angle * 180.f/float(std::numbers::pi));
}

void MyGUI::GraphicalShot::updateAnimation(const sf::Vector2f& position)	{
	frameCounter++;

	if(frameCounter == RELACAO_FRAME_ANIMACAO_FRAME_REAL)	{
		frameCounter = 0;
		currentTexture++;

		if(currentTexture == textures[SHOT].size())	{
			currentTexture = 0;
		}

		switchTexture(SHOT);
	}

	setPosition(position);
}

long unsigned MyGUI::GraphicalShot::getIdentifier() const	{
	return identifier;
}