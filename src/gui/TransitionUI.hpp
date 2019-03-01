#ifndef TRANSITION_UI_HPP_INCLUDED
#define TRANSITION_UI_HPP_INCLUDED

#include "../engine/Transition.hpp"
#include "StateUI.hpp"

#include <QGraphicsItem>

class QPolygonF;
class QPainterPath;

class TransitionUI : public QGraphicsItem
{
  private:
    Transition& transition;
    StateUI* start_state;
    StateUI* end_state;

    double border_size;
    double arrow_size;
    qreal arrow_angle;

    QPolygonF line;
    QPolygonF arrow_head;

    QPainterPath path;

  public:
    enum
    {
        Type = UserType + 2
    };

    TransitionUI(Transition& transition,
                 StateUI* start_state,
                 StateUI* end_state);

    Transition& getTransition();
    StateUI& getStartState();
    StateUI& getEndState();
    const Transition& getTransition() const;
    const StateUI& getStartState() const;
    const StateUI& getEndState() const;

    void setStartState(StateUI* start_state);
    void setEndState(StateUI* end_state);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    int type() const;

    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget = 0);

  private:
    void defineLine();
    void defineArrowHead();
};

#endif
