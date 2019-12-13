#include <iostream>
#include "manager.hpp"

StateManager::StateManager(const States::Type& initial, World & world, BodyTracker & kinect, bool kinectControl)
    : current_state (initial), world (world), kinect (kinect), kinectControl (kinectControl)
{
    registerState<StatePreparation>(States::Type::Preparation, world);
    registerState<StateGame>(States::Type::Game, world);
    registerState<StateResult>(States::Type::Result, world);
    registerState<StateExiting>(States::Type::Exiting, world);
}

StateManager::~StateManager()
{
    for (const auto entry : container)
    {
        delete entry.second;
    }
}

template <typename T>
void StateManager::registerState(const States::Type state, World & world)
{
    container[state] = new T(state, world);
}

void StateManager::activateState(const States::Type state)
{
    current_state = state;
    container[current_state]->reset();
}

States::Type StateManager::getCurrentState() const
{
    return current_state;
}

void StateManager::processEvents()
{
    container[current_state]->processEvents();
}

void StateManager::update(const float delta)
{
    State * current = container[current_state];
    if (kinectControl)
    {
        kinect.Update(false);
    }
    current->update(delta);

    States::Type next_state = current->switchTo();
    if (next_state != current_state)
    {
        activateState(next_state);
    }
}

void StateManager::render()
{
    container[current_state]->render();
}
