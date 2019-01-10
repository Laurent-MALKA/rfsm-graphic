#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "Transition.hpp"
#include "StateChart.hpp"

StateChart::StateChart(): initial_node_id(-1)
{
}

StateChart::~StateChart()
{
    for(auto &node: nodes)
    {
        for(auto& out_transition: node->getOutTransitions())
            delete out_transition;
        delete node;
    }
}

std::vector<Variable*> StateChart::getInVariables()
{
    return in_variables;
}

std::vector<Variable*> StateChart::getOutVariables()
{
    return out_variables;
}

std::vector<Variable*> StateChart::getInoutVariables()
{
    return inout_variables;
}

std::vector<Variable*> StateChart::getInternVariables()
{
    return intern_variables;
}

void StateChart::addInVariable()
{
    in_variables.push_back(new Variable());
}

void StateChart::addOutVariable()
{
    out_variables.push_back(new Variable());
}

void StateChart::addInoutVariable()
{
    inout_variables.push_back(new Variable());
}

void StateChart::addInternVariable()
{
    intern_variables.push_back(new Variable());
}

const Node& StateChart::getNode(int node_id) const
{
    unsigned int index = findNodeIndex(node_id);
    if(index == nodes.size())
        throw std::invalid_argument("Invalid node id");
    
    return *nodes[index];
}

bool StateChart::nodeExists(int node_id)
{
    return findNodeIndex(node_id) != nodes.size();
}

unsigned int StateChart::addNode(const char* name)
{
    Node* new_node = new Node();
    new_node->setName(name);
    nodes.push_back(new_node);

    return new_node->getId();
}

unsigned int StateChart::addNode(std::string name)
{
    Node* new_node = new Node();
    new_node->setName(name);
    nodes.push_back(new_node);

    return new_node->getId();
}

unsigned int StateChart::addTransition(int starting_node_id, int end_node_id, std::string condition, std::string action)
{
    unsigned int starting_node_index = findNodeIndex(starting_node_id);
    unsigned int end_node_index = findNodeIndex(end_node_id);
    
    if(starting_node_index == nodes.size())
        throw std::invalid_argument("Invalid starting node id");
    
    if(end_node_index == nodes.size())
        throw std::invalid_argument("Invalid end node id");

    Node* starting_node = nodes[starting_node_index];
    Node* end_node = nodes[end_node_index];

    Transition *new_transition = new Transition(*starting_node,
                                                *end_node);

    new_transition->setCondition(condition);
    new_transition->setAction(action);

    return new_transition->getId();
}

void StateChart::setInitialNode(int node_id)
{
    if(nodeExists(node_id))
        initial_node_id = node_id;
}

void StateChart::setInitialAction(std::string action)
{
    initial_action = action;
}

void StateChart::deleteNode(int node_id)
{
    unsigned int node_index = findNodeIndex(node_id);
    if(node_index == nodes.size())
        throw std::invalid_argument("Invalid node id");

    Node* node = nodes[node_index];
    
    for(auto& out_transition: node->getOutTransitions())
    {
        unsigned int end_node_index = findNodeIndex(out_transition->getEndNode().getId());
        nodes[end_node_index]->removeInTransition(out_transition->getId());
    }

    for(auto& in_transition: node->getInTransitions())
    {
        unsigned int starting_node_index = findNodeIndex(in_transition->getEndNode().getId());
        nodes[starting_node_index]->removeOutTransition(in_transition->getId());
    }

    delete nodes[node_index];
    nodes.erase(nodes.begin() + node_index);
}

void StateChart::deleteTransition(int transition_id)
{
    //Can be greatly improved
    bool transition_found = false;
    for(auto& node: nodes)
    {
        if(node->isInInTransitions(transition_id))
        {
            node->removeInTransition(transition_id);
            transition_found = true;
        }
        if(node->isInOutTransitions(transition_id))
        {
            node->removeOutTransition(transition_id);
            transition_found = true;
        }
    }
    if(!transition_found)
        throw std::invalid_argument("Invalid transition id");
}

std::string StateChart::toFSMCode()
{
    std::stringstream code;
    std::string indent = std::string(4,' ');
    bool first = true;

    code << "fsm model " << name << "(";
    if(in_variables.size() + out_variables.size() + inout_variables.size() != 0)
    {
        code << std::endl;
        for(auto& var: in_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << "in " << var->getName() << ": " << var->getType();
            first = false;
        }
        for(auto& var: out_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << "out " << var->getName() << ": " << var->getType();
            first = false;
        }
        for(auto& var: inout_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << "inout " << var->getName() << ": " << var->getType();
            first = false;
        }
    }
    code << ")" << std::endl;
    code << "{" << std::endl;

    code << indent;

    code << "states: " << std::endl;
    first = true;
    for(auto& node: nodes)
    {
        if(!first)
            code << "," << std::endl;
        code << indent << indent;
        code << node->getName();
        first = false;
    }
    code << ";" << std::endl;
    
    if(intern_variables.size() != 0)
    {
        code << indent;
        code << "vars: " << std::endl;
        first = true;
        for(auto& var: intern_variables)
        {
            if(!first)
                code << "," << std::endl;
            code << indent << indent;
            code << var->getName() << ": " << var->getType();
            first = false;
        }
        code << ";" << std::endl;
    }

    code << indent;
    code << "trans: " << std::endl;
    first = true;
    for(auto& node: nodes)
    {
        for(auto& transition: node->getOutTransitions())
        {
            if(!first)
                code << "," << std::endl;
            code << indent << indent;
            code << transition->getStartingNode().getName() << " -- ";
            code << transition->getCondition() << " | ";
            if(transition->hasAction())
                code << transition->getAction() << " ";
            code << "-> " << transition->getEndNode().getName();
        }
    }
    code << ";" << std::endl;

    code << indent;
    code << "itrans: " << std::endl;
    code << indent << indent;
    if(initial_action != "")
        code << "| " << initial_action << " ";
    code << "-> " << nodes[initial_node_id]->getName() << ";" << std::endl;
    
    code << "}";

    return code.str();
}

unsigned int StateChart::findNodeIndex(int node_id) const
{
    if (node_id < 0)
        throw std::invalid_argument("Id must be positive");

    unsigned int index = 0;
    while (index < nodes.size() && nodes[index]->getId() != (unsigned)node_id)
    {
        index++;
    }

    return index;
}