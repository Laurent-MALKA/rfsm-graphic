#ifndef SET_INITIAL_STATE_TOOL_HPP_INCLUDED
#define SET_INITIAL_STATE_TOOL_HPP_INCLUDED

#include "Tool.hpp"

class StateUI;

class SetInitialStateTool : public Tool
{
  private:
    StateUI* current_initial_state;
  public:
    explicit SetInitialStateTool(MainWindow* main_window);
    ~SetInitialStateTool() = default;

    void pressAct(QGraphicsSceneMouseEvent* event) override;
    void releaseAct(QGraphicsSceneMouseEvent* event) override {}
};

#endif
