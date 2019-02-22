#include "Transition.hpp"
#include "State.hpp"

#include <stdexcept>

unsigned int Transition::transitions_counter = 0;

Transition::Transition(State* starting_state, State* end_state)
    : starting_state(starting_state), end_state(end_state)
{
    id = transitions_counter++;

    starting_state->addOutTransition(this);
    end_state->addInTransition(this);
}

unsigned int Transition::getId() const
{
    return id;
}

const std::string& Transition::getCondition() const
{
    return condition;
}

void Transition::setCondition(const char* condition)
{
    this->condition = condition;
}

void Transition::setCondition(const std::string& condition)
{
    this->condition = condition;
}

const std::string& Transition::getAction() const
{
    return action;
}

void Transition::setAction(const char* action)
{
    this->action = action;
}

void Transition::setAction(const std::string& action)
{
    this->action = action;
}

bool Transition::hasAction()
{
    return !action.empty();
}

const State& Transition::getStartingState() const
{
    return *starting_state;
}

const State& Transition::getEndState() const
{
    return *end_state;
}

void Transition::setStartState(State* start_state)
{
    this->starting_state->removeOutTransition(id);
    this->starting_state = start_state;
    this->starting_state->addOutTransition(this);
}
void Transition::setEndState(State* end_state)
{
    this->end_state->removeInTransition(id);
    this->end_state = end_state;
    this->end_state->addInTransition(this);
}

unsigned int Transition::getStartingStateId() const
{
    return starting_state->getId();
}

unsigned int Transition::getEndStateId() const
{
    return end_state->getId();
}