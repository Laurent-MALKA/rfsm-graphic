#include "StateUI.hpp"

StateUI::StateUI(QWidget *parent, State& state, int posX, int posY) :
    QWidget(parent),
    state(state),
    posX(posX),
    posY(posY)
{
    move(posX,posY);
    resize(50,50);
}

void StateUI::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(125,125,125));
    painter.setPen(QColor(0,0,0)); 
    painter.drawText(0,0,QString(state.getName().c_str()));
}
