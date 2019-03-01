#include "Transition.hpp"
#include "State.hpp"

#include <stdexcept>

unsigned int Transition::transitions_counter = 0;

Transition::Transition(State* start_state, State* end_state)
    : start_state(start_state), end_state(end_state)
{
    id = transitions_counter++;

    start_state->addOutTransition(this);
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

void Transition::setCondition(const std::string& condition)
{
    this->condition = condition;
    for(auto& character : this->condition)
        character = std::tolower(character);
}

const std::string& Transition::getAction() const
{
    return action;
}

void Transition::setAction(const std::string& action)
{
    this->action = action;
    for(auto& character : this->action)
        character = std::tolower(character);
}

bool Transition::hasAction()
{
    return !action.empty();
}

const State& Transition::getStartState() const
{
    return *start_state;
}

const State& Transition::getEndState() const
{
    return *end_state;
}

void Transition::setStartState(State* start_state)
{
    this->start_state->removeOutTransition(id);
    this->start_state = start_state;
    this->start_state->addOutTransition(this);
}
void Transition::setEndState(State* end_state)
{
    this->end_state->removeInTransition(id);
    this->end_state = end_state;
    this->end_state->addInTransition(this);
}

unsigned int Transition::getStartStateId() const
{
    return start_state->getId();
}

unsigned int Transition::getEndStateId() const
{
    return end_state->getId();
}