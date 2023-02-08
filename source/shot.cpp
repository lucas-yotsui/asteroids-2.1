#include "engine/shot.h"

MyEngine::Shot::Shot(const std::pair<float, float>& initialPosition, const std::pair<float, float>& direction) : BaseEntity(1, SHOT_RADIUS, calculateSpeedComponents(initialPosition, direction), initialPosition)	{}

void MyEngine::Shot::update(float timeElapsed)	{
	currentPosition.first += currentSpeed.first * timeElapsed;
	currentPosition.second += currentSpeed.second * timeElapsed;
}

std::pair<float, float> MyEngine::Shot::calculateSpeedComponents(const std::pair<float, float>& initialPosition, const std::pair<float, float>& reference)	{
	angle = std::atan2(reference.second - initialPosition.second, reference.first - initialPosition.first); 

	return {SHOT_VECTORIAL_SPEED_MODULE * std::cos(angle), SHOT_VECTORIAL_SPEED_MODULE * std::sin(angle)};
}
//TODO Talvez essa parte aqui funcione com constexpr

float MyEngine::Shot::getAngle() const	{
	return angle;
}

long unsigned MyEngine::Shot::getIdentifier() const	{
	return identifier;
}