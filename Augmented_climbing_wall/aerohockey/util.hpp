#pragma once

#include <SFML/Graphics.hpp>

std::string getcwd_string();
float len2 (sf::Vector2f const v);
float dot (sf::Vector2f const v1, sf::Vector2f const v2);
float dist2 (sf::Vector2f const & p1, sf::Vector2f const & p2);

sf::Vector2f get_initial_velocity();
