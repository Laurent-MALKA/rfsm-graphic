#include "InputVariable.hpp"

InputVariable::InputVariable():Variable()
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