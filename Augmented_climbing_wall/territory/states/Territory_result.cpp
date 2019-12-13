#include <iostream>

#include "Territory_state.hpp"

using namespace Territory;

void StateResult::update(const float delta)
{
    State::update(delta);
    world.board.update();
}

void StateResult::render()
{
    world.mWindow.clear();

    world.board.render(world.mWindow);

    world.mWindow.display();
}

States::Type StateResult::switchTo()
{
    if (timeElapsed > 5.f)
    {
        return States::Type::Exiting;
    }
    return States::Type::Result;
}
