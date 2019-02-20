#ifndef INPUT_VARIABLE_HPP_INCLUDED
#define INPUT_VARIABLE_HPP_INCLUDED

#include "Variable.hpp"

class InputVariable : public Variable
{
    private:
        static std::vector<std::string> InputTypes;
        std::string stimuli;
    public:
        InputVariable(const std::string& name, int type_index = 0, const std::string& stimuli = "");

        std::vector<std::string> getTypes() const;

        std::string getStimuli() const;

        void setStimuli(const std::string& stimuli);
        void setStimuli(const char* stimuli);

};

#endif