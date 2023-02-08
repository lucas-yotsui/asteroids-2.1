#include "graphical-interface/explosion.h"

MyGUI::Explosion::Explosion(const sf::Vector2f& position) : Animation(position), finished(false)	{
	setScale(0.5, 0.5);
}

void MyGUI::Explosion::updateAnimation(const sf::Vector2f& position) {	
	frameCounter++;

	if (frameCounter == RELACAO_FRAME_ANIMACAO_FRAME_REAL) {
		frameCounter = 0;
		currentTexture++;
		
		if(currentTexture == textures[EXPLOSION].size())	{
			finish();
			return;	
		}

		switchTexture(EXPLOSION);
	}
}

void MyGUI::Explosion::finish() {
	finished = true;
}

bool MyGUI::Explosion::isFinished()	{
	return finished;
}