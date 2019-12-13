#include <iostream>

#include "Aerohockey_state.hpp"

using namespace Aerohockey;

void StateResult::render()
{
    world.mWindow.clear();

    world.mWindow.draw(world.background);
    world.board.render(world.mWindow);

    world.mWindow.display();
}

States::Type StateResult::switchTo()
{
    if (timeElapsed > Config::result_demonstration_time)
    {
        return States::Type::Exiting;
    }
    return States::Type::Result;
}
