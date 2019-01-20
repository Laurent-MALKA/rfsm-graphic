#ifndef STATE_CHART_HPP_INCLUDED
#define STATE_CHART_HPP_INCLUDED

#include <vector>
#include "State.hpp"
#include "Transition.hpp"
#include "Variable.hpp"
#include "InputVariable.hpp"

class StateChart
{
    private:
        std::string name;
        
        std::vector<InputVariable*> in_variables;
        std::vector<Variable*> out_variables;
        std::vector<Variable*> inout_variables;
        std::vector<Variable*> intern_variables;

        std::vector<State *> states;
        int initial_state_id;
        std::string initial_action;

    public:
        StateChart();
        ~StateChart();

        std::string getName() const;
        void setName(std::string name);

        std::vector<InputVariable*> getInVariables();
        std::vector<Variable*> getOutVariables();
        std::vector<Variable*> getInoutVariables();
        std::vector<Variable*> getInternVariables();

        //Variable creations
        int addInVariable();
        int addOutVariable();
        int addInoutVariable();
        int addInternVariable();

        //Variable getters
        const InputVariable* getInVariable(int index) const;
        const Variable* getOutVariable(int index) const;
        const Variable* getInoutVariable(int index) const;
        const Variable* getInternVariable(int index) const;       

        //Variable name setters
        void setInVariableName(int index, std::string name);
        void setOutVariableName(int index, std::string name);
        void setInoutVariableName(int index, std::string name);
        void setInternVariableName(int index, std::string name);

        //Variable type setters
        void setInVariableType(int index, std::string type);
        void setOutVariableType(int index, std::string type);
        void setInoutVariableType(int index, std::string type);
        void setInternVariableType(int index, std::string type);

        //Variable stimuli setter
        void setInVariableStimuli(int index, std::string stimuli);
                
        const State& getState(int state_id) const;
        State& getState(int state_id);
        bool stateExists(int state_id);

        unsigned int addState(const char* name);
        unsigned int addState(std::string name);
        unsigned int addTransition(int starting_state_id, int end_state_id, std::string condition, std::string action);

        void setInitialState(int state_id);
        void setInitialAction(std::string action);

        void deleteState(int state_id);
        void deleteTransition(int transition_id);

        std::string toFSMCode();
        
    private:
        unsigned int findStateIndex(int state_id) const;
};

#endif