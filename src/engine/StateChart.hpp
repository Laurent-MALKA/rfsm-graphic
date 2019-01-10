#ifndef STATE_CHART_HPP_INCLUDED
#define STATE_CHART_HPP_INCLUDED

#include <vector>
#include "State.hpp"
#include "Transition.hpp"
#include "Variable.hpp"

class StateChart
{
    private:
        std::string name;
        
        std::vector<Variable*> in_variables;
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

        std::vector<Variable*> getInVariables();
        std::vector<Variable*> getOutVariables();
        std::vector<Variable*> getInoutVariables();
        std::vector<Variable*> getInternVariables();

        void addInVariable();
        void addOutVariable();
        void addInoutVariable();
        void addInternVariable();
                
        const State& getState(int state_id) const;
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