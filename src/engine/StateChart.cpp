#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "Transition.hpp"
#include "StateChart.hpp"

StateChart::StateChart(): initial_state_id(-1)
{
}

StateChart::~StateChart()
{
    for(auto &state: states)
    {
        for(auto& out_transition: state->getOutTransitions())
            delete out_transition;
        delete state;
    }
}

std::string StateChart::getName() const
{
    return name;
}

void StateChart::setName(std::string name)
{
    this->name = name;
}

std::vector<InputVariable*> StateChart::getInVariables()
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
    in_variables.push_back(new InputVariable());
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

const State& StateChart::getState(int state_id) const
{
    unsigned int index = findStateIndex(state_id);
    if(index == states.size())
        throw std::invalid_argument("Invalid state id");

    return *states[index];
}

State& StateChart::getState(int state_id)
{
    unsigned int index = findStateIndex(state_id);
    if(index == states.size())
        throw std::invalid_argument("Invalid state id");

    return *states[index];
}

bool StateChart::stateExists(int state_id)
{
    return findStateIndex(state_id) != states.size();
}

unsigned int StateChart::addState(const char* name)
{
    State* new_state = new State();
    new_state->setName(name);
    states.push_back(new_state);

    return new_state->getId();
}

unsigned int StateChart::addState(std::string name)
{
    State* new_state = new State();
    new_state->setName(name);
    states.push_back(new_state);

    return new_state->getId();
}

unsigned int StateChart::addTransition(int starting_state_id, int end_state_id, std::string condition, std::string action)
{
    unsigned int starting_state_index = findStateIndex(starting_state_id);
    unsigned int end_state_index = findStateIndex(end_state_id);

    if(starting_state_index == states.size())
        throw std::invalid_argument("Invalid starting state id");

    if(end_state_index == states.size())
        throw std::invalid_argument("Invalid end state id");

    State* starting_state = states[starting_state_index];
    State* end_state = states[end_state_index];

    Transition *new_transition = new Transition(*starting_state,
                                                *end_state);

    new_transition->setCondition(condition);
    new_transition->setAction(action);

    return new_transition->getId();
}

void StateChart::setInitialState(int state_id)
{
    if(stateExists(state_id))
        initial_state_id = state_id;
}

void StateChart::setInitialAction(std::string action)
{
    initial_action = action;
}

void StateChart::deleteState(int state_id)
{
    unsigned int state_index = findStateIndex(state_id);
    if(state_index == states.size())
        throw std::invalid_argument("Invalid state id");

    State* state = states[state_index];

    for(auto& out_transition: state->getOutTransitions())
    {
        unsigned int end_state_index = findStateIndex(out_transition->getEndState().getId());
        states[end_state_index]->removeInTransition(out_transition->getId());
    }

    for(auto& in_transition: state->getInTransitions())
    {
        unsigned int starting_state_index = findStateIndex(in_transition->getEndState().getId());
        states[starting_state_index]->removeOutTransition(in_transition->getId());
    }

    delete states[state_index];
    states.erase(states.begin() + state_index);
}

void StateChart::deleteTransition(int transition_id)
{
    //Can be greatly improved
    bool transition_found = false;
    for(auto& state: states)
    {
        if(state->isInInTransitions(transition_id))
        {
            state->removeInTransition(transition_id);
            transition_found = true;
        }
        if(state->isInOutTransitions(transition_id))
        {
            state->removeOutTransition(transition_id);
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
    for(auto& state: states)
    {
        if(!first)
            code << "," << std::endl;
        code << indent << indent;
        code << state->getName();
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
    for(auto& state: states)
    {
        for(auto& transition: state->getOutTransitions())
        {
            if(!first)
                code << "," << std::endl;
            code << indent << indent;
            code << transition->getStartingState().getName() << " -- ";
            code << transition->getCondition() << " | ";
            if(transition->hasAction())
                code << transition->getAction() << " ";
            code << "-> " << transition->getEndState().getName();
        }
    }
    code << ";" << std::endl;

    code << indent;
    code << "itrans: " << std::endl;
    code << indent << indent;
    if(initial_action != "")
        code << "| " << initial_action << " ";
    code << "-> " << getState(initial_state_id).getName() << ";" << std::endl;

    code << "}" << std::endl << std::endl;

    for(auto& var: in_variables)
    {
        code << "input " << var->getName() << " : " << var->getType() << " = " << var->getStimuli() << std::endl;
    }

    for(auto& var: out_variables)
    {
        code << "output " << var->getName() << " : " << var->getType() << std::endl;        
    }

    code << std::endl;

    code << "fsm instance = " << name << "(";
    if(in_variables.size() + out_variables.size() + inout_variables.size() != 0)
    {
        first = true;
        code << std::endl;
        for(auto& var: in_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << var->getName();
            first = false;
        }
        for(auto& var: out_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << var->getName();
            first = false;
        }
        for(auto& var: inout_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << var->getName();
            first = false;
        }
    }
    
    code << ")";

    return code.str();
}

unsigned int StateChart::findStateIndex(int state_id) const
{
    if (state_id < 0)
        throw std::invalid_argument("Id must be positive");

    unsigned int index = 0;
    while (index < states.size() && states[index]->getId() != (unsigned)state_id)
    {
        index++;
    }

    return index;
}
