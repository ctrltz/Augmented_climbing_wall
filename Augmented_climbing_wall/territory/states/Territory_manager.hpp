#pragma once

#include <unordered_map>

#include "../../body_tracker.h"
#include "../objects/Territory_world.hpp"
#include "Territory_state.hpp"

namespace Territory
{
	using StateContainer = std::unordered_map<States::Type, State*>;

	struct StateManager
	{
		StateManager(const States::Type& initial, World& world, BodyTracker& kinect, bool kinectControl);
		~StateManager();

		template <typename T>
		void registerState(const States::Type state, World& world);

		void activateState(const States::Type state);
		States::Type getCurrentState() const;
		void processEvents();
		void update(const float delta);
		void render();

	private:
		States::Type current_state;
		StateContainer container;
		World& world;
		BodyTracker& kinect;
		bool kinectControl;
	};
}