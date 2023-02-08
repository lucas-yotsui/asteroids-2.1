#ifndef _GRAPHICAL_INTERFACE_H_
#define _GRAPHICAL_INTERFACE_H_

#include <vector>
#include <memory>
#include <list>
#include <utility>
#include <fstream>
#include "graphical-interface/graphical-player.h"
#include "graphical-interface/graphical-asteroid.h"
#include "graphical-interface/graphical-shot.h"
#include "graphical-interface/explosion.h"
#include "graphical-interface/hud.h"
#include "graphical-interface/camera.h"
#include "engine/user-commands.h"
#include "communication/asteroid-communication.h"
#include "communication/shot-communication.h"

namespace MyGUI	{
	class GraphicalInterface	{
	private:
		/**
		 * @brief Constructor for the GraphicalInterface class
		*/
		GraphicalInterface(const std::list<CommunicationEngineWithGUI::AsteroidCommunication>& asteroidsPositions);

		/**
		 * @brief Copy constructor for the class GraphicalInterface
		 * 
		 * @details This kind of constructor is deleted, as it isn't allowed for
		 * 2 instances of a singleton to exist within the program
		*/
		GraphicalInterface(const GraphicalInterface& other) = delete;

		/**
		 * @brief Atribution operator for the class GraphicalInterface
		 * 
		 * @details This kind of operator is deleted, as it isn't allowed for 
		 * 2 instances of a singleton to exist within the program and therefore 
		 * copy one into the other is impossible
		*/
		void operator=(const GraphicalInterface& other) = delete;
		
		/**
		 * Smart pointer to the single instance of this class existent in the 
		 * program 
		*/
		inline static std::shared_ptr<GraphicalInterface> singleton = nullptr;

		std::shared_ptr<GraphicalPlayer> player = GraphicalPlayer::getInstance();

		std::vector<std::shared_ptr<GraphicalAsteroid>> graphicalAsteroids;

		std::vector<std::shared_ptr<GraphicalShot>> shots;
		
		std::vector<std::shared_ptr<Explosion>> explosions;

		sf::RenderWindow window;

		Camera camera;

		HUD hud;

		/**
		 * Variable used to store the player's highest score ever
		*/
		unsigned highScore;

	public:
		/**
		 * @brief Constructs the singleton and/or return a shared_ptr to it.
		 * 
		 * @details Tests if the singleton is already built, if it isn't 
		 * constructs it, allocating it in the heap and assigning its control
		 * to the class' internal smart pointer. In any case, returns the class'
		 * smart pointer at the end.
		*/
		static std::shared_ptr<GraphicalInterface> getInstance(const std::list<CommunicationEngineWithGUI::AsteroidCommunication>& asteroidsPositions);

		std::list<unsigned short> processUserInputs();

		void updateAsteroids(const std::list<long unsigned>& deadAsteroids, const std::list<CommunicationEngineWithGUI::AsteroidCommunication>& asteroidPositions);

		void updateShots(const std::list<long unsigned>& deadShots, const std::list<CommunicationEngineWithGUI::ShotCommunication>& shotPositions);

		void updateExplosions();

		void updatePlayer(const std::pair<float, float>& playerCurrentposition, bool moving);

		void updateHUD(unsigned short life, unsigned points);

		void render(float elapsedTime);

		void gameOver(unsigned points);

		bool isWindowOpen() const;

		std::pair<float, float> getMouseCoordinates() const;
	};
};

#endif