#ifndef _SHOT_H_
#define _SHOT_H_

#include "engine/base-entity.h"

#define SHOT_VECTORIAL_SPEED_MODULE 300.f
#define SHOT_RADIUS 20.f

namespace MyEngine	{
	class Shot final : public BaseEntity	{
	private:
		/**
		 * @brief Calculates the vectorial speed components.
		 * 
		 * @details Applies basic trigonometry to determine the components for the vectorial
		 * speed of the shot based on a defined module for such speed.
		 * 
		 * @return std::pair<float, float> containing the components of the speed. 
		*/
		std::pair<float, float> calculateSpeedComponents(const std::pair<float, float>& initialPosition, const std::pair<float, float>& reference);

		/**
		 * Angle between the X axis and the shot's trajectory axis
		*/
		float angle;

		/**
		 * Shot's unique identifier
		*/
		unsigned identifier;

		/**
		 * Identifier assigner, incremented everytime a shot is created
		*/
		inline static unsigned idAssigner = 0;

	public:
		/**
		 * @brief Constructor for the Shot class.
		 * 
		 * @details Constructs a Shot object at a given initial position and direction
		 * 
		 * @param initialPosition std::pair<float, float> representing the starting position 
		 * for the shot
		 * @param direction std::pair<float, float> representing the direction of the shot.
		*/
		Shot(const std::pair<float, float>& initialPosition, const std::pair<float, float>& direction);

		/**
		 * @brief Update the current position of the shot
		 * 
		 * @details Update the shot's current position by calculating the
		 * time elapsed since the last update and the shot's speed. This
		 * speed is kept in a pair, representing a two-dimensional vector with the 
		 * one-dimensional speeds in the axis X and Y. the calculations are then
		 * performed in each axis and the results are put together in a std::pair, also 
		 * representing a two-dimensonal vector.
		 * 
		 * @param elapsedTime Time passed since last update.
		*/
		void update(float timeElapsed) override final;

		/** 
		 * @brief Inform the angle between the X axis and the shot's trajectory axis
		 * 
		 * @return Angle stored in the member variable "angle" 
		*/
		float getAngle() const;

		/**
		 * @brief Inform the unique identifier of the shot
		 * 
		 * @return Shot's identifier
		*/
		long unsigned getIdentifier() const;
	};
}

#endif