#include "engine/engine.h"

MyEngine::Engine::Engine() : timeSinceLastShot(COOLDOWN_TIME * 2), paused(true), points(0)	{
	for(unsigned short i = 0; i < 20; i++)	{
		asteroids.emplace_back(new Asteroid{player->getPosition(), LARGE});
		// newAsteroids.emplace_back(asteroids.back()->getPosition());
	}

	shots.clear();
}

std::shared_ptr<MyEngine::Engine> MyEngine::Engine::getInstance()	{
	if(!singleton)	{
		singleton.reset(new MyEngine::Engine());
	}

	return singleton;
}

void MyEngine::Engine::update(const std::pair<float, float>& mousePosition)	{
	player->updateMovementDirection(mousePosition);
 	player->update(TIME_PER_FRAME);

	for(long unsigned i = 0; i < asteroids.size(); i++)	{
		asteroids[i]->getLife() > 0 ? asteroids[i]->update(TIME_PER_FRAME) : asteroidBreakdown(i);
		if(asteroids[i]->calculateDistance(*player) > 5000.f)	{
			deadAsteroids.emplace_back(asteroids[i]->getIdentifier());
			asteroids.erase(asteroids.begin() + i);
			asteroids.emplace_back(new Asteroid{player->getPosition(), LARGE});
		}

	}

	for(long unsigned i = 0; i < shots.size(); i++)	{
		if(player->calculateDistance(*(shots[i])) > 3000.f)	{
			deadShots.emplace_back(shots[i]->getIdentifier());
			shots.erase(shots.begin() + i);
		} else	{
			shots[i]->update(TIME_PER_FRAME);
		}
	}

	while(asteroids.size() < 20)	{
		asteroids.emplace_back(new Asteroid{player->getPosition(), LARGE});
	}
}

void MyEngine::Engine::collisionAmongAsteroids()	{
	for(unsigned short i = 0; i < asteroids.size(); i++)	{
		for (unsigned short j = i + 1; j < asteroids.size(); j++)	{
			if(asteroids[i]->intersects(*(asteroids[j])))	{
				asteroids[i]->switchSpeeds(*(asteroids[j]));
			}
		}
	}
}

void MyEngine::Engine::collisionWithPlayer()	{
	for(unsigned short i = 0; i < asteroids.size(); i++)	{
 		if(player->intersects(*(asteroids[i])) && !player->isInvulnerable())	{
			player->invulnerabilityReset();
			player->switchSpeeds(*(asteroids[i]));
			(*player)--;
			(*(asteroids[i]))--;
		}
	}
}

void MyEngine::Engine::collisionShotAndAsteroid()	{
	for(unsigned short j = 0; j < asteroids.size(); j++)	{
		for (unsigned short i = 0; i < shots.size(); i++)	{
			if(shots[i]->intersects(*(asteroids[j])))	{
				(*(asteroids[j]))--;
				deadShots.emplace_back(shots[i]->getIdentifier());
				shots.erase(shots.begin() + i);
			}
		}
	}
	
}

void MyEngine::Engine::asteroidBreakdown(unsigned long asteroidPosition)	{
	deadAsteroids.emplace_back(asteroids[asteroidPosition]->getIdentifier());

	switch (asteroids[asteroidPosition]->getLevel())	{
	case LARGE:
		points += 15;

		for(unsigned short ammountOfMediumOnes = 0; ammountOfMediumOnes < 1; ammountOfMediumOnes++)	{
			asteroids.emplace_back(new Asteroid{asteroids[asteroidPosition]->getPosition(), MEDIUM});
		}

		for(unsigned short ammountOfSmallOnes = 0; ammountOfSmallOnes < 2; ammountOfSmallOnes++)	{
			asteroids.emplace_back(new Asteroid{asteroids[asteroidPosition]->getPosition(), SMALL});
		}
		break;
	
	case MEDIUM:
		points += 10;
		
		for(unsigned short ammountOfSmallOnes = 0; ammountOfSmallOnes < 2; ammountOfSmallOnes++)	{
			asteroids.emplace_back(new Asteroid{asteroids[asteroidPosition]->getPosition(), SMALL});			
		}
		break;
	
	default:
		points += 5;
		break;
	}

	asteroids.erase(asteroids.begin() + asteroidPosition);

}

unsigned MyEngine::Engine::getPoints() const	{
	return points;
}

unsigned short MyEngine::Engine::getPLayerLife() const	{
	return player->getLife();
}

bool MyEngine::Engine::playerMoving() const	{
	return player->isMoving();
}

bool MyEngine::Engine::runEngine(const std::pair<float, float>& mousePosition, const std::list<unsigned short>& commands)	{
	for(auto command: commands)	{
		switch(command)	{
			case MyCommands::PAUSE:
				paused = !paused;
				break;

			case MyCommands::EXIT:
				return true;
				break;
			
			default:
				player->takeCommand(command);
				break;
		}
	}

	if(!paused)	{
		shoot(mousePosition);

		collisionShotAndAsteroid();
		collisionAmongAsteroids();
		collisionWithPlayer();

		update(mousePosition);
	}

	return !(player->getLife() > 0);
}

std::pair<float, float> MyEngine::Engine::getPlayerPosition() const	{
	return player->getPosition();
}

std::list<CommunicationEngineWithGUI::AsteroidCommunication> MyEngine::Engine::getAsteroids() const	{
	std::list<CommunicationEngineWithGUI::AsteroidCommunication> output;

	for(auto currentAsteroid: asteroids)	{
		CommunicationEngineWithGUI::AsteroidCommunication temp;

		temp.positionInX = currentAsteroid->getPosition().first;
		temp.positionInY = currentAsteroid->getPosition().second;
		temp.level = currentAsteroid->getLevel();
		temp.identifier = currentAsteroid->getIdentifier();

		output.emplace_back(temp);
	}

	return output;
}

std::list<CommunicationEngineWithGUI::ShotCommunication> MyEngine::Engine::getShots() const	{
	std::list<CommunicationEngineWithGUI::ShotCommunication> output;

	for(auto shot: shots)	{
		CommunicationEngineWithGUI::ShotCommunication temp;
		temp.positionInX = shot->getPosition().first;
		temp.positionInY = shot->getPosition().second;
		temp.angle = shot->getAngle();
		temp.identifier = shot->getIdentifier();

		output.emplace_back(temp);
	}

	return output;
}

void MyEngine::Engine::shoot(const std::pair<float, float>& direction)	{
	timeSinceLastShot += TIME_PER_FRAME;

	if(player->isShooting() && (timeSinceLastShot > COOLDOWN_TIME))	{
		shots.emplace_back(new Shot{player->getPosition(), direction});
		timeSinceLastShot = 0;
	}
}

std::list<long unsigned> MyEngine::Engine::getDeadAsteroids()	{
	std::list<long unsigned> output{deadAsteroids};
	deadAsteroids.clear();
	return output;
}

std::list<long unsigned> MyEngine::Engine::getDeadShots()	{
	std::list<long unsigned> output {deadShots};
	deadShots.clear();
	return output;
}

bool MyEngine::Engine::isPaused() const	{
	return paused;
}