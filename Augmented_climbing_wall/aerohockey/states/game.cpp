#include <iostream>

#include "state.hpp"

void StateGame::processEvents()
{
    world.processEvents();
}

void StateGame::update(const float delta)
{
    State::update(delta);
    world.update();
}

void StateGame::render()
{
    world.render();
}

void StateGame::reset()
{
    State::reset();
    world.reset();
}

States::Type StateGame::switchTo()
{
    if ((timeElapsed > Config::game_length) || (world.left.score() == Config::max_score)
            || (world.right.score() == Config::max_score))
    {
        return States::Type::Result;
    }
    return States::Type::Game;
}
