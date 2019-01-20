#ifndef RFSM_GRAPHIC_STATE_UI_HPP
#define RFSM_GRAPHIC_STATE_UI_HPP

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QRegion>

#include "../engine/State.hpp"

class StateUI : public QWidget
{
    private:
        State& state;
        float borderSize = 1;

    public:
        StateUI(QWidget *parent, State& state, float posX, float posY);

        State& getState();

        void paintEvent(QPaintEvent*);
};

#endif