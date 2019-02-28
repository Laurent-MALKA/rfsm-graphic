#ifndef INPUT_VARIABLE_HPP_INCLUDED
#define INPUT_VARIABLE_HPP_INCLUDED

#include "Variable.hpp"

class InputVariable : public Variable
{
  private:
    std::string stimuli;

  public:
    InputVariable(const std::string& name,
                  const std::string& type = "int",
                  const std::string& stimuli = "");

    const std::string& getStimuli() const;

    void setStimuli(const std::string& stimuli);
};

#endif