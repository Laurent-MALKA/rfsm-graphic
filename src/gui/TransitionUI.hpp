#ifndef TRANSITION_UI_HPP_INCLUDED
#define TRANSITION_UI_HPP_INCLUDED

#include <QGraphicsLineItem>

#include "../engine/Transition.hpp"
#include "StateUI.hpp"

class QPolygonF;

class TransitionUI : public QGraphicsLineItem
{
    private:
        Transition& transition;
        StateUI& start_state;
        StateUI& end_state;

        double border_size;
        double arrow_size;
        qreal arrow_angle;
        QPolygonF arrow_head;

    public:
       enum { Type = UserType + 2 };

        TransitionUI(Transition& transition, StateUI& start_state, StateUI& end_state);
        Transition& getTransition();
        StateUI& getStartState();
        StateUI& getEndState();

        QRectF boundingRect() const;
        QPainterPath shape() const;
        int type() const;

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

};

#endif
