#ifndef RFSM_GRAPHIC_CANVAS_HPP
#define RFSM_GRAPHIC_CANVAS_HPP

#include <vector>

#include <QGraphicsScene>

#include "../engine/StateChart.hpp"
#include "StateUI.hpp"
#include "TransitionUI.hpp"

class MainWindow;

class Canvas : public QGraphicsScene
{
  private:
    StateChart state_chart;
    std::vector<StateUI*> states;
    std::vector<TransitionUI*> transitions;
    QGraphicsView *view;
    MainWindow *main_window;
    
  public:
    Canvas(MainWindow* parent = nullptr);

    const std::vector<StateUI*> getStates() const;
    StateUI* addState(double posX, double posY);
    TransitionUI* addTransition(StateUI& start_state, StateUI& end_state); 
    void deleteState(int state_id);
    void deleteTransition(int transition_id);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    void setStatesFlag(QGraphicsItem::GraphicsItemFlag flag, bool enabled = true);
    //void addEdge(/* NODE infos */);
};

#endif
