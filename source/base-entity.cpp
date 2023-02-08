#include "engine/base-entity.h"

MyEngine::BaseEntity::BaseEntity(unsigned short initialLife, unsigned short entityRadius, float initialSpeedInX, float initialSpeedInY) : currentSpeed(initialSpeedInX, initialSpeedInY), life(initialLife), radius(entityRadius)	{}

MyEngine::BaseEntity::BaseEntity(unsigned short initialLife, unsigned short entityRadius, const std::pair<float, float>& initialSpeed, const std::pair<float, float>& initialPosition) : currentPosition(initialPosition), currentSpeed(initialSpeed), life(initialLife), radius(entityRadius)	{}

float MyEngine::BaseEntity::calculateDistance(const BaseEntity& otherEntity) const	{
	return std::hypot(this->currentPosition.first - otherEntity.currentPosition.first, this->currentPosition.second - otherEntity.currentPosition.second);
}

bool MyEngine::BaseEntity::intersects(const BaseEntity& otherEntity) const	{
	return (calculateDistance(otherEntity) < (this->radius + otherEntity.radius));
}

void MyEngine::BaseEntity::switchSpeeds(BaseEntity& otherEntity)	{
	auto tempX = otherEntity.currentSpeed.first;
	auto tempY = otherEntity.currentSpeed.second;

	otherEntity.currentSpeed.first = this->currentSpeed.first;
	otherEntity.currentSpeed.second = this->currentSpeed.second;

	this->currentSpeed.first = tempX;
	this->currentSpeed.second = tempY;
}

void MyEngine::BaseEntity::operator--(int)	{
	life--;
}

const std::pair<float, float>& MyEngine::BaseEntity::getPosition() const	{
	return currentPosition;
}

unsigned short MyEngine::BaseEntity::getLife() const	{
	return life;
}

MyEngine::BaseEntity::~BaseEntity()	{}