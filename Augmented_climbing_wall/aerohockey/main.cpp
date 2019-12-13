#include <SFML/Main.hpp>

#include <iostream>

#include "config/config.hpp"
#include "easylogging/easylogging++.h"
#include "objects/world.hpp"
#include "states/state.hpp"
#include "states/manager.hpp"

INITIALIZE_EASYLOGGINGPP

int main()
{
    // Configure logging
    el::Configurations defaultConf;
    defaultConf.setToDefault();

    defaultConf.setGlobally(el::ConfigurationType::Enabled, "true");
    defaultConf.setGlobally(el::ConfigurationType::Filename, "game.log");
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime [%level] - %msg");
    defaultConf.setGlobally(el::ConfigurationType::ToFile, "true");
    defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "true");

    el::Loggers::reconfigureLogger("default", defaultConf);

    sf::Time update_time = sf::seconds(1.f / Config::fps);

	// Initialize Kinect tracking
    BodyTracker kinect;
	kinect.Run();

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

    return EXIT_SUCCESS;
}
