#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include <string>
#include <vector>

class Transition;

class State
{
  private:
    static unsigned int states_counter;
    unsigned int id;
    std::string name;
    std::vector<Transition*> in_transitions;
    std::vector<Transition*> out_transitions;

  public:
    State(const std::string& name = "", int id = -1);
    // State(State&); //for copy/pasting

    unsigned int getId() const;

    static unsigned int getStatesCounter();

    const Transition& getInTransition(int id) const;
    const Transition& getOutTransition(int id) const;

    const std::vector<Transition*> getInTransitions() const;
    const std::vector<Transition*> getOutTransitions() const;
    std::vector<Transition*> getInTransitions();
    std::vector<Transition*> getOutTransitions();

    void addInTransition(Transition*);
    void addOutTransition(Transition*);

    void removeInTransition(int id);
    void removeOutTransition(int id);

    const std::string& getName() const;
    void setName(const std::string& name);

    bool isInInTransitions(int id);
    bool isInOutTransitions(int id);

  private:
    unsigned int findInTransition(int id) const;
    unsigned int findOutTransition(int id) const;
};

#endif