#ifndef TRANSITION_HPP_INCLUDED
#define TRANSITION_HPP_INCLUDED

#include <vector>

class Node;

class Transition
{
    private:
        static unsigned int transitions_counter;
        unsigned int id;
        std::string condition;
        std::string action;

        Node& starting_node;
        Node& end_node;

    public:
        Transition(Node& starting_node, Node& end_node);

        unsigned int getId() const;

        const std::string& getCondition() const;
        void setCondition(const char*);
        void setCondition(const std::string&);

        const std::string& getAction() const;
        void setAction(const char* action);
        void setAction(std::string action);
        bool hasAction();

        const Node& getStartingNode() const;
        const Node& getEndNode() const;

        unsigned int getStartingNodeId() const;
        unsigned int getEndNodeId() const;
};

#endif