#include <cstdlib>
#include <cmath>
#include <direct.h> // _getcwd
#include <iostream>

#include "config/config.hpp"
#include "util.hpp"

std::string getcwd_string() {
	char* buffer;

	if ((buffer = _getcwd(NULL, 0)) == NULL)
	{
		std::cout << "Failed to retrieve CWD, problems with texture loading may occur.\n";
		return "";
	}
	else
	{
		return std::string(buffer);
		free(buffer);
	}
}


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
	if (((angle > 45) && (angle < 135)) || ((angle > 225) && (angle < 315)))
	{
		angle = (angle + 90) % 360;
	}
	
	return sf::Vector2f(cos(angle), sin(angle)) * Config::initial_puck_velocity;
}