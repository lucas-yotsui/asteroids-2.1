#include "graphical-interface/graphical-interface.h"

MyGUI::GraphicalInterface::GraphicalInterface(const std::list<CommunicationEngineWithGUI::AsteroidCommunication>& asteroidsPositions) : window(sf::VideoMode::getDesktopMode(), "Asteroids 2.1"), camera({float(window.getSize().x), float(window.getSize().y)}), hud(window)	{
	for(auto currentAsteroid: asteroidsPositions)	{
		graphicalAsteroids.emplace_back(new GraphicalAsteroid(currentAsteroid));
	}

	shots.clear();
	explosions.clear();

	window.setView(camera);

	std::ifstream highScoreFile{"high-score.txt"};
	highScoreFile >> highScore;
	highScoreFile.close();
}

std::shared_ptr<MyGUI::GraphicalInterface> MyGUI::GraphicalInterface::getInstance(const std::list<CommunicationEngineWithGUI::AsteroidCommunication>& asteroidsPositions)	{
	if(!singleton)	{
		singleton.reset(new GraphicalInterface(asteroidsPositions));
	}

	return singleton;
}

std::list<unsigned short> MyGUI::GraphicalInterface::processUserInputs()	{
	std::list<unsigned short> inputs;
	sf::Event event;

	while(window.pollEvent(event))	{
		switch(event.type)	{
			case sf::Event::KeyPressed:
				switch (event.key.code)	{
				case sf::Keyboard::Key::Escape:
					inputs.emplace_back(MyCommands::PAUSE);
					break;
				
				case sf::Keyboard::Key::Space:
					inputs.emplace_back(MyCommands::ACCELERATE);
					break;

				default:
					break;
				}
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code)	{		
				case sf::Keyboard::Key::Space:
					inputs.emplace_back(MyCommands::DONT_ACCELERATE);
					break;

				default:
					break;
				}
				break;

			case sf::Event::MouseButtonPressed:
				if(event.mouseButton.button == sf::Mouse::Left)	{
					inputs.emplace_back(MyCommands::SHOOT);
				}
				break;

			case sf::Event::MouseButtonReleased:
				if(event.mouseButton.button == sf::Mouse::Left)	{
					inputs.emplace_back(MyCommands::DONT_SHOOT);
				}
				break;
			
			case sf::Event::Closed:
				inputs.emplace_back(MyCommands::EXIT);
				break;

			default:
				break;
		}
	}

	return inputs;
}

void MyGUI::GraphicalInterface::updateAsteroids(const std::list<long unsigned>& deadAsteroids, const std::list<CommunicationEngineWithGUI::AsteroidCommunication>& asteroidPositions)	{
	for(auto currentDeadAsteroid: deadAsteroids)	{
		for(unsigned i = 0; i < graphicalAsteroids.size(); i++)	{
			if(graphicalAsteroids[i]->getIdentifier() == currentDeadAsteroid)	{
				explosions.emplace_back(new Explosion{graphicalAsteroids[i]->getPosition()});
				graphicalAsteroids.erase(graphicalAsteroids.begin() + i);
				break;
			}
		}
	}
	
	bool alreadyExists;

	for(auto currentAsteroidPosition: asteroidPositions)	{
		alreadyExists = false;
		
		for(auto currentGraphicalAsteroid: graphicalAsteroids)	{
			if(currentGraphicalAsteroid->getIdentifier() == currentAsteroidPosition.identifier)	{
				currentGraphicalAsteroid->updateAnimation({currentAsteroidPosition.positionInX, currentAsteroidPosition.positionInY});
				alreadyExists = true;
				break;
			}
		}

		if(!alreadyExists)	{
			graphicalAsteroids.emplace_back(new GraphicalAsteroid{currentAsteroidPosition});
		}
	}
}

void MyGUI::GraphicalInterface::updateShots(const std::list<long unsigned>& deadShots, const std::list<CommunicationEngineWithGUI::ShotCommunication>& shotPositions)	{
	for(auto currentDeadShot: deadShots)	{
		for(unsigned i = 0; i < shots.size(); i++)	{
			if(shots[i]->getIdentifier() == currentDeadShot)	{
				shots.erase(shots.begin() + i);
				break;
			}
		}
	}

	bool alreadyExists;

	for(auto currentShotPosition: shotPositions)	{
		alreadyExists = false;

		for(auto currentGraphicalShot: shots)	{
			if(currentGraphicalShot->getIdentifier() == currentShotPosition.identifier)	{
				currentGraphicalShot->updateAnimation({currentShotPosition.positionInX, currentShotPosition.positionInY});
				alreadyExists = true;
				break;
			}
		}

		if(!alreadyExists)	{
			shots.emplace_back(new GraphicalShot{currentShotPosition});
		}
	}
}

void MyGUI::GraphicalInterface::updateExplosions()	{
	for(unsigned currentExplosion = 0; currentExplosion < explosions.size(); currentExplosion++)	{
		if(explosions[currentExplosion]->isFinished())	{
			explosions.erase(explosions.begin() + currentExplosion);
		} else	{
			explosions[currentExplosion]->updateAnimation({0.f, 0.f});
		}
	}
}

void MyGUI::GraphicalInterface::updatePlayer(const std::pair<float, float>& playerCurrentPosition, bool moving)	{
	player->update(playerCurrentPosition, getMouseCoordinates(), moving);
}

void MyGUI::GraphicalInterface::updateHUD(unsigned short life, unsigned points)	{
	hud.update(camera.getCenter(), life, points);
}

void MyGUI::GraphicalInterface::render(float elapsedTime)	{
	window.clear();

	window.setView(camera);

	camera.update(player->getPosition(), elapsedTime);
	
	hud.render(window);

	window.draw(*player);
	
	for(auto asteroid: graphicalAsteroids)	{
		window.draw(*asteroid);
	}

	for(auto shot: shots)	{
		window.draw(*shot);
	}

	for(auto explosion: explosions)	{
		window.draw(*explosion);
	}

	window.display();

	window.setView(window.getDefaultView());
}

void MyGUI::GraphicalInterface::gameOver(unsigned points)	{
	if(points > highScore)	{
		std::ofstream highScoreFile{"high-score.txt"};
		highScore >> points;
		highScoreFile.close();
	}
	
	window.close();
}

bool MyGUI::GraphicalInterface::isWindowOpen() const	{
	return window.isOpen();
}

std::pair<float, float> MyGUI::GraphicalInterface::getMouseCoordinates() const	{	
	auto mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);
	return {mousePosition.x, mousePosition.y};
}