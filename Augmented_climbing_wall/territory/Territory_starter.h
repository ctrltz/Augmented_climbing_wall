#pragma once

#include "../server.h"
#include "../body_tracker.h"
#include "objects/Territory_world.hpp"
#include "states/Territory_manager.hpp"

namespace Territory
{
	struct Starter
	{
	public:
		Starter();
		void start(myServer& server);

	private:
		// Territory
		BodyTracker& kinect;
		sf::Time update_time;
		World world;
		StateManager manager;

		// Server communication
		sf::Clock serverDelayClock;
		std::vector<int> getClientData(myServer& server);
	};
}