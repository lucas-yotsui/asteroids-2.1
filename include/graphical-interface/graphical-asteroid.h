#ifndef _GRAPHICAL_ASTEROID_H_
#define _GRAPHICAL_ASTEROID_H_

#include "graphical-interface/animation.h"
#include "communication/asteroid-communication.h"

namespace MyGUI	{
	class GraphicalAsteroid	: public Animation	{
	private:
		/**
		 * Size of the asteroid (Small, Medium or Large)
		*/
		short unsigned size;

		long unsigned identifier;

	public:
		/**
		 * @brief Constructor for the GraphicalAsteroid class.
		 * 
		 * @details Constructs an object of the GraphicalAsteroid class, setting it to 
		 * a specific initial position and size.
		 * 
		 * @param position Initial position in which the asteroid is initialized at;
		 * 
		 * @param asteroidSize Size of the asteroid initialized 
		*/
		GraphicalAsteroid(const CommunicationEngineWithGUI::AsteroidCommunication& asteroidData);

		/**
		 * @brief Updates the state and position of the asteroid.
		 * 
		 * @details If the current animation state has been already active for its
		 * ammount of screen frames, changes into the next one. In case this state is 
		 * the final one, it is set back to the first one starting the cycle again. Also
		 * updates the asteroid's position as it is constantly moving. 
		 * 
		 * @param position Current position of this entity on the screen.
		*/
		void updateAnimation(const sf::Vector2f& position) override final;

		/**
		 * @brief Informs the unique identifier of the graphical asteroid
		 * 
		 * @return Graphical asteroid's identifier
		*/		
		long unsigned getIdentifier() const;
	};
}

#endif