#pragma once

#include <SFML/Graphics.hpp>
#include "../../body_tracker.h"

namespace Aerohockey
{
	struct Paddle
	{
	public:
		Paddle();
		Paddle(float radius, sf::Color color, sf::Vector2f position, float velocity, float update_time,
			sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
		void update(BodyTracker& kinect, const Limbs::Type type, bool left, bool kinectControl);
		void render(sf::RenderWindow& window, bool left);
		void handleInput();
		void moveTo(sf::Vector2f position);
		sf::CircleShape shape();
		float radius();
		sf::Vector2f& position();
		sf::Vector2f& velocity();

	private:
		sf::CircleShape shape_;
		float radius_;
		float update_time;
		sf::Color color_;
		sf::Vector2f position_;
		sf::Vector2f current_velocity_;
		bool valid_;
		float velocity_, vx_, vy_;
		sf::Keyboard::Key const up_, down_, left_, right_;
	};
}