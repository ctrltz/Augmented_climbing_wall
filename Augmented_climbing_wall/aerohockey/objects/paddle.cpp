#include "paddle.hpp"

#define SCALE_FACTOR 0.70711f

Paddle::Paddle()
    : radius_(0), color_(sf::Color::Black), position_(sf::Vector2f(0.f, 0.f))
    , velocity_(0.f), vx_(0), vy_(0)
    , update_time (0.f), valid_ (true)
    , up_(sf::Keyboard::W), down_(sf::Keyboard::S), left_ (sf::Keyboard::A), right_ (sf::Keyboard::D)
{

}

Paddle::Paddle (float radius, sf::Color color, sf::Vector2f position, float velocity, float update_time, 
                sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right)
    : radius_ (radius), color_ (color), position_ (position)
    , update_time (update_time)
    , velocity_ (velocity), vx_ (0), vy_ (0)
    , up_ (up), down_ (down), left_ (left), right_ (right)
{
    current_velocity_ = sf::Vector2f(0.f, 0.f);
    shape_.setRadius(radius_);
    shape_.setFillColor(color_);
    shape_.setOutlineColor(color_);
    shape_.setOutlineThickness(-5.f);
    shape_.setOrigin(radius_, radius_);
    shape_.setPosition(position_);
}

void Paddle::handleInput()
{
    vx_ = 0;
    vy_ = 0;
    if (sf::Keyboard::isKeyPressed(up_))
    {
        vy_ -= velocity_;
    }
    if (sf::Keyboard::isKeyPressed(down_))
    {
        vy_ += velocity_;
    }
    if (sf::Keyboard::isKeyPressed(left_))
    {
        vx_ -= velocity_;
    }
    if (sf::Keyboard::isKeyPressed(right_))
    {
        vx_ += velocity_;
    }
    if ((vx_ != 0) && (vy_ != 0))
    {
        vx_ *= SCALE_FACTOR;
        vy_ *= SCALE_FACTOR;
    }
}


void Paddle::update (BodyTracker & kinect, const Limbs::Type type, bool left, bool kinectControl)
{
    if (kinectControl)
    {
        float z = kinect.getLimbDepthPoints(type, left);

        sf::Vector2f position(0.f, 0.f), velocity(0.f, 0.f);
        if (z > 1)
        {
            position = kinect.getLimbPointsXY(type, left);
            velocity = kinect.getLimbVelocitiesXY(type, left);
        }
        position_ = position;
        current_velocity_ = velocity;
        shape_.setPosition(position);
    }
    else
    {
        current_velocity_.x = vx_;
        current_velocity_.y = vy_;
        shape_.move(current_velocity_ * update_time);
        position_ = shape_.getPosition();
    }
}

void Paddle::render(sf::RenderWindow& window, bool left)
{
    sf::Vector2u window_size = window.getSize();
    valid_ = true;

    if ((position_.y < 0) || (position_.y > window_size.y))
    {
        valid_ = false;
    }

    if ((left) && ((position_.x < 0) || (position_.x > window_size.x / 2)))
    {
        valid_ = false;
    }

    if ((!left) && ((position_.x < window_size.x / 2) || (position_.x > window_size.x)))
    {
        valid_ = false;
    }

    if (valid_)
    {
        shape_.setFillColor(color_);
    }
    else
    {
        shape_.setFillColor(sf::Color::Transparent);
    }

    window.draw(shape_);
}

void Paddle::moveTo(sf::Vector2f position)
{
    position_ = position;
    shape_.setPosition(position_);
}

sf::CircleShape Paddle::shape()
{
    return shape_;
}


float Paddle::radius()
{
    return radius_;
}


sf::Vector2f & Paddle::position()
{
    return position_;
}


sf::Vector2f & Paddle::velocity()
{
    return current_velocity_;
}
