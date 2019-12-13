#pragma once

#include <string>
#include "Territory_player.hpp"

namespace Territory
{
	struct Scoreboard
	{
	public:
		Scoreboard(Player& left, Player& right);
		void update();
		void render(sf::RenderWindow& window);
		void reset();

	private:
		std::string time_line(float seconds);
		char t_[8];
		Player& left_;
		Player& right_;
		sf::RectangleShape left_score_border, right_score_border;
		sf::Font font_;
		sf::Text left_score, right_score;
	};
}