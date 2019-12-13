#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../body_tracker.h"
#include "paddle.hpp"

namespace Aerohockey
{
	struct Player
	{
	public:
		Player(float radius, sf::Color color, float update_time, BodyTracker& kinect, bool left, bool kinectControl);
		~Player();
		void handleInput();
		void update();
		void render(sf::RenderWindow& window);
		std::vector<Paddle>& paddles();
		unsigned score();
		void scored();
		void reset();
		int n_limbs;

	private:
		bool left, kinectControl;
		BodyTracker& kinect;
		std::vector<Paddle> paddles_;
		unsigned score_;
	};
}