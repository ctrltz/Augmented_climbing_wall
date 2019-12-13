#include <SFML/Graphics.hpp>

#include "../../body_tracker.h"
#include "Territory_map.hpp"
#include "Territory_player.hpp"

using namespace Territory;

Player::Player (float radius, sf::Color color, float update_time, BodyTracker & kinect, bool left, bool kinectControl)
      : kinect (kinect), left (left), kinectControl (kinectControl), score_(0)
{
    if (kinectControl)
    {
        n_limbs = 4;
        for (int i = 0; i < n_limbs; i++)
        {
            paddles_.push_back(Paddle(radius, color, sf::Vector2f(0.f, 0.f), 0.f, 0.f,
                                      sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D));
        }
    }
    else
    {
        n_limbs = 1;
        if (left)
        {
            paddles_.push_back(Paddle(radius, color, sf::Vector2f(0.f, 0.f), 800.f, update_time,
                                      sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D));
        }
        else
        {
            paddles_.push_back(Paddle(radius, color, sf::Vector2f(0.f, 0.f), 800.f, update_time,
                                      sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right));
        }
    }
}


Player::~Player()
{

}

void Player::handleInput()
{
    for (int i = 0; i < n_limbs; i++)
    {
        paddles_[i].handleInput();
    }
}

void Player::update(Map & map)
{
    for (int k = 0; k < n_limbs; k++)
    {
        paddles_[k].update(kinect, static_cast<Limbs::Type>(k), left, kinectControl);

		int size = paddles_[k].radius() / map.size();
		int x_center = paddles_[k].position().x / map.size();
		int y_center = paddles_[k].position().y / map.size();
		
		for (int i = x_center - size; i <= x_center + size; i++)
		{
			for (int j = y_center - size; j <= y_center + size; j++)
			{
				map.setEnabled(i, j, left);
			}
		}
    }
}

std::vector<Paddle> & Player::paddles()
{
    return paddles_;
}

unsigned Player::score()
{
    return score_;
}

void Player::capturedCell()
{
    score_++;
}

void Player::lostCell()
{
    score_--;
}

void Player::reset()
{
    score_ = 0;
}
