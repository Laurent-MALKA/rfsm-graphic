#include "InputVariable.hpp"

std::vector<std::string> InputVariable::Types = {"event", "bool", "int", "float"};

InputVariable::InputVariable(std::string name, int type_index, std::string stimuli):Variable(name,type_index), stimuli(stimuli)
{
    
}

std::string InputVariable::getStimuli() const
{
    return stimuli;
}

void InputVariable::setStimuli(std::string stimuli)
{
    this->stimuli = stimuli;
}

void InputVariable::setStimuli(const char* stimuli)
{
    this->stimuli = stimuli;
}