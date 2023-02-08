#include "graphical-interface/animation.h"

MyGUI::Animation::Animation(const sf::Vector2f& position) : currentTexture(0), frameCounter(0)	{
	if (!texturesAlreadyInitialized) {
		MyGUI::Animation::loadTextures();
	}
	
	setPosition(position);
}

void MyGUI::Animation::loadTextures() {
	textures[EXPLOSION] = std::vector<sf::Texture>{ 7 };
	textures[SHOT] = std::vector<sf::Texture>{ 13 };
	textures[LARGE_ASTEROID] = std::vector<sf::Texture>{ 1 };
	textures[MEDIUM_ASTEROID] = std::vector<sf::Texture>{ 1 };
	textures[SMALL_ASTEROID] = std::vector<sf::Texture>{ 1 };

	std::cout << (textures[EXPLOSION][0].loadFromFile("textures/sequencia-explosao.png", sf::IntRect(63, 68, 65, 64)) ? "Explosao: Primeira textura carregada com sucesso\n" : "Explosao: Falha ao carregar a primeira textura\n");
	std::cout << (textures[EXPLOSION][1].loadFromFile("textures/sequencia-explosao.png", sf::IntRect(214, 37, 119, 105)) ? "Explosao: Segunda textura carregada com sucesso\n" : "Explosao: Falha ao carregar a segunda textura\n");
	std::cout << (textures[EXPLOSION][2].loadFromFile("textures/sequencia-explosao.png", sf::IntRect(383, 19, 156, 144)) ? "Explosao: Terceira textura carregada com sucesso\n" : "Explosao: Falha ao carregar a terceira textura\n");
	std::cout << (textures[EXPLOSION][3].loadFromFile("textures/sequencia-explosao.png", sf::IntRect(560, 2, 171, 172)) ? "Explosao: Quarta textura carregada com sucesso\n" : "Explosao: Falha ao carregar a quarta textura\n");
	std::cout << (textures[EXPLOSION][4].loadFromFile("textures/sequencia-explosao.png", sf::IntRect(738, 4, 169, 168)) ? "Explosao: Quinta textura carregada com sucesso\n" : "Explosao: Falha ao carregar a quinta textura\n");
	std::cout << (textures[EXPLOSION][5].loadFromFile("textures/sequencia-explosao.png", sf::IntRect(10, 198, 166, 157)) ? "Explosao: Sexta textura carregada com sucesso\n" : "Explosao: Falha ao carregar a sexta textura\n");
	std::cout << (textures[EXPLOSION][6].loadFromFile("textures/sequencia-explosao.png", sf::IntRect(204, 205, 151, 149)) ? "Explosao: Sétima textura carregada com sucesso\n" : "Explosao: Falha ao carregar a setima textura\n");

	std::cout << (textures[SHOT][0].loadFromFile("textures/tiro.png", sf::IntRect(0, 0, 85, 32)) ? "Tiro: Primeira textura carregada com sucesso\n" : "Tiro: Falha ao carregar a primeira textura");
	std::cout << (textures[SHOT][1].loadFromFile("textures/tiro.png", sf::IntRect(85, 0, 85, 32)) ? "Tiro: Segunda textura carregada com sucesso\n" : "Tiro: Falha ao carregar a segunda textura");
	std::cout << (textures[SHOT][2].loadFromFile("textures/tiro.png", sf::IntRect(170, 0, 85, 32)) ? "Tiro: Terceira textura carregada com sucesso\n" : "Tiro: Falha ao carregar a terceira textura");
	std::cout << (textures[SHOT][3].loadFromFile("textures/tiro.png", sf::IntRect(255, 0, 85, 32)) ? "Tiro: Quarta textura carregada com sucesso\n" : "Tiro: Falha ao carregar a quarta textura");
	std::cout << (textures[SHOT][4].loadFromFile("textures/tiro.png", sf::IntRect(340, 0, 85, 32)) ? "Tiro: Quinta textura carregada com sucesso\n" : "Tiro: Falha ao carregar a quinta textura");
	std::cout << (textures[SHOT][5].loadFromFile("textures/tiro.png", sf::IntRect(425, 0, 85, 32)) ? "Tiro: Sexta textura carregada com sucesso\n" : "Tiro: Falha ao carregar a sexta textura");
	std::cout << (textures[SHOT][6].loadFromFile("textures/tiro.png", sf::IntRect(510, 0, 85, 32)) ? "Tiro: Sétima textura carregada com sucesso\n" : "Tiro: Falha ao carregar a sétima textura");
	std::cout << (textures[SHOT][7].loadFromFile("textures/tiro.png", sf::IntRect(0, 32, 85, 32)) ? "Tiro: Oitava textura carregada com sucesso\n" : "Tiro: Falha ao carregar a oitava textura");
	std::cout << (textures[SHOT][8].loadFromFile("textures/tiro.png", sf::IntRect(85, 32, 85, 32)) ? "Tiro: Nona textura carregada com sucesso\n" : "Tiro: Falha ao carregar a nona textura");
	std::cout << (textures[SHOT][9].loadFromFile("textures/tiro.png", sf::IntRect(170, 32, 85, 32)) ? "Tiro: Décima textura carregada com sucesso\n" : "Tiro: Falha ao carregar a décima textura");
	std::cout << (textures[SHOT][10].loadFromFile("textures/tiro.png", sf::IntRect(255, 32, 85, 32)) ? "Tiro: Décima-primeira textura carregada com sucesso\n" : "Tiro: Falha ao carregar a décima-primeira textura");
	std::cout << (textures[SHOT][11].loadFromFile("textures/tiro.png", sf::IntRect(340, 32, 85, 32)) ? "Tiro: Décima-segunda textura carregada com sucesso\n" : "Tiro: Falha ao carregar a décima-segunda textura");
	std::cout << (textures[SHOT][12].loadFromFile("textures/tiro.png", sf::IntRect(425, 32, 85, 32)) ? "Tiro: Décima-terceira textura carregada com sucesso\n" : "Tiro: Falha ao carregar a décima-terceira textura");

	std::cout << (textures[LARGE_ASTEROID][0].loadFromFile("textures/asteroide-grande.png", sf::IntRect(108, 242, 1022, 772)) ? "Asteroide Grande: textura carregada com sucesso\n" : "Asteroide Grande: Falha ao carregar a textura\n");
	
	std::cout << (textures[MEDIUM_ASTEROID][0].loadFromFile("textures/asteroide-medio.png", sf::IntRect(439, 505, 530, 409)) ? "Asteroide Medio: textura carregada com sucesso\n" : "Asteroide Medio: Falha ao carregar a textura\n");
	
	std::cout << (textures[SMALL_ASTEROID][0].loadFromFile("textures/asteroide-pequeno.png", sf::IntRect(531, 567, 358, 273)) ? "Asteroide Pequeno: textura carregada com sucesso\n" : "Asteroide Pequeno: Falha ao carregar a textura\n");
	
	texturesAlreadyInitialized = true;
}

void MyGUI::Animation::switchTexture(unsigned short typeOfAnimation) {
	setTexture(textures[typeOfAnimation][currentTexture]);
	setOrigin(0, 0);
	setTextureRect(sf::IntRect(0, 0, textures[typeOfAnimation][currentTexture].getSize().x, textures[typeOfAnimation][currentTexture].getSize().y));
	setOrigin(float(textures[typeOfAnimation][currentTexture].getSize().x / 2.0), float(textures[typeOfAnimation][currentTexture].getSize().x / 2.0));
}

MyGUI::Animation::~Animation()	{}