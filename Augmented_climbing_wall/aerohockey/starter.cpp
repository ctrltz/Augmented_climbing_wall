#include <SFML/Main.hpp>

#include "objects/world.hpp"
#include "states/state.hpp"
#include "states/manager.hpp"
#include "../Cliker.h"

#include "starter.h"

void starter()
{
	sf::Time update_time = sf::seconds(1.f / Config::fps);

	BodyTracker & kinect = Cliker::getKinectApplication();
	World world(Config::screen_width, Config::screen_height, update_time.asSeconds(), kinect, Config::kinectControl);
	StateManager manager(States::Type::Preparation, world, kinect, Config::kinectControl);

	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;
	while ((world.mWindow.isOpen()) && (manager.getCurrentState() != States::Type::Exiting))
	{
		manager.processEvents();
		elapsed += clock.restart();

		while (elapsed > update_time)
		{
			manager.processEvents();
			manager.update(update_time.asSeconds());
			elapsed -= update_time;
		}

		manager.render();

		// Avoid infinite FPS
		sf::sleep(sf::microseconds(1));
	}
}