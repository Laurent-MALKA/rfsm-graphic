#include "StateChart.hpp"
#include "Transition.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>

StateChart::StateChart() : initial_state_id(-1) {}

StateChart::~StateChart()
{
    for(auto& state : states)
    {
        for(auto& out_transition : state->getOutTransitions())
            delete out_transition;
        delete state;
    }
}

std::string StateChart::getName() const
{
    return name;
}

void StateChart::setName(const std::string& name)
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

int StateChart::addInVariable()
{
    std::string name = "in_var_" + std::to_string(in_variables.size());
    in_variables.push_back(new InputVariable(name));
    return in_variables.size() - 1;
}

int StateChart::addOutVariable()
{
    std::string name = "out_var_" + std::to_string(out_variables.size());
    out_variables.push_back(new Variable(name));
    return out_variables.size() - 1;
}

int StateChart::addInoutVariable()
{
    std::string name = "inout_var_" + std::to_string(inout_variables.size());
    inout_variables.push_back(new Variable(name));
    return inout_variables.size() - 1;
}

int StateChart::addInternVariable()
{
    std::string name = "intern_var_" + std::to_string(in_variables.size());
    intern_variables.push_back(new Variable(name));
    return intern_variables.size() - 1;
}

const InputVariable* StateChart::getInVariable(int index) const
{
    if(0 <= index && index < in_variables.size())
    {
        return in_variables[index];
    }
    else
        throw std::out_of_range("invalid index");
}

const Variable* StateChart::getOutVariable(int index) const
{
    if(0 <= index && index < out_variables.size())
    {
        return out_variables[index];
    }
    else
        throw std::out_of_range("invalid index");
}

const Variable* StateChart::getInoutVariable(int index) const
{
    if(0 <= index && index < inout_variables.size())
    {
        return inout_variables[index];
    }
    else
        throw std::out_of_range("invalid index");
}

const Variable* StateChart::getInternVariable(int index) const
{
    if(0 <= index && index < intern_variables.size())
    {
        return intern_variables[index];
    }
    else
        throw std::out_of_range("invalid index");
}

void StateChart::setInVariableName(int index, const std::string& name)
{
    if(0 <= index && index < in_variables.size())
    {
        in_variables[index]->setName(name);
    }
    else
        throw std::out_of_range("invalid index");
}

void StateChart::setOutVariableName(int index, const std::string& name)
{
    if(0 <= index && index < out_variables.size())
    {
        out_variables[index]->setName(name);
    }
    else
        throw std::out_of_range("invalid index");
}

void StateChart::setInoutVariableName(int index, const std::string& name)
{
    if(0 <= index && index < inout_variables.size())
    {
        inout_variables[index]->setName(name);
    }
    else
        throw std::out_of_range("invalid index");
}

void StateChart::setInternVariableName(int index, const std::string& name)
{
    if(0 <= index && index < intern_variables.size())
    {
        intern_variables[index]->setName(name);
    }
    else
        throw std::out_of_range("invalid index");
}

void StateChart::setInVariableType(int index, const std::string& type)
{
    if(0 <= index && index < in_variables.size())
    {
        in_variables[index]->setType(type);
    }
    else
        throw std::out_of_range("invalid index");
}

void StateChart::setOutVariableType(int index, const std::string& type)
{
    if(0 <= index && index < out_variables.size())
    {
        out_variables[index]->setType(type);
    }
    else
        throw std::out_of_range("invalid index");
}

void StateChart::setInoutVariableType(int index, const std::string& type)
{
    if(0 <= index && index < inout_variables.size())
    {
        inout_variables[index]->setType(type);
    }
    else
        throw std::out_of_range("invalid index");
}

void StateChart::setInternVariableType(int index, const std::string& type)
{
    if(0 <= index && index < intern_variables.size())
    {
        intern_variables[index]->setType(type);
    }
    else
        throw std::out_of_range("invalid index");
}

void StateChart::setInVariableStimuli(int index, const std::string& stimuli)
{
    if(0 <= index && index < in_variables.size())
    {
        in_variables[index]->setStimuli(stimuli);
    }
    else
        throw std::out_of_range("invalid index");
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

Transition& StateChart::getTransition(int transition_id)
{
    for(auto& state : states)
    {
        for(auto& transition : state->getOutTransitions())
        {
            if(transition->getId() == transition_id)
                return *transition;
        }
    }

    throw std::invalid_argument("Wrong transition id");
}

unsigned int StateChart::addState(const char* name)
{
    State* new_state = new State();
    new_state->setName(name);
    states.push_back(new_state);

    return new_state->getId();
}

unsigned int StateChart::addState(const std::string& name)
{
    State* new_state = new State();
    new_state->setName(name);
    states.push_back(new_state);

    return new_state->getId();
}

unsigned int StateChart::addTransition(int starting_state_id,
                                       int end_state_id,
                                       const std::string& condition,
                                       const std::string& action)
{
    unsigned int starting_state_index = findStateIndex(starting_state_id);
    unsigned int end_state_index = findStateIndex(end_state_id);

    if(starting_state_index == states.size())
        throw std::invalid_argument("Invalid starting state id");

    if(end_state_index == states.size())
        throw std::invalid_argument("Invalid end state id");

    State* starting_state = states[starting_state_index];
    State* end_state = states[end_state_index];

    Transition* new_transition = new Transition(*starting_state, *end_state);

    new_transition->setCondition(condition);
    new_transition->setAction(action);

    return new_transition->getId();
}

void StateChart::setInitialState(int state_id)
{
    if(stateExists(state_id))
        initial_state_id = state_id;
}

void StateChart::setInitialAction(const std::string& action)
{
    initial_action = action;
}

void StateChart::deleteState(int state_id)
{
    unsigned int state_index = findStateIndex(state_id);
    if(state_index == states.size())
        throw std::invalid_argument("Invalid state id");

    State* state = states[state_index];

    for(auto& out_transition : state->getOutTransitions())
    {
        unsigned int end_state_index =
            findStateIndex(out_transition->getEndState().getId());
        states[end_state_index]->removeInTransition(out_transition->getId());
    }

    for(auto& in_transition : state->getInTransitions())
    {
        unsigned int starting_state_index =
            findStateIndex(in_transition->getStartingState().getId());
        states[starting_state_index]->removeOutTransition(
            in_transition->getId());
    }

    delete states[state_index];
    states.erase(states.begin() + state_index);
}

void StateChart::deleteTransition(int transition_id)
{
    // Can be greatly improved
    bool transition_found = false;
    for(auto& state : states)
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
    std::string indent = std::string(4, ' ');
    bool first = true;

    code << "fsm model " << name << "(";
    if(in_variables.size() + out_variables.size() + inout_variables.size() != 0)
    {
        code << std::endl;
        for(auto& var : in_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << "in " << var->getName() << ": " << var->getType();
            first = false;
        }
        for(auto& var : out_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << "out " << var->getName() << ": " << var->getType();
            first = false;
        }
        for(auto& var : inout_variables)
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
    for(auto& state : states)
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
        for(auto& var : intern_variables)
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

    for(auto& state : states)
    {
        for(auto& transition : state->getOutTransitions())
        {
            if(!first)
                code << "," << std::endl;
            code << indent << indent;
            code << transition->getStartingState().getName() << " -- ";
            code << transition->getCondition();
            if(transition->hasAction())
            {
                code << " | ";
                code << transition->getAction();
            }
            code << " -> " << transition->getEndState().getName();
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

    for(auto& var : in_variables)
    {
        code << "input " << var->getName() << " : " << var->getType() << " = "
             << var->getStimuli() << std::endl;
    }

    for(auto& var : out_variables)
    {
        code << "output " << var->getName() << " : " << var->getType()
             << std::endl;
    }

    code << std::endl;

    code << "fsm instance = " << name << "(";
    if(in_variables.size() + out_variables.size() + inout_variables.size() != 0)
    {
        first = true;
        code << std::endl;
        for(auto& var : in_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << var->getName();
            first = false;
        }
        for(auto& var : out_variables)
        {
            if(!first)
            {
                code << "," << std::endl;
            }
            code << indent;
            code << var->getName();
            first = false;
        }
        for(auto& var : inout_variables)
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
    if(state_id < 0)
        throw std::invalid_argument("Id must be positive");

    unsigned int index = 0;
    while(index < states.size() && states[index]->getId() != (unsigned)state_id)
    {
        index++;
    }

    return index;
}
