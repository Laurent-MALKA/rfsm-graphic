#ifndef RFSM_GRAPHIC_CANVAS_HPP
#define RFSM_GRAPHIC_CANVAS_HPP

#include <vector>

#include <QFrame>

#include "../engine/StateChart.hpp"
#include "StateUI.hpp"

class Canvas : public QFrame
{
  private:
    StateChart state_chart;
    std::vector<StateUI*> states;
    
  
  public:
    void addState(std::string name, int posX, int posY);
    //void addEdge(/* NODE infos */);
};

#endif