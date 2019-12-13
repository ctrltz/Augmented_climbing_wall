#pragma once

#include <unordered_map>

#include "../../body_tracker.h"
#include "../objects/Aerohockey_world.hpp"
#include "Aerohockey_state.hpp"

namespace Aerohockey
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
		BodyTracker& kinect;
		World& world;
		bool kinectControl;
	};
}