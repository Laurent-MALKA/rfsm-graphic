#include "InputVariable.hpp"

std::vector<std::string> InputVariable::InputTypes = {"event",
                                                      "bool",
                                                      "int",
                                                      "float"};

InputVariable::InputVariable(const std::string& name,
                             int type_index,
                             const std::string& stimuli)
    : Variable(name, type_index), stimuli(stimuli)
{}

std::vector<std::string> InputVariable::getTypes() const
{
    return InputTypes;
}

std::string InputVariable::getStimuli() const
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