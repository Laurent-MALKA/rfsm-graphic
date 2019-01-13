#ifndef RFSM_GRAPHIC_STATE_UI_HPP
#define RFSM_GRAPHIC_STATE_UI_HPP

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

#include "../engine/State.hpp"

class StateUI : public QWidget
{
    private:
        State& state;
        float borderSize = 4;

    public:
        StateUI(QWidget *parent, State& state, float posX, float posY);

        void paintEvent(QPaintEvent*);

};

#endif