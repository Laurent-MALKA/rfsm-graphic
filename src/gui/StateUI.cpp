#include <QRectF>
#include <QPen>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>

#include "StateUI.hpp"

StateUI::StateUI(QWidget *parent, State& state, float posX, float posY) :
    QWidget(parent),
    state(state)
{
    this->resize(100 + 2*borderSize, 50 + 2*borderSize); // default size, compute size later ? setWidthFromStateName()
    this->move(posX,posY);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QLabel* label = new QLabel(state.getName().c_str());
    label->setFont(QFont("Arial", 16, QFont::Bold));
    layout->addWidget(label);

    setLayout(layout);
}

/**
 * Overload method the repaint the component
 */
void StateUI::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, borderSize);
    painter.setPen(pen);
    painter.setBrush(Qt::white);

    QRectF rect(borderSize/2, borderSize/2, width() - 2*borderSize, height() - 2*borderSize);
    painter.drawRoundedRect(rect, 20, 20);
}
