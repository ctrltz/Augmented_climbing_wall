#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../../body_tracker.h"
#include "Territory_board.hpp"
#include "Territory_map.hpp"
#include "Territory_player.hpp"
#include "Territory_ready_button.hpp"

namespace Territory
{
	struct World
	{
	public:
		World(float width, float height, float update_time, BodyTracker& kinect, bool kinectControl);
		void processEvents();

		void render();
		void reset();
		void update();

		int width_, height_;
		float update_time;
		BodyTracker& kinect;
		bool score_changed, paused, kinectControl, use_paddle_velocity;
		sf::RenderWindow& mWindow;
		sf::Sprite bodySprite;
		sf::Texture bodyTexture;
		sf::Image bodyImage;
		Player left, right;
		Scoreboard board;
		Map map;
		ReadyButton left_ready, right_ready;
		sf::RectangleShape left_border, top_border, right_border;
	};
}