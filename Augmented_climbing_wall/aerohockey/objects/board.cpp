#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "board.hpp"

using namespace std;
using namespace Aerohockey;

Scoreboard::Scoreboard(Player * left, Player * right, float gameDuration)
    : left_ (left), right_ (right), gameDuration_ (gameDuration)
{
    remainingTime_ = gameDuration_;
    std::string path = Config::font_scoreboard_path;
    if (!font_.loadFromFile(path))
    {
        std::cout << "Failed to load font for scoreboard: " << path << "\n";
    }
    else
    {
        std::cout << "Successfully loaded font for scoreboard: " << path << "\n";
        left_score.setFont(font_);
        timer_.setFont(font_);
        right_score.setFont(font_);
    }

    left_score_border.setPosition(Config::screen_width / 2 - Config::timer_width / 2 - Config::score_width, 
        Config::screen_height - Config::board_height);
    left_score_border.setSize(sf::Vector2f(Config::score_width, Config::board_height));
    left_score_border.setFillColor(Config::red);
    left_score_border.setOutlineColor(sf::Color::White);
    left_score_border.setOutlineThickness(-2.f);

    right_score_border.setPosition(Config::screen_width / 2 + Config::timer_width / 2, 
        Config::screen_height - Config::board_height);
    right_score_border.setSize(sf::Vector2f(Config::score_width, Config::board_height));
    right_score_border.setFillColor(Config::green);
    right_score_border.setOutlineColor(sf::Color::White);
    right_score_border.setOutlineThickness(-2.f);

    time_border.setPosition(Config::screen_width / 2 - Config::timer_width / 2, 
        Config::screen_height - Config::board_height);
    time_border.setSize(sf::Vector2f(Config::timer_width, Config::board_height));
    time_border.setFillColor(sf::Color::Transparent);
    time_border.setOutlineColor(sf::Color::White);
    time_border.setOutlineThickness(-2.f);
    
    left_score.setCharacterSize(Config::font_size);
    left_score.setFillColor(sf::Color::White);
    left_score.setString(to_string(left_->score()));

    timer_.setCharacterSize(Config::font_size);
    timer_.setFillColor(sf::Color::White);
    timer_.setString(time_line(remainingTime_));

    right_score.setCharacterSize(Config::font_size);
    right_score.setFillColor(sf::Color::White);
    right_score.setString(to_string(right_->score()));
}

string Scoreboard::time_line(float seconds)
{
    int mins = (int) seconds / 60;
    int secs = (int) seconds % 60;
    sprintf(t_, "%02d:%02d", mins, secs);

    return t_;
}

void Scoreboard::align_center(sf::Text& text, sf::RectangleShape& border)
{
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(border.getPosition().x + border.getSize().x / 2, 
        border.getPosition().y + border.getSize().y / 2);
}

void Scoreboard::update(float delta, bool& score_changed)
{
    if (score_changed)
    {
        left_score.setString(to_string(left_->score()));
        right_score.setString(to_string(right_->score()));
        score_changed = false;
    }

    remainingTime_ -= delta;
    timer_.setString(time_line(remainingTime_));

    // Align text to be in the center of the corresponding cells
    align_center(left_score, left_score_border);
    align_center(timer_, time_border);
    align_center(right_score, right_score_border);
}

void Scoreboard::render(sf::RenderWindow & window)
{
    window.draw(left_score_border);
    window.draw(right_score_border);
    window.draw(time_border);

    window.draw(left_score);
    window.draw(timer_);
    window.draw(right_score);
}

void Scoreboard::reset()
{
    remainingTime_ = gameDuration_;
    left_score.setString(to_string(0));
    right_score.setString(to_string(0));
}
