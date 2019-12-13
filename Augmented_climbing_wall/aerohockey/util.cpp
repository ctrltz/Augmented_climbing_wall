#include <cstdlib>
#include <cmath>
#include <iostream>

#include "config/config.hpp"
#include "util.hpp"

constexpr auto PI = 3.14159265358979f;

float len2 (sf::Vector2f const v)
{
    return v.x * v.x + v.y * v.y;
}


float dot (sf::Vector2f const v1, sf::Vector2f const v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}


float dist2 (sf::Vector2f const & p1, sf::Vector2f const & p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

sf::Vector2f get_initial_velocity()
{
	int angle = std::rand() % 360;

	// Avoid too vertical directions
	if (((angle > 60) && (angle < 150)) || ((angle > 240) && (angle < 300)))
	{
		angle = (angle + 90) % 360;
	}
	
	return sf::Vector2f(cos(PI * angle / 180), sin(PI * angle / 180)) * Aerohockey::Config::initial_puck_velocity;
}