#ifndef _GRAPHICAL_SHOT_H_
#define _GRAPHICAL_SHOT_H_

#include "graphical-interface/animation.h"
#include "communication/shot-communication.h"

namespace MyGUI	{
	class GraphicalShot : public Animation	{
	private:
		long unsigned identifier;
		inline static long unsigned idAssigner = 0;

	public:
		GraphicalShot(const CommunicationEngineWithGUI::ShotCommunication& initialPosition);
		void updateAnimation(const sf::Vector2f& position) override final;
		long unsigned getIdentifier() const;
	};
}

#endif