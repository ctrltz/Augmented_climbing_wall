#include <iostream>

#include "state.hpp"

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
