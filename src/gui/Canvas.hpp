#ifndef RFSM_GRAPHIC_CANVAS_HPP
#define RFSM_GRAPHIC_CANVAS_HPP

#include "../engine/StateChart.hpp"
#include "StateUI.hpp"
#include "TransitionUI.hpp"

#include <QGraphicsScene>
#include <vector>

class MainWindow;

class Canvas : public QGraphicsScene
{
  private:
    StateChart* state_chart;
    std::vector<StateUI*> states;
    std::vector<TransitionUI*> transitions;
    MainWindow* main_window;

  public:
    explicit Canvas(MainWindow* parent);
    ~Canvas();

    StateChart* getStateChart();

    const std::vector<StateUI*> getStates() const;
    std::vector<StateUI*> getStates();

    StateUI* addState(double posX, double posY);
    TransitionUI* addTransition(StateUI* start_state, StateUI* end_state);

    const StateUI* getInitialState() const;
    void setInitialState(int state_id);

    void deleteState(int state_id);
    void deleteTransition(int transition_id);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    void setStatesFlag(QGraphicsItem::GraphicsItemFlag flag,
                       bool enabled = true);
    void setTransitionsFlag(QGraphicsItem::GraphicsItemFlag flag,
                            bool enabled = true);

    void importCanvas(const std::string& json);
    std::string exportCanvas();

    void selectAllItems();
    void deleteSelectedItems();

    void clear();

  private:
    void free(); /* WARNING : Doesn't reallocate state_chart,
                  * clearCanvas() does
                  */
};

#endif
