#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#include <memory>
#include <utility>
#include "engine/base-entity.h"
#include "engine/user-commands.h"

#define PLAYER_SPEED 200.f
#define DRAG 50.f
#define PLAYER_RADIUS 50.f
#define COOLDOWN_TIME 2.f

namespace MyEngine	{
	/**
	 * @brief Class that represents the player on the game engine.
	 * 
	 * @note This class follows the singleton pattern, which means
	 * it is built in such a way that only one instance of it can exist 
	 * in a program
	*/
	class Player final : public BaseEntity	{
	private:
		/**
		 * @brief Constructor for the Player class
		 * 
		 * @details Constructs a player object at the (0, 0) position and standing still
		*/
		Player();

		/**
		 * @brief Copy constructor for the class Player
		 * 
		 * @details This kind of constructor is deleted, as it isn't allowed for
		 * 2 instances of a singleton to exist within the program
		*/
		Player(const Player& other) = delete;

		/**
		 * @brief Atribution operator for the class Player
		 * 
		 * @details This kind of operator is deleted, as it isn't allowed for 
		 * 2 instances of a singleton to exist within the program and therefore 
		 * copy one into the other is impossible
		*/
		void operator=(const Player& other) = delete;

		/**
		 * Smart pointer to the single instance of this class existent in the 
		 * program 
		*/
		inline static std::shared_ptr<Player> singleton = nullptr;
		
		/**
		 * Variable to control wheter the player is moving or not
		*/
		bool accelerating; 
		
		/**
		 * Variable to control whether the player is shooting or not
		*/
		bool shooting;

		/**
		 * Variable to control the player's invulnerability time after being hit 
		 * by an asteroid
		*/
		unsigned invulnerabilityCounter;
		
		/**
		 * Variable to control the angle between the ship and the horizontal axis
		*/
		float angle;

	public:
		/**
		 * @brief Constructs the singleton and/or return a shared_ptr to it.
		 * 
		 * @details Tests if the singleton is already built, if it isn't 
		 * constructs it, allocating it in the heap andn assigning its control
		 * to the class' internal smart pointer. In any case, returns the class'
		 * smart pointer at the end.
		*/
		static std::shared_ptr<Player> getInstance();

		/**
		 * @brief Update the current position of the player 
		 * 
		 * @details Update the player's current position by calculating the
		 * time elapsed since the last update and the player's speed. This
		 * speed is kept in a pair, representing a two-dimensional vector with the 
		 * one-dimensional speeds in the axis X and Y. the calculations are then
		 * performed in each axis and the results are put together in a std::pair, also 
		 * representing a two-dimensonal vector.
		 * 
		 * @param elapsedTime Time passed since last update.
		*/
		void update(float timeElapsed) override final;

		void updateMovementDirection(const std::pair<float, float>& mousePosition);

		/**
		 * @brief Communicates with the graphical user interface, translating inputs
		 * from peripherals into commands of the game.
		 * 
		 * @details Receives a single unsigned short parameter that contains a unique message
		 * corresponding to a specific command such as move in a given direction, rotate the
		 * ship or shoot.
		 * 
		 * @param command Message that specifies the command inputted by the user. 
		*/
		void takeCommand(unsigned short command);

		/**
		 * @brief Informs if the player is currently shooting.
		 * 
		 * @return true if it is currently shooting and false otherwise
		*/
		bool isShooting() const;

		/**
		 * @brief Informs if the player is currenty invulnerable.
		 * 
		 * @return true if the player is currently invulnerable and false otherwise.
		*/
		bool isInvulnerable() const;

		/**
		 * @brief Informs if the player is moving or not
		 * 
		 * @return true if the player is moving in any direction and false otherwise
		*/
		bool isMoving() const;

		/**
		 * @brief Resets the player's invulnerability counter. Meaning it just took 
		 * a hit
		*/
		void invulnerabilityReset();
	};
}

#endif