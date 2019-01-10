#include <stdexcept>
#include "Node.hpp"
#include "Transition.hpp"

unsigned int Node::nodes_counter = 0;

Node::Node()
{
    id = nodes_counter++;
}

unsigned int Node::getId() const
{
    return id;
}

const Transition& Node::getInTransition(int id) const
{
    unsigned int index = findInTransition(id);
    if((unsigned)index == in_transitions.size())
        throw std::invalid_argument("Transition id not found");

    return *in_transitions[index];
}

const Transition& Node::getOutTransition(int id) const
{
    unsigned int index = findOutTransition(id);
    if((unsigned)index == out_transitions.size())
        throw std::invalid_argument("Transition id not found");

    return *out_transitions[index];
}

const std::vector<Transition*> Node::getInTransitions() const
{
    return in_transitions;
}

const std::vector<Transition*> Node::getOutTransitions() const
{
    return out_transitions;
}

std::vector<Transition*> Node::getInTransitions()
{
    return in_transitions;
}

std::vector<Transition*> Node::getOutTransitions()
{
    return out_transitions;
}

void Node::addInTransition(Transition* transition)
{
    in_transitions.push_back(transition);
}

void Node::addOutTransition(Transition* transition)
{
    out_transitions.push_back(transition);
}

void Node::removeInTransition(int id)
{
    unsigned int index = findInTransition(id);
    if((unsigned)index == in_transitions.size())
        throw std::invalid_argument("Transition id not found");
    
    //Handle transition destruction
    in_transitions.erase(in_transitions.begin() + index);
}

void Node::removeOutTransition(int id)
{
    unsigned int index = findOutTransition(id);
    if((unsigned)index == out_transitions.size())
        throw std::invalid_argument("Transition id not found");
    
    //Handle transition destruction
    out_transitions.erase(out_transitions.begin() + index);
}

const std::string& Node::getName() const
{
    return name;
}

void Node::setName(const char* name)
{
    this->name = name;
}

void Node::setName(std::string name)
{
    this->name = name;
}

bool Node::isInInTransitions(int id)
{
    return findInTransition(id) != in_transitions.size();
}

bool Node::isInOutTransitions(int id)
{
    return findOutTransition(id) != out_transitions.size();
}

unsigned int Node::findInTransition(int id) const
{
    if(id < 0)
        throw std::invalid_argument("Id must be positive");
    unsigned int index = 0;
    while(index < in_transitions.size() && in_transitions[index]->getId() != (unsigned)id)
    {
        index++;
    }

    return index;
}

unsigned int Node::findOutTransition(int id) const
{
    if(id < 0)
        throw std::invalid_argument("Id must be positive");
    unsigned int index = 0;
    while(index < out_transitions.size() && out_transitions[index]->getId() != (unsigned)id)
    {
        index++;
    }

    return index;
}
