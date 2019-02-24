#include "InputVariable.hpp"

InputVariable::InputVariable(const std::string& name,
                             const std::string& type_index,
                             const std::string& stimuli)
    : Variable(name, type_index), stimuli(stimuli)
{}

const std::string& InputVariable::getStimuli() const
{
    return stimuli;
}

void InputVariable::setStimuli(const std::string& stimuli)
{
    this->stimuli = stimuli;
}

void InputVariable::setStimuli(const char* stimuli)
{
    this->stimuli = stimuli;
}