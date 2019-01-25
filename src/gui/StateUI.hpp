#ifndef RFSM_GRAPHIC_STATE_UI_HPP
#define RFSM_GRAPHIC_STATE_UI_HPP

#include <QGraphicsWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QRegion>

#include "../engine/State.hpp"

class StateUI : public QGraphicsWidget
{
    private:
        State& state;
        float borderSize = 1;

    public:
        StateUI(State& state, double posX, double posY);

        State& getState();

        void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr);
};

#endif
