#include <QRectF>
#include <QPen>
#include <QFont>
#include <QPainter>
#include <QGraphicsScene>

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

    setZValue(1);
}

State& StateUI::getState()
{
    return state;
}

int StateUI::type() const
{
    return Type;
}


/**
 * Overload method the repaint the component
 */

void StateUI::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, borderSize);
    
    if(isSelected())
        pen.setStyle(Qt::DashLine);
    else
        pen.setStyle(Qt::SolidLine);
    
    painter->setPen(pen);
    painter->setBrush(Qt::white);

    painter->drawRoundedRect(rect(), 20, 20);

    QPointF pos(rect().x(), rect().y());
    QTransform t = painter->transform();
    painter->resetTransform();
    pos = t.map(pos);

    painter->drawText(pos.x(), pos.y(), rect().width(), rect().height(), Qt::AlignHCenter | Qt::AlignVCenter, state.getName().c_str());

    scene()->update();
}

QVariant StateUI::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange || change == ItemSelectedHasChanged && isSelected())
    {
        auto colliding_items = collidingItems();
        if(colliding_items.size() == 0)
            setZValue(1);
        else
        {
            for(auto& item: colliding_items)
            {
                if(zValue() <= item->zValue())
                    setZValue(item->zValue() + 1);
            }
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
