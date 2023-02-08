#include "game/game.h"

MyGame::Game::Game() : engine(MyEngine::Engine::getInstance()), GUI(MyGUI::GraphicalInterface::getInstance(engine->getAsteroids()))	{
	runGame();
}

void MyGame::Game::runGame()	{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (GUI->isWindowOpen())	{
		if(engine->runEngine(GUI->getMouseCoordinates(), GUI->processUserInputs()))	{
			GUI->gameOver(engine->getPoints());
			break;
		}

		GUI->updateAsteroids(engine->getDeadAsteroids(), engine->getAsteroids());
		GUI->updatePlayer(engine->getPlayerPosition(), engine->playerMoving());
		GUI->updateShots(engine->getDeadShots(), engine->getShots());
		GUI->updateHUD(engine->getPLayerLife(), engine->getPoints());
		
		GUI->render(TIME_PER_FRAME);

		timeSinceLastUpdate = clock.getElapsedTime();
		if (timeSinceLastUpdate < sf::seconds(TIME_PER_FRAME))	{
			sf::sleep(sf::seconds(TIME_PER_FRAME) - timeSinceLastUpdate);
		}	
	}
}