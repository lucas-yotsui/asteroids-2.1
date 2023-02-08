#ifndef _HUD_H_
#define _HUD_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace MyGUI	{
	enum TextureIDs	{
		BACKGROUND_TEXTURE,
		FULL_LIFE_TEXTURE,
		HALF_LIFE_TEXTURE,
		EMPTY_LIFE_TEXTURE
	};

	enum SpriteIDs	{
		BACKGROUND_SPRITE,
		FIRST_LIFE_SPRITE,
		SECOND_LIFE_SPRITE,
		THIRD_LIFE_SPRITE,
		FOURTH_LIFE_SPRITE
	};

	class HUD	{
	private:
		std::vector<sf::Sprite> sprites;
		std::vector<sf::Text> texts;

		std::vector<sf::Texture> textures;
		sf::Font font;

		float windowWidth;
		float windowHeight;

	public:
		HUD(const sf::RenderWindow& window);
		void setHighScore(unsigned highScore);
		void update(const sf::Vector2f& viewCenterPosition, unsigned short life, unsigned points);
		void render(sf::RenderWindow& window) const;
	};
}

#endif