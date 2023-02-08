#include "engine/player.h"

MyEngine::Player::Player() : BaseEntity(8, PLAYER_RADIUS, {0.f, 0.f}, {0.f, 0.f}), accelerating(false), shooting(false), invulnerabilityCounter(0)	{}

std::shared_ptr<MyEngine::Player> MyEngine::Player::getInstance()	{
	if(!singleton)	{
		singleton.reset(new Player());
	}

	return singleton;
}

void MyEngine::Player::update(float timeElapsed)	{
	if(accelerating)	{
		currentSpeed.first = PLAYER_SPEED * std::cos(angle);
		currentSpeed.second = PLAYER_SPEED * std::sin(angle);
	} else {
		if(currentSpeed.first > 0)	{
			if(currentSpeed.first > DRAG * timeElapsed)	{
				currentSpeed.first -= DRAG * timeElapsed;
			} else	{
				currentSpeed.first = 0;
			}
		} else	{
			if(currentSpeed.first < -(DRAG * timeElapsed))	{
				currentSpeed.first += DRAG * timeElapsed;
			} else	{
				currentSpeed.first = 0;
			}
		}

		if(currentSpeed.second > 0)	{
			if(currentSpeed.second > DRAG * timeElapsed)	{
				currentSpeed.second -= DRAG * timeElapsed;
			} else	{
				currentSpeed.second = 0;
			}
		} else	{
			if(currentSpeed.second < -(DRAG * timeElapsed))	{
				currentSpeed.second += DRAG * timeElapsed;
			} else	{
				currentSpeed.second = 0;
			}
		}
	}

	currentPosition.first += currentSpeed.first * timeElapsed;
	currentPosition.second += currentSpeed.second * timeElapsed; 

	invulnerabilityCounter++;
}

void MyEngine::Player::updateMovementDirection(const std::pair<float, float>& mousePosition)	{
	angle = std::atan2(mousePosition.second - currentPosition.second, mousePosition.first - currentPosition.first);
}

void MyEngine::Player::takeCommand(unsigned short command)	{
	switch (command)	{
	case MyCommands::ACCELERATE:
		accelerating = true;
		break;
		
	case MyCommands::SHOOT:
		shooting = true;
		break;

	case MyCommands::DONT_ACCELERATE:
		accelerating = false;
		break;

	case MyCommands::DONT_SHOOT:
		shooting = false;
		break;
	
	default:
		break;
	}
}

bool MyEngine::Player::isShooting() const	{
	return shooting;
}

bool MyEngine::Player::isInvulnerable() const	{
	return invulnerabilityCounter < 60;
}

bool MyEngine::Player::isMoving() const	{
	return accelerating;
}

void MyEngine::Player::invulnerabilityReset()	{
	invulnerabilityCounter = 0;
}