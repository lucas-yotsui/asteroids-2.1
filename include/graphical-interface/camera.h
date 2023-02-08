#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SFML/Graphics.hpp>

namespace MyGUI	{
	class Camera : public sf::View	{
	public:
		Camera(const sf::Vector2f& size);
		void update(const sf::Vector2f& playerPosition, float elapsedTime);
	};
}

#endif