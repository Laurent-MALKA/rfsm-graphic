#include "StateUI.hpp"

#include <QFont>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QRectF>

StateUI::StateUI(State& state, double posX, double posY)
    : state(state), initial(false)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    qreal width = 100 + 2 * borderSize;
    qreal heigth = 50 + 2 * borderSize;
    setGeometry(
        posX - width / 2,
        posY - heigth / 2,
        width,
        heigth); // default size, compute size later ? setWidthFromStateName()

    setZValue(1);
}

State& StateUI::getState()
{
    return state;
}

const State& StateUI::getState() const
{
    return state;
}

int StateUI::type() const
{
    return Type;
}

bool StateUI::isInitial() const
{
    return initial;
}

void StateUI::setInitial(bool initial)
{
    this->initial = initial;
}

/**
 * Overload method the repaint the component
 */

void StateUI::paint(QPainter* painter,
                    const QStyleOptionGraphicsItem*,
                    QWidget*)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, borderSize);
    QBrush brush(Qt::white);

    if(isSelected())
        pen.setStyle(Qt::DashLine);
    else
        pen.setStyle(Qt::SolidLine);

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawRoundedRect(rect(), 20, 20);
    if(initial)
    {
        painter->setPen(QPen(Qt::NoPen));
        painter->setBrush(QBrush(Qt::lightGray, Qt::DiagCrossPattern));
        painter->drawRoundedRect(rect(), 20, 20);
        painter->setPen(pen);
        painter->setBrush(brush);
    }

    QPointF pos(rect().x(), rect().y());
    QTransform t = painter->transform();
    painter->resetTransform();
    pos = t.map(pos);

    painter->drawText(pos.x(),
                      pos.y(),
                      rect().width(),
                      rect().height(),
                      Qt::AlignHCenter | Qt::AlignVCenter,
                      state.getName().c_str());

    scene()->update();
}

QVariant StateUI::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if(change == ItemPositionChange
       || (change == ItemSelectedHasChanged && isSelected()))
    {
        auto colliding_items = collidingItems();
        if(colliding_items.empty())
            setZValue(1);
        else
        {
            for(auto& item : colliding_items)
            {
                if(zValue() <= item->zValue())
                    setZValue(item->zValue() + 1);
            }
        }
    }

    return QGraphicsWidget::itemChange(change, value);
}
