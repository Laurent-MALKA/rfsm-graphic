#ifndef STATE_CHART_HPP_INCLUDED
#define STATE_CHART_HPP_INCLUDED

#include "InputVariable.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include "Variable.hpp"

#include <string>
#include <vector>

class StateChart
{
  private:
    std::string name;

    std::vector<InputVariable*> in_variables;
    std::vector<Variable*> out_variables;
    std::vector<Variable*> inout_variables;
    std::vector<Variable*> intern_variables;

    std::vector<State*> states;
    int initial_state_id;
    std::string initial_action;

  public:
    explicit StateChart(const std::string& name = "StateChart");
    ~StateChart();

    std::string getName() const;
    void setName(const std::string& name);

    std::vector<InputVariable*> getInVariables();
    std::vector<Variable*> getOutVariables();
    std::vector<Variable*> getInoutVariables();
    std::vector<Variable*> getInternVariables();

    // Variable creations
    int addInVariable();
    int addOutVariable();
    int addInoutVariable();
    int addInternVariable();

    // Variable creations with args
    int addInVariable(const std::string& name,
                      const std::string& type,
                      const std::string& stimuli);
    int addOutVariable(const std::string& name, const std::string& type);
    int addInoutVariable(const std::string& name, const std::string& type);
    int addInternVariable(const std::string& name, const std::string& type);

    // Variable getters
    const InputVariable* getInVariable(int index) const;
    const Variable* getOutVariable(int index) const;
    const Variable* getInoutVariable(int index) const;
    const Variable* getInternVariable(int index) const;

    // Variable name setters
    void setInVariableName(int index, const std::string& name);
    void setOutVariableName(int index, const std::string& name);
    void setInoutVariableName(int index, const std::string& name);
    void setInternVariableName(int index, const std::string& name);

    // Variable type setters
    void setInVariableType(int index, const std::string& type);
    void setOutVariableType(int index, const std::string& type);
    void setInoutVariableType(int index, const std::string& type);
    void setInternVariableType(int index, const std::string& type);

    // Variable stimuli setter
    void setInVariableStimuli(int index, const std::string& stimuli);

    void removeInputVariable(int index);
    void removeOutputVariable(int index);
    void removeInoutVariable(int index);
    void removeInternVariable(int index);

    const State& getState(int state_id) const;
    State& getState(int state_id);
    bool stateExists(int state_id);

    Transition& getTransition(int transition_id);

    unsigned int addState(const char* name);
    unsigned int addState(const std::string& name);
    unsigned int addTransition(int starting_state_id,
                               int end_state_id,
                               const std::string& condition = "",
                               const std::string& action = "");

    void setInitialState(int state_id);
    void setInitialAction(const std::string& action);

    int getInitialStateId() const;

    void deleteState(int state_id);
    void deleteTransition(int transition_id);

    std::string toFSMCode();

  private:
    unsigned int findStateIndex(int state_id) const;
};

#endif