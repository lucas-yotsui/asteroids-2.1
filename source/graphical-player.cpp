#include "graphical-interface/graphical-player.h"

MyGUI::GraphicalPlayer::GraphicalPlayer() : textures{2}	{
	textures[0].loadFromFile("textures/full-ship.png", sf::IntRect{0, 0, 288, 257});
	textures[1].loadFromFile("textures/full-ship.png", sf::IntRect{288, 0, 288, 257});
	setTexture(textures[0]);
	setOrigin(float(textures[0].getSize().x) / 2.f, float(textures[0].getSize().y) / 2.f);
	setPosition(0.f, 0.f);
	setScale(0.5, 0.5);
}

std::shared_ptr<MyGUI::GraphicalPlayer> MyGUI::GraphicalPlayer::getInstance()	{
	if(!singleton)	{
		singleton.reset(new GraphicalPlayer());
	}

	return singleton;
}

void MyGUI::GraphicalPlayer::update(const std::pair<float, float>& currentPosition, const std::pair<float, float>& mousePosition, bool moving)	{
	moving ? setTexture(textures[0]) : setTexture(textures[1]);
	setPosition(currentPosition.first, currentPosition.second);

	auto angle = std::atan2(mousePosition.second - currentPosition.second, mousePosition.first - currentPosition.first);
	angle *= 180.f/float(std::numbers::pi);

	setRotation(90);
	rotate(angle);
}