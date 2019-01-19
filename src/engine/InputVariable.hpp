#ifndef INPUT_VARIABLE_HPP_INCLUDED
#define INPUT_VARIABLE_HPP_INCLUDED

#include "Variable.hpp"

class InputVariable : public Variable
{
    private:
        std::string stimuli;  
    public:
        InputVariable();

        std::string getStimuli() const;

        void setStimuli(std::string stimuli);
        void setStimuli(const char* stimuli);

};

#endif