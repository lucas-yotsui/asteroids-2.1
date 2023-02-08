#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <iostream>
#include <memory>
#include <list>
#include "engine/user-commands.h"
#include "engine/player.h"
#include "engine/asteroid.h"
#include "engine/shot.h"
#include "communication/asteroid-communication.h"
#include "communication/shot-communication.h"

namespace MyEngine	{
	class Engine {
	private:
		/**
		 * @brief Constructor for the Engine class
		*/
		Engine();

		/**
		 * @brief Copy constructor for the class Engine
		 * 
		 * @details This kind of constructor is deleted, as it isn't allowed for
		 * 2 instances of a singleton to exist within the program
		*/
		Engine(const Engine& other) = delete;

		/**
		 * @brief Atribution operator for the class Engine
		 * 
		 * @details This kind of operator is deleted, as it isn't allowed for 
		 * 2 instances of a singleton to exist within the program and therefore 
		 * copy one into the other is impossible
		*/
		void operator=(const Engine& other) = delete;

		/**
		 * Smart pointer to the single instance of this class existent in the 
		 * program 
		*/
		inline static std::shared_ptr<Engine> singleton = nullptr;

		/**
		 * Object of type shared_ptr<Player> used to refer to the singleton 
		 * player entity. 
		 * 
		 * @note This entity is kept here through a smart pointer, therefore 
		 * all of its members must be accessed through a -> operator, instead 
		 * of the usual . operator
		*/
		std::shared_ptr<Player> player = Player::getInstance();

		/**
		 * Vector of smart pointers to the asteroids
		*/
		std::vector<std::shared_ptr<Asteroid>> asteroids;

		/**
		 * Vector of smart pointers to the shots
		*/
		std::vector<std::shared_ptr<Shot>> shots;

		/**
		 * List containing dead asteroids' identifiers
		 * 
		 * @note Used for communication with the graphical interface
		*/
		std::list<long unsigned> deadAsteroids;

		/**
		 * List containing dead shots' identifiers
		 * 
		 * @note Used for communication with the graphical interface
		*/
		std::list<long unsigned> deadShots;

		/**
		 * Variable used to store the time of last call of the shot fired
		*/
		float timeSinceLastShot;

		/**
		 * Variable used to control whether the game is paused or not
		*/
		bool paused;

		/**
		 * Variable used to store the ammount of points gathered by the player
		*/
		unsigned points;

		/**
		 * @brief Checks for collision among asteroids 
		 * 
		 * @details Scans the entirety of the vector contatining the asteroids
		 * looking for a collision between them and, upon findning one, calls for 
		 * the asteroid's function that switches their speeds, simulating a 
		 * perfectly elastic colision.
		*/
		void collisionAmongAsteroids();

		/**
		 * @brief Checks for collisions between an asteroid and a player.
		 * 
		 * @details Scans the entirety of the vector containing the asteroids
		 * looking for a collision between one of them and a player and, upon 
		 * finding one, calls for the asteroid's function that switches its direction
		 * and for both the player's and the asteroid's function that diminishes their 
		 * life levels.
		*/
		void collisionWithPlayer();

		/**
		 * @brief Checks for collisions between an asteroid and a shot.
		 * 
		 * @details Scans the entirety of the vectors containing the asteroids and
		 * the one containing the shots for collisions between those two entities and,
		 * upon finding one, destroys the shot and diminishes the asteroids life. 
		*/
		void collisionShotAndAsteroid();

		/**
		 * @brief Checks for asteroids are completely depleted of their life
		 * 
		 * @details Scans the entire asteroids vector to look for asteroids that
		 * are completely depleted of their life and upon finding, destroys them and 
		 * creates asteroids of lower levels or just destroy if they are of the lowest 
		 * level already. 
		*/
		void asteroidBreakdown(unsigned long asteroidPosition);

		/**
		 * @brief Updates all of the elements contained in the engine
		 * 
		 * @details Calls for all of the elements' update functions
		*/
		void update(const std::pair<float, float>& mousePosition);

		/**
		 * @brief Creates a shot if the player is currently shooting.
		*/
		void shoot(const std::pair<float, float>& direction);

	public:
		/**
		 * @brief Constructs the singleton and/or return a shared_ptr to it.
		 * 
		 * @details Tests if the singleton is already built, if it isn't 
		 * constructs it, allocating it in the heap and assigning its control
		 * to the class' internal smart pointer. In any case, returns the class'
		 * smart pointer at the end.
		*/
		static std::shared_ptr<Engine> getInstance();

		/**
		 * @brief Informs the current positions of the player in the engine
		 * 
		 * @details Calls for the getPosition method of the player storing it at an 
		 * object of type std::pair<float, floa	GUI->updateAsteroids(engine->getDeadAsteroids(), engine->getNewAsteroids(), engine->getAsteroidsPositions());
			GUI->updatePlayer(engine->getPlayerPosition());
			GUI->updateShots(engine->getDeadShots(), engine->getNewShots(), engine->getShots());t> so it can be returned at the end
		 * 
		 * @return Position of the player
		*/
		std::pair<float, float> getPlayerPosition() const;

		/**
		 * @brief Informs the current positions of all the asteroids in the engine
		 * 
		 * @details Calls for the getPosition method of all the asteroids at the 
		 * asteroids vector at the moment of the calling, storing them at an object 
		 * of type std::list<std::pair<float, float>> so they can all be returned at 
		 * the end
		 * 
		 * @return List containing the positions of all the asteroids
		*/
		std::list<CommunicationEngineWithGUI::AsteroidCommunication> getAsteroids() const;

		/**
		 * @brief Informs the current positions of all the shots in the engine
		 * 
		 * @details Calls for the getPosition method of all the shots at the 
		 * shots vector at the moment of the calling, storing them at an object 
		 * of type std::list<std::pair<float, float>> so they can all be returned at 
		 * the end
		 * 
		 * @return List containing the positions of all the shots
		*/
		std::list<CommunicationEngineWithGUI::ShotCommunication> getShots() const;

		/**
		 * @brief Inform the identifiers of all asteorids that have been exploded since the 
		 * last call of this function
		 * 
		 * @details Copy the identifiers stored in the deadAsteroids member to a temporary 
		 * list, clear the deadAsteroids list and return the temporary one to the caller
		 * 
		 * @return List containing the identifiers of the exploded asteroids
		*/
		std::list<long unsigned> getDeadAsteroids();

		/**
		 * @brief Inform the identifiers of all shots that have exploded since the last call 
		 * of this function
		 * 
		 * @details Copy the identifiers stored in the deadShots member to a temporary 
		 * list, clear the deadShots list and return the temporary one to the caller
		 * 
		 * @return List containing the identifiers of the exploded shots
		*/
		std::list<long unsigned> getDeadShots();

		/**
		 * @brief Informs if the engine is currently paused
		 * 
		 * @return True in case the engine is paused and false otherwise
		*/
		bool isPaused() const;

		/**
		 * @brief Inform how many points the player has gathered so far
		 * 
		 * @return Ammount of points gathered by the player
		*/
		unsigned getPoints() const;

		/**
		 * @brief Inform how much life the player currently has
		 * 
		 * @return Current life level of the player
		*/
		unsigned short getPLayerLife() const;

		/**
		 * @brief Inform whether the player is moving or not
		 * 
		 * @return true if the player os moving in any direction and false 
		 * otherwise
		*/
		bool playerMoving() const;

		/**
		 * @brief Runs the engine of the game
		 * 
		 * @details Calls for the update methods of all the asteroids and of the player,
		 * checks for collisions among the asteroids and of them with the player, checks
		 * all of the shots for collisions with the asteroids, creates more asteroids if 
		 * needed and checks if the game is over.
		*/
		bool runEngine(const std::pair<float, float>& mousePosition, const std::list<unsigned short>& commands);

	};
}

#endif