#ifndef _BASE_ENTITY_H_
#define _BASE_ENTITY_H_

#include <utility>
#include <cmath>

#define TIME_PER_FRAME 1.f / 60.f

namespace MyEngine	{
	class BaseEntity	{
	protected: 
		/**
		 * Entity's current position
		*/
		std::pair<float, float> currentPosition;

		/**
		 * Entity's speed
		*/
		std::pair<float, float> currentSpeed;
		
		/**
		 * Entity's current life level
		*/
		unsigned short life;

		/**
		 * Radius of the circumference in which the entity is constrained
		*/
		unsigned short radius;
		
		/**
		 * @brief Constructor for the BaseEntity class
		 * 
		 * @details Constructs an object of the BaseEntity class. Declared as protected, since
		 * this is an abstract class and an object of it can't be constructed anyway. Therefore,
		 * keeping it this way, allows for the the classes that inherit this one to access this
		 * constructor, while preventing any external access to it.
		 * 
		 * @param initialLife Value to initialize the entity's life level with.
		 * 
		 * @param initialSpeedInX Value to initialize the entity's speed in the X axis with.
		 * 
		 * @param initialSpeedInY Value to initialize the entity's speed in the Y axis with.  
		*/
		BaseEntity(unsigned short initialLife, unsigned short entityRadius, float initialSpeedInX, float initialSpeedInY);
		
		/**
		 * @brief Constructor for the BaseEntity class
		 * 
		 * @details Constructs an object of the BaseEntity class. Declared as protected, since
		 * this is an abstract class and an object of it can't be constructed anyway. Therefore,
		 * keeping it this way, allows for the the classes that inherit this one to access this
		 * constructor, while preventing any external access to it.
		 * 
		 * @param initialLife Value to initialize the entity's life level with.
		 * 
		 * @param initialSpeed std::pair<float, float> containing the components of the value of 
		 * the entity's speed.
		 * 
		 * @param initialPosition std::pair<float, float> containing the components of the value 
		 * of the values of the entity's intial position.
		*/
		BaseEntity(unsigned short initialLife, unsigned short entityRadius, const std::pair<float, float>& initialSpeed, const std::pair<float, float>& initialPosition);

	public:
		/**
		 * @brief Purely virtual function that makes this class 
		 * abstract. When overriden, will update the entity's 
		 * current position.
		 * 
		 * @param elapsedTime Time passed since last update.
		*/
		virtual void update(float elapsedTime) = 0;

		/**
		 * @brief Inform the current position of the entity.
		 * 
		 * @return Entity's current position.
		*/
		const std::pair<float, float>& getPosition() const;

		/**
		 * @brief Inform the current level of life of the entity.
		 * 
		 * @return Entity's current life level.
		*/
		unsigned short getLife() const;

		/**
		 * @brief Calculates the distance between two entities
		 * 
		 * @return Calculated distance 
		*/
		float calculateDistance(const BaseEntity& otherEntity) const;

		/**
		 * @brief Checks if the asteroid intersects with something else
		 * 
		 * @details Checks if the borders of the element received are within
		 * the borders of the asteroid;
		 * 
		 * @param otherEntity Current position of the other entity
		 * being analyzed.
		 * 
		 * @return True if the two entities intersect and false otherwise.
		*/
		bool intersects(const BaseEntity& otherEntity) const;

		/**
		 * @brief Switches the two entities' speeds;
		 * 
		 * @details Switches the two entities speeds to simulate a perfectly elastic
		 * collision.
		 * 
		 * @param otherEntity Second entity involved in the collision.
		*/
		void switchSpeeds(BaseEntity& otherEntity);

		/**
		 * @brief Overload of -- operator for BaseEntity class, represents it taking damage.
		 * 
		 * @details Reduces the entity's life level by 1 point.
		*/
		void operator--(int);

		virtual ~BaseEntity();
	};
}

#endif