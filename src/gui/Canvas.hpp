#ifndef RFSM_GRAPHIC_CANVAS_HPP
#define RFSM_GRAPHIC_CANVAS_HPP

#include <vector>
#include <QFrame>

#include "../engine/StateChart.hpp"
#include "StateUI.hpp"
#include "Tools.hpp"

class Canvas : public QFrame
{
  private:
    StateChart state_chart;
    std::vector<StateUI*> states;
    Tool* current_tool;
    
  public:
    Canvas(QWidget* parent = nullptr);
    StateUI* addState(float posX, float posY);
    void setCurrentTool(Tool* tool);
    //void addEdge(/* NODE infos */);

    void mousePressEvent(QMouseEvent *event);
};

#endif