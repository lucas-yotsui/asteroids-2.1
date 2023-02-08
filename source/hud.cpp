#include "graphical-interface/hud.h"

MyGUI::HUD::HUD(const sf::RenderWindow& window)	{
	windowWidth = float(window.getSize().x);
	windowHeight = float(window.getSize().y);

	textures = std::vector<sf::Texture>{ 4 };
	sprites = std::vector<sf::Sprite>{ 5 };
	texts = std::vector<sf::Text>{ 2 };

	std::cout << (font.loadFromFile("fonts/Starjedi.ttf") ? "Fonte carregada com sucesso\n" : "Falha ao carregar a fonte\n");

	textures[BACKGROUND_TEXTURE].loadFromFile("textures/background.png");
	textures[FULL_LIFE_TEXTURE].loadFromFile("textures/life-levels.png", sf::IntRect{0, 0, 84, 90});
	textures[HALF_LIFE_TEXTURE].loadFromFile("textures/life-levels.png", sf::IntRect{84, 0, 84, 90});
	textures[EMPTY_LIFE_TEXTURE].loadFromFile("textures/life-levels.png", sf::IntRect{168, 0, 84, 90});

	sprites[BACKGROUND_SPRITE].setTexture(textures[BACKGROUND_TEXTURE]);
	sprites[FIRST_LIFE_SPRITE].setTexture(textures[FULL_LIFE_TEXTURE]);
	sprites[SECOND_LIFE_SPRITE].setTexture(textures[FULL_LIFE_TEXTURE]);
	sprites[THIRD_LIFE_SPRITE].setTexture(textures[FULL_LIFE_TEXTURE]);
	sprites[FOURTH_LIFE_SPRITE].setTexture(textures[FULL_LIFE_TEXTURE]);

	for(auto currentText: texts)	{
		currentText.setFont(font);
		currentText.setFillColor(sf::Color::Yellow);
		currentText.setOutlineColor(sf::Color::Black);
		currentText.setScale(15.f,15.f);
	}
	
	sprites[BACKGROUND_SPRITE].setScale(3.f, 3.f);
	sprites[BACKGROUND_SPRITE].setOrigin(float(textures[BACKGROUND_TEXTURE].getSize().x)/2.f, float(textures[BACKGROUND_TEXTURE].getSize().y)/2.f);
}

void MyGUI::HUD::setHighScore(unsigned highScore)	{
	texts[0].setString("Melhor Pontuação: " + std::to_string(highScore)); 
}

void MyGUI::HUD::update(const sf::Vector2f& viewCenterPosition, unsigned short life, unsigned points)	{
	switch(life)	{
		case 7:
			sprites[FOURTH_LIFE_SPRITE].setTexture(textures[HALF_LIFE_TEXTURE]);
			break;
		
		case 6:
			sprites[FOURTH_LIFE_SPRITE].setTexture(textures[EMPTY_LIFE_TEXTURE]);
			break;

		case 5:
			sprites[THIRD_LIFE_SPRITE].setTexture(textures[HALF_LIFE_TEXTURE]);
			break;

		case 4:
			sprites[THIRD_LIFE_SPRITE].setTexture(textures[EMPTY_LIFE_TEXTURE]);
			break;

		case 3:
			sprites[SECOND_LIFE_SPRITE].setTexture(textures[HALF_LIFE_TEXTURE]);
			break;

		case 2:
			sprites[SECOND_LIFE_SPRITE].setTexture(textures[EMPTY_LIFE_TEXTURE]);
			break;

		case 1:
			sprites[FIRST_LIFE_SPRITE].setTexture(textures[HALF_LIFE_TEXTURE]);
			break;

		case 0:
			sprites[FIRST_LIFE_SPRITE].setTexture(textures[EMPTY_LIFE_TEXTURE]);
			break;
		
		default:
			break;
	}

	sprites[BACKGROUND_SPRITE].setPosition(viewCenterPosition.x, viewCenterPosition.y);
	sprites[FIRST_LIFE_SPRITE].setPosition((viewCenterPosition.x + (3 * windowWidth/2.f)) - 80.f, viewCenterPosition.y - (3 * windowHeight/2.f));
	sprites[SECOND_LIFE_SPRITE].setPosition((viewCenterPosition.x + (3 * windowWidth/2.f)) - 160.f, viewCenterPosition.y - (3 * windowHeight/2.f));
	sprites[THIRD_LIFE_SPRITE].setPosition((viewCenterPosition.x + (3 * windowWidth/2.f)) - 240.f, viewCenterPosition.y - (3 * windowHeight/2.f));
	sprites[FOURTH_LIFE_SPRITE].setPosition((viewCenterPosition.x + (3 * windowWidth/2.f)) - 320.f, viewCenterPosition.y - (3 * windowHeight/2.f));

	texts[1].setString(std::to_string(points));
	texts[0].setPosition(viewCenterPosition.x - (3 * windowWidth/2.f), viewCenterPosition.y - (3 * windowHeight/2.f));
	texts[1].setPosition(viewCenterPosition.x, (viewCenterPosition.y - (windowHeight/2.f)));
}

void MyGUI::HUD::render(sf::RenderWindow& window) const	{
	for(auto currentSprite: sprites)	{
		window.draw(currentSprite);
	}

	for(auto currentText: texts)	{
		window.draw(currentText);
	}
}