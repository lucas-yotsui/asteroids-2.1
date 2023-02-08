#include "graphical-interface/camera.h"

MyGUI::Camera::Camera(const sf::Vector2f& size)	{
	setCenter(0, 0);
	setSize(size);
	zoom(3);
}

void MyGUI::Camera::update(const sf::Vector2f& playerPosition, float elapsedTime)	{
	auto offset = playerPosition - this->getCenter();
	move(offset/2.f * elapsedTime);
}