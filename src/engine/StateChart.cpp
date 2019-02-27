#include "StateChart.hpp"
#include "Transition.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>

StateChart::StateChart(const std::string& name)
    : name(name), initial_state_id(-1)
{}

StateChart::~StateChart()
{
    for(auto& state : states)
    {
        for(auto& out_transition : state->getOutTransitions())
            delete out_transition;
        delete state;
    }

    for(auto& var : in_variables)
        delete var;

    for(auto& var : out_variables)
        delete var;

    for(auto& var : inout_variables)
        delete var;

    for(auto& var : intern_variables)
        delete var;
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

int StateChart::addInVariable(const std::string& name,
                              const std::string& type,
                              const std::string& stimuli)
{
    in_variables.push_back(new InputVariable(name, type, stimuli));
    return in_variables.size() - 1;
}

int StateChart::addOutVariable(const std::string& name, const std::string& type)
{
    out_variables.push_back(new Variable(name, type));
    return out_variables.size() - 1;
}

int StateChart::addInoutVariable(const std::string& name,
                                 const std::string& type)
{
    inout_variables.push_back(new Variable(name, type));
    return inout_variables.size() - 1;
}

int StateChart::addInternVariable(const std::string& name,
                                  const std::string& type)
{
    intern_variables.push_back(new Variable(name, type));
    return intern_variables.size() - 1;
}

const InputVariable* StateChart::getInVariable(int index) const
{
    if(index < 0 || in_variables.size() <= index)
        throw std::out_of_range("invalid index");

    return in_variables[index];
}

const Variable* StateChart::getOutVariable(int index) const
{
    if(index < 0 && out_variables.size() <= index)
        throw std::out_of_range("invalid index");

    return out_variables[index];
}

const Variable* StateChart::getInoutVariable(int index) const
{
    if(index < 0 && inout_variables.size() <= index)
        throw std::out_of_range("invalid index");

    return inout_variables[index];
}

const Variable* StateChart::getInternVariable(int index) const
{
    if(index < 0 && intern_variables.size() <= index)
        throw std::out_of_range("invalid index");

    return intern_variables[index];
}

void StateChart::setInVariableName(int index, const std::string& name)
{
    if(index < 0 && in_variables.size() <= index)
        throw std::out_of_range("invalid index");

    in_variables[index]->setName(name);
}

void StateChart::setOutVariableName(int index, const std::string& name)
{
    if(index < 0 && out_variables.size() <= index)
        throw std::out_of_range("invalid index");

    out_variables[index]->setName(name);
}

void StateChart::setInoutVariableName(int index, const std::string& name)
{
    if(index < 0 && inout_variables.size() <= index)
        throw std::out_of_range("invalid index");

    inout_variables[index]->setName(name);
}

void StateChart::setInternVariableName(int index, const std::string& name)
{
    if(index < 0 && intern_variables.size() <= index)
        throw std::out_of_range("invalid index");

    intern_variables[index]->setName(name);
}

void StateChart::setInVariableType(int index, const std::string& type)
{
    if(index < 0 && in_variables.size() <= index)
        throw std::out_of_range("invalid index");

    in_variables[index]->setType(type);
}

void StateChart::setOutVariableType(int index, const std::string& type)
{
    if(index < 0 && out_variables.size() <= index)
        throw std::out_of_range("invalid index");

    out_variables[index]->setType(type);
}

void StateChart::setInoutVariableType(int index, const std::string& type)
{
    if(index < 0 && inout_variables.size() <= index)
        throw std::out_of_range("invalid index");

    inout_variables[index]->setType(type);
}

void StateChart::setInternVariableType(int index, const std::string& type)
{
    if(index < 0 && intern_variables.size() <= index)
        throw std::out_of_range("invalid index");

    intern_variables[index]->setType(type);
}

void StateChart::setInVariableStimuli(int index, const std::string& stimuli)
{
    if(index < 0 && in_variables.size() <= index)
        throw std::out_of_range("invalid index");

    in_variables[index]->setStimuli(stimuli);
}

void StateChart::removeInputVariable(int index)
{
    if(index < 0 || in_variables.size() <= index)
        throw std::invalid_argument("Wrong variable index");

    in_variables.erase(in_variables.begin() + index);
}

void StateChart::removeOutputVariable(int index)
{
    if(index < 0 || out_variables.size() <= index)
        throw std::invalid_argument("Wrong variable index");

    out_variables.erase(out_variables.begin() + index);
}

void StateChart::removeInoutVariable(int index)
{
    if(index < 0 || inout_variables.size() <= index)
        throw std::invalid_argument("Wrong variable index");

    inout_variables.erase(inout_variables.begin() + index);
}

void StateChart::removeInternVariable(int index)
{
    if(index < 0 || intern_variables.size() <= index)
        throw std::invalid_argument("Wrong variable index");

    intern_variables.erase(intern_variables.begin() + index);
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

    Transition* new_transition = new Transition(starting_state, end_state);

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

int StateChart::getInitialStateId() const
{
    return initial_state_id;
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

    if(initial_state_id == state_id)
        initial_state_id = -1;
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

    if(!intern_variables.empty())
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


    std::stringstream transitions_code;
    transitions_code << indent;
    transitions_code << "trans: " << std::endl;
    first = true;

    for(auto& state : states)
    {
        for(auto& transition : state->getOutTransitions())
        {
            if(!first)
                transitions_code << "," << std::endl;
            transitions_code << indent << indent;
            transitions_code << transition->getStartingState().getName() << " -- ";
            if(transition->getCondition().empty())
                throw std::invalid_argument("A transition doesn't have a condition");
            transitions_code << transition->getCondition();
            if(transition->hasAction())
            {
                transitions_code << " | ";
                transitions_code << transition->getAction();
            }
            transitions_code << " -> " << transition->getEndState().getName();
            first = false;
        }
    }
    transitions_code << ";" << std::endl;

    if(!first)
        code << transitions_code.str();

    code << indent;
    code << "itrans: " << std::endl;
    code << indent << indent;
    if(!initial_action.empty())
        code << "| " << initial_action << " ";
    if(initial_state_id == -1)
        throw std::invalid_argument("Initial state undefined");
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
