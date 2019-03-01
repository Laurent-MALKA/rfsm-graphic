#include "StateUI.hpp"

#include <QFont>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QRectF>

StateUI::StateUI(State& state, double posX, double posY)
    : state(state), initial(false), size(100, 50)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setPos(posX - size.width() / 2, posY - height / 2);

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

QRectF StateUI::boundingRect() const
{
    return QRectF(0, 0, size.width(), size.height())
        .adjusted(-border_size / 2,
                  -border_size / 2,
                  border_size / 2,
                  border_size / 2);
}

QPainterPath StateUI::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(0, 0, size.width(), size.height())
                     .adjusted(-border_size / 2,
                               -border_size / 2,
                               border_size / 2,
                               border_size / 2));
    return path;
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
 * Overload method to repaint the component
 */
void StateUI::paint(QPainter* painter,
                    const QStyleOptionGraphicsItem*,
                    QWidget*)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black);
    QBrush brush(Qt::SolidPattern);

    if(isSelected())
        brush.setColor(QColor(199, 212, 255));
    else
        brush.setColor(Qt::lightGray);

    if(initial)
        border_size = 5;
    else
        border_size = 1;

    pen.setWidth(border_size);

    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawRect(0, 0, size.width(), size.height());

    painter->drawText(0,
                      0,
                      size.width(),
                      size.height(),
                      Qt::AlignHCenter | Qt::AlignVCenter,
                      state.getName().c_str());
}

QVariant StateUI::itemChange(GraphicsItemChange change, const QVariant& value)
{
    if(scene() != nullptr)
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
        if(change == ItemPositionChange)
        {
            scene()->update();

            QPointF newPos = value.toPointF();
            QRectF scene_rect = scene()->sceneRect();

            if(!scene_rect.contains(newPos))
            {
                newPos.setX(qMin(scene_rect.right(),
                                 qMax(newPos.x(), scene_rect.left())));
                newPos.setY(qMin(scene_rect.bottom(),
                                 qMax(newPos.y(), scene_rect.top())));

                return newPos;
            }
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
