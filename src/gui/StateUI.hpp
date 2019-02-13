#ifndef RFSM_GRAPHIC_STATE_UI_HPP
#define RFSM_GRAPHIC_STATE_UI_HPP

#include <QGraphicsWidget>

#include "../engine/State.hpp"

class StateUI : public QGraphicsWidget
{
    private:
        State& state;
        float borderSize = 1;

    public:
        enum { Type = UserType + 1 };

        StateUI(State& state, double posX, double posY);

        State& getState();

        int type() const;

        void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr);

        void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
};

#endif
