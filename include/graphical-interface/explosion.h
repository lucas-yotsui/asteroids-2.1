#ifndef _EXPLOSAO_H_
#define _EXPLOSAO_H_

#include "graphical-interface/animation.h"

namespace MyGUI	{
	class Explosion : public Animation	{
	private:
		/**
		 * Variable used to control wheter the explosion is already finished or not
		*/
		bool finished;

		/**
		 * @brief Sets the explosion animation as finished
		*/
		void finish();

	public:
		/**
		 * @brief Constructor for the Explosion class
		 * 
		 * @param position Initial position for the explosion
		*/
		Explosion(const sf::Vector2f& position);

		/**
		 * @brief Updates the state and position of the explosion.
		 * 
		 * @details If the current animation state has been already active for its
		 * ammount of screen frames, changes into the next one. In case this state is 
		 * the final one, the explosion is set as finished in order to be destroyed. 
		 * 
		 * @param Inherited From the base class' function header, would be used to 
		 * update the animation's position on the screen, however, since the explosion
		 * doesn't move, this parameter is not used.
		*/
		void updateAnimation(const sf::Vector2f& position) override final;

		/**
		 * @brief Informs if the animation is finished or not.
		 * 
		 * @return true if the animation is finished and false otherwise.
		*/
		bool isFinished();
	};
};

#endif