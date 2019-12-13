#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

struct Puck
{
public:
    Puck(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity);
    void moveTo(sf::Vector2f position);
    void update(float delta);
    void render(sf::RenderWindow& window);
    void walls_collide(float width, float height, sf::Sound & sound);
    void reset(sf::Vector2f position, sf::Vector2f velocity);
    sf::Sprite & shape();
    float radius();
    sf::Vector2f & position();
    sf::Vector2f & velocity(); 

private:
    sf::Sprite sprite_;
    sf::Texture texture_;
    float radius_;
    sf::Color color_;
    sf::Vector2f position_;
    size_t current, capacity;
    std::vector<sf::Vector2f> trace_;
    sf::Vector2f velocity_;
};
