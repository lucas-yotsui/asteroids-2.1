#ifndef _GAME_H_
#define _GAME_H_

#include "engine/engine.h"
#include "graphical-interface/graphical-interface.h"

namespace MyGame	{
	class Game	{
	private:
		std::shared_ptr<MyEngine::Engine> engine;
		std::shared_ptr<MyGUI::GraphicalInterface> GUI;

		void runGame();
	public:
		Game();
	};
}

#endif