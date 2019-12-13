#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>

#include "../../mainWindow.h"
#include "world.hpp"

using namespace std;
using namespace Aerohockey;

World::World(float width, float height, float update_time, BodyTracker & kinect, bool kinectControl)
    : width_(width)
    , height_(height)
    , score_changed(false)
    , kinectControl (kinectControl)
    , puck_velocity (get_initial_velocity())
    , update_time (update_time)
    , mWindow(MainWindow::getWindow())
    , puck (Config::puck_radius, sf::Color::White, sf::Vector2f(width / 2, height / 2), puck_velocity)
    , left (Config::paddle_radius, Config::red, update_time, kinect, true, kinectControl)
    , right (Config::paddle_radius, Config::green, update_time, kinect, false, kinectControl)
    , board (&left, &right, Config::game_length)
    , left_ready (Config::left_ready_button_position, Config::left_ready_button_size)
    , right_ready (Config::right_ready_button_position, Config::right_ready_button_size)
{
    std::string scored_path = Config::sound_scored_path;
    if (!scored.loadFromFile(scored_path))
    {
        std::cout << "Failed to load 'scored' sound: " << scored_path << "\n";
    }
    else
    {
        std::cout << "Successfully loaded 'scored' sound: " << scored_path << "\n";
        scored_sound.setBuffer(scored);
    }

    std::string hit_path = Config::sound_hit_path;
    if (!hit.loadFromFile(hit_path))
    {
        std::cout << "Failed to load 'hit' sound: " << hit_path << "\n";
    }
    else
    {
        std::cout << "Successfully loaded 'hit' sound: " << hit_path << "\n";
        hit_sound.setBuffer(hit);
    }

    std::string wall_path = Config::sound_wall_path;
    if (!wall.loadFromFile(wall_path))
    {
        std::cout << "Failed to load 'wall' sound: " << wall_path << "\n";
    }
    else
    {
        std::cout << "Successfully loaded 'wall' sound: " << wall_path << "\n";
        wall_sound.setBuffer(wall);
    }

    std::string path = Config::texture_background_path;
    if (!bg_texture.loadFromFile(path))
    {
        std::cout << "Failed to load texture: " << path << "\n";
    }
    else
    {
        std::cout << "Successfully loaded background texture: " << path << "\n";
        background.setTexture(bg_texture);
        background.setScale(width_ / background.getLocalBounds().width,
                            height_ / background.getLocalBounds().height);
    }

    left_border.setPosition(0.f, 0.f);
    left_border.setSize(sf::Vector2f(width_ / 2, height_));
    left_border.setFillColor(sf::Color::Transparent);
    left_border.setOutlineColor(sf::Color(242, 99, 80, 200));
    left_border.setOutlineThickness(-10.f);

    right_border.setPosition(width_ / 2, 0.f);
    right_border.setSize(sf::Vector2f(width_ / 2, height_));
    right_border.setOutlineColor(sf::Color(102, 214, 92, 200));
    right_border.setFillColor(sf::Color::Transparent);
    right_border.setOutlineThickness(-10.f);
}


void World::processEvents()
{
    if (!kinectControl)
    {
        left.handleInput();
        right.handleInput();
    }
}


void World::update()
{
    left.update();
    right.update();
    puck.update(update_time);

    for (int i = 0; i < left.n_limbs; i++)
    {
        collide_objects(left.paddles()[i], puck);
    }
    for (int i = 0; i < right.n_limbs; i++)
    {
        collide_objects(right.paddles()[i], puck);
    }
    puck.walls_collide(width_, height_, wall_sound);

    score_changed = goal_scored();
    board.update(update_time, score_changed);
}


void World::collide_objects(Paddle & first, Puck & second)
{
    float r1 = first.radius();
    float r2 = second.radius();
    float threshold = (r1 + r2) * (r1 + r2);
    sf::Vector2f x1 = first.position(), x2 = second.position();

    float dist = dist2(x1, x2);
    if (dist2(x1, x2) <= threshold)
    {
        sf::Vector2f v1 = sf::Vector2f(0.f, 0.f), v2 = second.velocity();
        if (Config::use_paddle_velocity)
        {
            v1 = first.velocity();
        }

        float rewind_time = 0.f;
        if (dist < threshold)
        {
            sf::Vector2f dv = v1 - v2;
            rewind_time = (r1 + r2 - sqrt(dist)) / sqrt(len2(dv));

            first.moveTo(x1 - rewind_time * v1);
            second.moveTo(x2 - rewind_time * v2);
        }

        sf::Vector2f x1 = first.position(), x2 = second.position();
        second.velocity() = v2 - 2.f * (x2 - x1) * dot(v2 - v1, x2 - x1) / len2(x2 - x1);

		if (Config::use_velocity_cap)
		{
			float velocity_module = sqrt(len2(second.velocity()));
			if (velocity_module > Config::max_puck_velocity)
			{
				float scale = Config::max_puck_velocity / velocity_module;
				second.velocity() *= scale;
			}
		}

        second.update(rewind_time);
        hit_sound.play();
    }
}

bool World::goal_scored()
{
    // Get random velocity for puck reset
    sf::Vector2f velocity = get_initial_velocity();

    if ((puck.position().x < 0) || (puck.position().x > width_))
    {
        if (puck.position().x < 0)
        {
            right.scored();

            // Right has scored -> puck goes left -> vx should be negative
            velocity.x = -1.f * abs(velocity.x);
        }
        else
        {
            left.scored();

            // Left has scored -> puck goes right -> vx should be positive
            velocity.x = abs(velocity.x);
        }
        puck.reset(sf::Vector2f(width_ / 2, height_ / 2), velocity);
        scored_sound.play();
        return true;
    }
    return false;
}

void World::render()
{
    mWindow.clear();

    mWindow.draw(background);

    mWindow.draw(left_border);
    mWindow.draw(right_border);

    left.render(mWindow);
    right.render(mWindow);
    puck.render(mWindow);

    board.render(mWindow);

    mWindow.display();
}


void World::reset()
{
    left.reset();
    right.reset();
    puck.reset(sf::Vector2f(width_ / 2, height_ / 2), get_initial_velocity());
    board.reset();
}
