#ifndef ADD_TRANSITION_TOOL_HPP_INCLUDED
#define ADD_TRANSITION_TOOL_HPP_INCLUDED

#include "Tool.hpp"

class AddTransitionTool : public Tool
{
  public:
    explicit AddTransitionTool(MainWindow* main_window);
    ~AddTransitionTool() = default;

    void pressAct(QGraphicsSceneMouseEvent* event) override {}
    void releaseAct(QGraphicsSceneMouseEvent* event) override;
};

#endif