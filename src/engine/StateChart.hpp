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

        std::vector<State *> nodes;
        int initial_node_id;
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
                
        const State& getNode(int node_id) const;
        bool nodeExists(int node_id);

        unsigned int addNode(const char* name);
        unsigned int addNode(std::string name);
        unsigned int addTransition(int starting_node_id, int end_node_id, std::string condition, std::string action);

        void setInitialNode(int node_id);
        void setInitialAction(std::string action);

        void deleteNode(int node_id);
        void deleteTransition(int transition_id);

        std::string toFSMCode();
        
    private:
        unsigned int findNodeIndex(int node_id) const;
};

#endif