#ifndef _ANIMACAO_H_
#define _ANIMACAO_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#define RELACAO_FRAME_ANIMACAO_FRAME_REAL 50

namespace MyGUI	{
	enum TypesOfAnimation	{
		SMALL_ASTEROID = 0,
		MEDIUM_ASTEROID = 1,
		LARGE_ASTEROID = 2,
		EXPLOSION = 3,
		SHOT = 4
	};

	class Animation : public sf::Sprite {
	protected:
		/**
		 * Variable used to store the current texture being displayed 
		*/
		short unsigned currentTexture;

		/**
		 * Variable used to count screen frames passed and control the 
		 * animation frames
		*/
		short unsigned frameCounter;
		
		/**
		 * @brief Switches into the next texture of the animation.
		 * 
		 * @param typeOfAnimation Variable that informs to which kind the
		 * animation belongs. Used to access the correct row of matrix of 
		 * textures. 
		*/
		void switchTexture(unsigned short typeOfAnimation);

		/**
		 * @brief Loads the textures into the vector used to store them.
		 * 
		 * @details This function is executed only when the first object of a
		 * class that inherits this one is instantiated. It loads into the memory 
		 * all of the textures of all the kinds of animations and stores them in 
		 * the static vector "textures".
		*/
		void loadTextures();

		/**
		 * Static variable used to control wheter the loadTextures function has 
		 * already been called
		*/
		inline static bool texturesAlreadyInitialized = false;
		
		/**
		 * Static member of type std::vector<std::vector<sf::Texture>> used to store
		 * all of the textures used in the program by all of the animations. This object 
		 * is unique for all of the objects of all of the classes that inherit this one. 
		 * This approach was chosen to minimize the ammount of similar assets allocated, 
		 * reducing memory waste.
		*/
		inline static std::vector<std::vector<sf::Texture>> textures {5};
		

	public:
		
		/**
		 * @brief Default constructor for the Animation class
		 * 
		 * @details Constructs an object of the Animation class, setting it to a 
		 * specified position on the screen.  
		*/
		Animation(const sf::Vector2f& position);
		
		/**
		 * @brief Purely virtual function that makes this class abstract.When overriden 
		 * will update the animation's position and state, calling the switchTexture function 
		 * when necessary.
		 * 
		 * @param position Current position of the animation
		 * 
		*/
		virtual void updateAnimation(const sf::Vector2f& position) = 0;	

		virtual ~Animation();
	};
}

#endif