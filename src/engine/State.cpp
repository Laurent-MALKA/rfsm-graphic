#include "State.hpp"
#include "Transition.hpp"

#include <stdexcept>

unsigned int State::states_counter = 0;

State::State(const std::string& name, int id)
    : id(id == -1 ? states_counter : id), name(name)
{
    states_counter++;
}

unsigned int State::getId() const
{
    return id;
}

unsigned int State::getStatesCounter()
{
    return states_counter;
}

const Transition& State::getInTransition(int id) const
{
    unsigned int index = findInTransition(id);
    if((unsigned)index == in_transitions.size())
        throw std::invalid_argument(
            std::string("No transition found with id : ") + std::to_string(id));

    return *in_transitions[index];
}

const Transition& State::getOutTransition(int id) const
{
    unsigned int index = findOutTransition(id);
    if((unsigned)index == out_transitions.size())
        throw std::invalid_argument(
            std::string("No transition found with id : ") + std::to_string(id));

    return *out_transitions[index];
}

const std::vector<Transition*> State::getInTransitions() const
{
    return in_transitions;
}

const std::vector<Transition*> State::getOutTransitions() const
{
    return out_transitions;
}

std::vector<Transition*> State::getInTransitions()
{
    return in_transitions;
}

std::vector<Transition*> State::getOutTransitions()
{
    return out_transitions;
}

void State::addInTransition(Transition* transition)
{
    in_transitions.push_back(transition);
}

void State::addOutTransition(Transition* transition)
{
    out_transitions.push_back(transition);
}

void State::removeInTransition(int id)
{
    unsigned int index = findInTransition(id);
    if((unsigned)index == in_transitions.size())
        throw std::invalid_argument(
            std::string("No transition found with id : ") + std::to_string(id));

    // Handle transition destruction
    in_transitions.erase(in_transitions.begin() + index);
}

void State::removeOutTransition(int id)
{
    unsigned int index = findOutTransition(id);
    if((unsigned)index == out_transitions.size())
        throw std::invalid_argument(
            std::string("No transition found with id : ") + std::to_string(id));

    // Handle transition destruction
    out_transitions.erase(out_transitions.begin() + index);
}

const std::string& State::getName() const
{
    return name;
}

void State::setName(const std::string& name)
{
    this->name = name;
}

bool State::isInInTransitions(int id)
{
    return findInTransition(id) != in_transitions.size();
}

bool State::isInOutTransitions(int id)
{
    return findOutTransition(id) != out_transitions.size();
}

unsigned int State::findInTransition(int id) const
{
    if(id < 0)
        throw std::invalid_argument("Id must be positive");
    unsigned int index = 0;
    while(index < in_transitions.size()
          && in_transitions[index]->getId() != (unsigned)id)
    {
        index++;
    }

    return index;
}

unsigned int State::findOutTransition(int id) const
{
    if(id < 0)
        throw std::invalid_argument("Id must be positive");
    unsigned int index = 0;
    while(index < out_transitions.size()
          && out_transitions[index]->getId() != (unsigned)id)
    {
        index++;
    }

    return index;
}
