#ifndef ADD_TRANSITION_TOOL_HPP_INCLUDED
#define ADD_TRANSITION_TOOL_HPP_INCLUDED

#include "Tool.hpp"

class AddTransitionTool : public Tool
{
    public:
    explicit AddTransitionTool(MainWindow* main_window);
    ~AddTransitionTool();

    void pressAct(QGraphicsSceneMouseEvent *event) {}
    void releaseAct(QGraphicsSceneMouseEvent *event);
};

#endif