#pragma once

#include <string>
#include "Aerohockey_player.hpp"
#include "../config/Aerohockey_config.hpp"
#include "../../util.hpp"

namespace Aerohockey
{
	struct Scoreboard
	{
	public:
		Scoreboard(Player* left, Player* right, float gameDuration);
		void update(float delta, bool& score_changed);
		void render(sf::RenderWindow& window);
		void reset();

	private:
		std::string time_line(float seconds);
		void align_center(sf::Text& text, sf::RectangleShape& border);
		char t_[8];
		Player* left_;
		Player* right_;
		sf::RectangleShape left_score_border, right_score_border, time_border;
		float remainingTime_, gameDuration_;
		sf::Font font_;
		sf::Text timer_, left_score, right_score;
	};
}