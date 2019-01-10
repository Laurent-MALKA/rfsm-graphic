#ifndef TRANSITION_HPP_INCLUDED
#define TRANSITION_HPP_INCLUDED

#include <vector>

class State;

class Transition
{
    private:
        static unsigned int transitions_counter;
        unsigned int id;
        std::string condition;
        std::string action;

        State& starting_node;
        State& end_node;

    public:
        Transition(State& starting_node, State& end_node);

        unsigned int getId() const;

        const std::string& getCondition() const;
        void setCondition(const char*);
        void setCondition(const std::string&);

        const std::string& getAction() const;
        void setAction(const char* action);
        void setAction(std::string action);
        bool hasAction();

        const State& getStartingNode() const;
        const State& getEndNode() const;

        unsigned int getStartingNodeId() const;
        unsigned int getEndNodeId() const;
};

#endif