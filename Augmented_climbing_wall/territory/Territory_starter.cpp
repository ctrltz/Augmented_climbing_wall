#include <SFML/Main.hpp>

#include "../Cliker.h"
#include "objects/Territory_world.hpp"
#include "states/Territory_state.hpp"
#include "states/Territory_manager.hpp"
#include "Territory_starter.h"

using namespace Territory;

Starter::Starter() 
	: update_time (sf::seconds(1.f / Config::fps))
	, kinect (Cliker::getKinectApplication())
	, world (Config::screen_width, Config::screen_height, update_time.asSeconds(), kinect, Config::kinectControl)
	, manager(States::Type::Preparation, world, kinect, Config::kinectControl)
{ }

void Starter::start(myServer & server)
{
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

		std::vector<int> data = getClientData(server);
		for (int i = 2; i < data.size(); i += 5)
		{
			if (data[i] == 4)
			{
				manager.activateState(States::Type::Exiting);  //4 - BACK button presed (magick number from client)			
			}
		}
	}
}

std::vector<int> Starter::getClientData(myServer& server)
{
	//delay for no frizing 
	if (serverDelayClock.getElapsedTime().asMilliseconds() > 500) {
		std::vector<int> data = server.getData();
		//2 - byte contains information about presed buttons (magick number from client)
		// +=5 need becose with time delation we stack more then one message, and information about prest button will be only in one message
		serverDelayClock.restart();
		return data;
	}
}