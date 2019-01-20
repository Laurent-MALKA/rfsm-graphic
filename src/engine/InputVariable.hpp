#ifndef INPUT_VARIABLE_HPP_INCLUDED
#define INPUT_VARIABLE_HPP_INCLUDED

#include "Variable.hpp"

class InputVariable : public Variable
{
    public:
        static std::vector<std::string> Types;
    private:
        std::string stimuli;
    public:
        InputVariable(std::string name, int type_index = 0, std::string stimuli = "");

        std::string getStimuli() const;

        void setStimuli(std::string stimuli);
        void setStimuli(const char* stimuli);

};

#endif