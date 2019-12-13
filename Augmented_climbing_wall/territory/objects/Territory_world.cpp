#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>

#include "Territory_world.hpp"
#include "../../mainWindow.h"
#include "../../util.hpp"

using namespace std;
using namespace Territory;

World::World(float width, float height, float update_time, BodyTracker & kinect, bool kinectControl)
    : width_(width)
    , height_(height)
    , update_time (update_time)
	, kinect (kinect)
    , score_changed(false)
    , paused(false)
    , kinectControl (kinectControl)
    , use_paddle_velocity(false)
    , mWindow(MainWindow::getWindow())
    , left (height / 20, Config::red, update_time, kinect, true, kinectControl)
    , right (height / 20, Config::green, update_time, kinect, false, kinectControl)
    , board (left, right)
	, map (width, height, 30, left, right)
    , left_ready (sf::Vector2f(width / 4, height / 2), sf::Vector2f(width / 10, width / 10))
    , right_ready (sf::Vector2f(width * 3 / 4, height / 2), sf::Vector2f(width / 10, width / 10))
{
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(true);

    left_border.setPosition(0.f, 0.f);
    left_border.setSize(sf::Vector2f(2.f, height_ - 60.f));
    left_border.setFillColor(sf::Color(204, 0, 0));

    right_border.setPosition(798.f, 0.f);
    right_border.setSize(sf::Vector2f(2.f, height_ - 60.f));
    right_border.setFillColor(sf::Color(0, 102, 0));

    left_border.setPosition(0.f, 0.f);
    left_border.setSize(sf::Vector2f(800.f, 2.f));
    left_border.setFillColor(sf::Color::White);

	if (!bodyTexture.loadFromFile("territory/media/textures/tile.jpg", sf::IntRect(0, 0, 97, 97)))
	{
		std::cout << "Failed to create body texture\n";
	}
	map.setTexture(bodyTexture);
	bodySprite.setTexture(bodyTexture);
}


void World::processEvents()
{
    if (!kinectControl)
    {
        left.handleInput();
        right.handleInput();
    }
}


void World::update()
{
	map.update(kinect, kinectControl);
    if (!kinectControl)
    {
        left.update(map);
        right.update(map);
    }
}

void World::render()
{
    mWindow.clear();

	map.render(mWindow);
	for (int i = 0; i < left.paddles().size(); i++)
	{
		mWindow.draw(left.paddles()[i].shape());
	}
	for (int i = 0; i < right.paddles().size(); i++)
	{
		mWindow.draw(right.paddles()[i].shape());
	}
	//mWindow.draw(bodySprite);

    mWindow.display();
}


void World::reset()
{
    left.reset();
    right.reset();
    board.reset();
}
