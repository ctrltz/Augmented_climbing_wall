#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "Territory_board.hpp"

using namespace std;
using namespace Territory;

Scoreboard::Scoreboard(Player & left, Player & right)
    : left_ (left), right_ (right)
{
    font_.loadFromFile("territory/media/fonts/DIN.ttf");

    float x = 120.f;
    sf::Color red = sf::Color(204, 0, 0);
    sf::Color green = sf::Color(0, 102, 0);

    left_score_border.setPosition(400.f - x, 540.f);
    left_score_border.setSize(sf::Vector2f(x, 80.f));
    left_score_border.setFillColor(red);
    left_score_border.setOutlineColor(sf::Color::White);
    left_score_border.setOutlineThickness(-2.f);

    right_score_border.setPosition(400.f, 540.f);
    right_score_border.setSize(sf::Vector2f(x, 80.f));
    right_score_border.setFillColor(green);
    right_score_border.setOutlineColor(sf::Color::White);
    right_score_border.setOutlineThickness(-2.f);

    left_score.setFont(font_);
    left_score.setCharacterSize(40);
    left_score.setPosition(300.f, 545.f);
    left_score.setFillColor(sf::Color::White);
    left_score.setString(to_string(left_.score()));

    right_score.setFont(font_);
    right_score.setCharacterSize(40);
    right_score.setPosition(420.f, 545.f);
    right_score.setFillColor(sf::Color::White);
    right_score.setString(to_string(right_.score()));
}

string Scoreboard::time_line(float seconds)
{
    int mins = (int) seconds / 60;
    int secs = (int) seconds % 60;
    sprintf(t_, "%02d:%02d", mins, secs);

    return t_;
}

void Scoreboard::update()
{
    left_score.setString(to_string(left_.score()));
    right_score.setString(to_string(right_.score()));
}

void Scoreboard::render(sf::RenderWindow & window)
{
    window.draw(left_score_border);
    window.draw(right_score_border);

    window.draw(left_score);
    window.draw(right_score);
}

void Scoreboard::reset()
{
    left_score.setString(to_string(0));
    right_score.setString(to_string(0));
}
