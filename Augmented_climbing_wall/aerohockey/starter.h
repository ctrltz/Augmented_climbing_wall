#pragma once

#include "../server.h"
#include "../body_tracker.h"
#include "objects/world.hpp"
#include "states/manager.hpp"

namespace Aerohockey
{
	struct Starter
	{
	public:
		Starter();
		void start(myServer& server);

	private:
		// Aerohockey
		BodyTracker& kinect;
		sf::Time update_time;
		World world;
		StateManager manager;

		// Server communication
		sf::Clock serverDelayClock;
		std::vector<int> getClientData(myServer& server);
	};
}