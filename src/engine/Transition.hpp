#ifndef TRANSITION_HPP_INCLUDED
#define TRANSITION_HPP_INCLUDED

#include <string>
#include <vector>

class State;

class Transition
{
  private:
    static unsigned int transitions_counter;
    unsigned int id;
    std::string condition;
    std::string action;

    State* start_state;
    State* end_state;

  public:
    Transition(State* start_state, State* end_state);

    unsigned int getId() const;

    const std::string& getCondition() const;
    void setCondition(const std::string&);

    const std::string& getAction() const;
    void setAction(const std::string& action);
    bool hasAction();

    const State& getStartState() const;
    const State& getEndState() const;

    void setStartState(State* start_state);
    void setEndState(State* end_state);

    unsigned int getStartStateId() const;
    unsigned int getEndStateId() const;
};

#endif