#include <SFML/Graphics.hpp>
#include <iostream>

#include "Territory_state.hpp"

using namespace Territory;

void StatePreparation::processEvents()
{
    world.processEvents();
}

void StatePreparation::update(const float delta)
{
    State::update(delta);

    world.left.update(world.map);
    world.right.update(world.map);
    world.left_ready.update(world.left.paddles());
    world.right_ready.update(world.right.paddles());
}

void StatePreparation::render()
{
    world.mWindow.clear();

    for (int i = 0; i < world.left.n_limbs; i++)
    {
        world.mWindow.draw(world.left.paddles()[i].shape());
    }
    for (int i = 0; i < world.right.n_limbs; i++)
    {
        world.mWindow.draw(world.right.paddles()[i].shape());
    }
    world.mWindow.draw(world.left_ready.sprite());
    world.mWindow.draw(world.right_ready.sprite());

    world.mWindow.display();
}

States::Type StatePreparation::switchTo()
{
    if (world.left_ready.isActivated() && world.right_ready.isActivated())
    {
        return States::Type::Game;
    }
    return States::Type::Preparation;
}
