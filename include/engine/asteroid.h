#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include <utility>
#include <random>
#include "engine/base-entity.h"

#define ASTEROID_MIN_SPEED 20.f
#define ASTEROID_MAX_SPEED 60.f
#define ASTEROID_RADIUS 50.f

namespace MyEngine	{
	enum Levels {
		SMALL = 0,
		MEDIUM = 1,
		LARGE = 2
	};

	class Asteroid final : public BaseEntity	{
	private:
		/**
		 * Interval containing the possible distances to the player at which a new
		 * asteroid can be initialized
		*/
		inline static auto initialDistance = std::uniform_real_distribution(1000.f, 2500.f);
		
		/**
		 * Interval containing the available positions to be accessed in the 
		 * sideOptions vector
		*/
		inline static auto sidePicker = std::uniform_int_distribution(0, 1);
		
		/**
		 * Vector used to define if the distance to the player in which a new 
		 * asteroid is initialized will be positive or negative.
		*/
		inline static const std::vector<float> sideOptions = {-1, 1};

		/**
		 * Random number generator to define the asteroid's initial speed
		*/
		inline static std::default_random_engine generator;

		/**
		 * Delimiter of the interval in which the initial speed of the asteroid
		 * must be contained
		*/
		inline static std::uniform_real_distribution<float> speedRange{ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED};

		/**
		 * Asteroid's level
		*/
		short level;

		/**
		 * Asteroid's unique identifier
		*/
		unsigned identifier;

		/**
		 * Identifier assigner, incremented everytime an asteroid is created
		*/
		inline static unsigned idAssigner = 0;

	public:
		/**
		 * @brief Contructor for the Asteroid class.
		 * 
		 * @param initialPosition Position in which the player is currently at or 
		 * position in which the large asteroid that originated smaller ones was at.
		 * 
		 * @param lvl Level of the asteroid being created;
		*/
		Asteroid(const std::pair<float, float>& initialPosition, short lvl);

		/**
		 * @brief Update the current position of the asteroid
		 * 
		 * @details Update the asteroid's current position by calculating the
		 * time elapsed since the last update and the asteroid's speed. This
		 * speed is kept in a pair, representing a two-dimensional vector with the 
		 * one-dimensional speeds in the axis X and Y. the calculations are then
		 * performed in each axis and the results are put together in a std::pair, also 
		 * representing a two-dimensonal vector.
		 * 
		 * @param elapsedTime Time passed since last update.
		*/
		void update(float timeElapsed) override final;

		/**
		 * @brief Inform the current level of the asteroid.
		 * 
		 * @return Asteroid's current level.
		*/
		unsigned short getLevel() const;

		/**
		 * @brief Inform the unique identifier of the asteroid
		 * 
		 * @return Asteroid's identifier
		*/
		unsigned getIdentifier() const;
	};
}

#endif