#ifndef _GRAPHICAL_PLAYER_H_
#define _GRAPHICAL_PLAYER_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include <numbers>

namespace MyGUI	{
	/**
	 * @brief Class that represents the player on the Graphical Interface.
	 * 
	 * @note This class follows the singleton pattern, which means
	 * it is built in such a way that only one instance of it can exist 
	 * in a program
	*/
	class GraphicalPlayer : public sf::Sprite	{
	private:
		/**
		 * @brief Contructor for the GraphicalPlayer class
		 * 
		 * @details Constructs a player object at the (0, 0) position 
		*/
		GraphicalPlayer();

		/**
		 * @brief Copy constructor for the class GraphicalPlayer
		 * 
		 * @details This kind of constructor is deleted, as it isn't allowed for
		 * 2 instances of a singleton to exist within the program
		*/
		GraphicalPlayer(const GraphicalPlayer& other) = delete;

		/**
		 * @brief Atribution operator for the class GraphicalPlayer
		 * 
		 * @details This kind of operator is deleted, as it isn't allowed for 
		 * 2 instances of a singleton to exist within the program and therefore 
		 * copy one into the other is impossible
		*/
		void operator=(const GraphicalPlayer& other) = delete;

		/**
		 * Smart pointer to the single instance of this class existent in the 
		 * program 
		*/
		inline static std::shared_ptr<GraphicalPlayer> singleton = nullptr;

		/**
		 * Player's ship texture
		*/
		std::vector<sf::Texture> textures;

	public:
		/**
		 * @brief Constructs the singleton and/or return a shared_ptr to it.
		 * 
		 * @details Tests if the singleton is already built, if it isn't 
		 * constructs it, allocating it in the heap andn assigning its control
		 * to the class' internal smart pointer. In any case, returns the class'
		 * smart pointer at the end.
		*/
		static std::shared_ptr<GraphicalPlayer> getInstance();

		/**
		 * @brief Updates the player's current position and orientation.
		 * 
		 * @details Places this graphical representation of the player on the 
		 * position determined by the game engine. Besides, rotates the ship, 
		 * pointing it to the mouse, so that the player can see where it is 
		 * aiming at.
		 * 
		 * @param currentPosition Engine's player current position
		 * @param mousePosition Mouse current position on the window
		*/
		void update(const std::pair<float, float>& currentPosition, const std::pair<float, float>& mousePosition, bool moving);

	};
}

#endif