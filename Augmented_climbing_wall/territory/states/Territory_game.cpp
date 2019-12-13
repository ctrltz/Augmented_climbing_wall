#include <iostream>

#include "Territory_state.hpp"

using namespace Territory;

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
    if (timeElapsed > 30.f)
    {
        return States::Type::Result;
    }
    return States::Type::Game;
}
