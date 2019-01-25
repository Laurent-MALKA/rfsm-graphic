#include <QRectF>
#include <QPen>
#include <QLabel>
#include <QFont>
#include <QGraphicsLayout>
#include <QGraphicsAnchorLayout>

#include "StateUI.hpp"

StateUI::StateUI(State& state, double posX, double posY) :
    state(state)
{

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    qreal width = 100 + 2*borderSize;
    qreal heigth = 50 + 2*borderSize;
    setGeometry(posX - width/2,posY - heigth/2, width, heigth); // default size, compute size later ? setWidthFromStateName()
}

State& StateUI::getState()
{
    return state;
}

/**
 * Overload method the repaint the component
 */

void StateUI::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, borderSize);
    painter->setPen(pen);
    painter->setBrush(Qt::white);

    painter->drawRoundedRect(rect(), 20, 20);

    QPointF pos(rect().x(), rect().y());
    QTransform t = painter->transform();
    painter->resetTransform();
    pos = t.map(pos);

    painter->drawText(pos.x(), pos.y(), rect().width(), rect().height(), Qt::AlignHCenter | Qt::AlignVCenter, state.getName().c_str());
}
