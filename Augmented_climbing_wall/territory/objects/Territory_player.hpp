#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../body_tracker.h"
#include "Territory_paddle.hpp"

namespace Territory
{
	struct Map;

	struct Player
	{
	public:
		Player(float radius, sf::Color color, float update_time, BodyTracker& kinect, bool left, bool kinectControl);
		~Player();
		void handleInput();
		void update(Map& map);
		std::vector<Paddle>& paddles();
		unsigned score();
		void capturedCell();
		void lostCell();
		void reset();
		int n_limbs;

	private:
		BodyTracker& kinect;
		bool left, kinectControl;
		std::vector<Paddle> paddles_;
		unsigned score_;
	};
}