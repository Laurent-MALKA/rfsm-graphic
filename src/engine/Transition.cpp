#include <stdexcept>
#include "Transition.hpp"
#include "Node.hpp"

unsigned int Transition::transitions_counter = 0;

Transition::Transition(Node& starting_node, Node& end_node) : starting_node(starting_node), end_node(end_node)
{
    id = transitions_counter++;

    starting_node.addOutTransition(this);
    end_node.addInTransition(this);
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

void Transition::setAction(std::string action)
{
    this->action = action;
}

bool Transition::hasAction()
{
    return !action.empty();
}

const Node& Transition::getStartingNode() const
{
    return starting_node;
}

const Node& Transition::getEndNode() const
{
    return end_node;
}

unsigned int Transition::getStartingNodeId() const
{
    return starting_node.getId();
}

unsigned int Transition::getEndNodeId() const
{
    return end_node.getId();
}