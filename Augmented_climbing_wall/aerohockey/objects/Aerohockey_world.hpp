#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../config/Aerohockey_config.hpp"
#include "../../body_tracker.h"
#include "../../util.hpp"
#include "Aerohockey_board.hpp"
#include "Aerohockey_player.hpp"
#include "Aerohockey_puck.hpp"
#include "Aerohockey_ready_button.hpp"

namespace Aerohockey
{
	struct World
	{
	public:
		World(float width, float height, float update_time, BodyTracker& kinect, bool kinectControl);
		void processEvents();

		void collide_objects(Paddle& first, Puck& second);
		void render();
		void reset();
		bool goal_scored();
		void update();

		int width_, height_;
		float update_time;
		bool score_changed, kinectControl;
		sf::RenderWindow& mWindow;
		sf::Sprite background;
		sf::Texture bg_texture, left_hand_texture, right_hand_texture;
		sf::SoundBuffer scored, hit, wall;
		sf::Sound scored_sound, hit_sound, wall_sound;
		sf::Vector2f puck_velocity;
		Puck puck;
		Player left, right;
		Scoreboard board;
		ReadyButton left_ready, right_ready;
		sf::RectangleShape left_border, top_border, right_border;
	};
}